#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <string.h>
#include <signal.h>
#include <errno.h>
 
#define DEFAULT_TIME 10             /*10s检测一次*/
#define MIN_WAIT_TASK_NUM 10        /*如果queue_size > MIN_WAIT_TASK_NUM添加新的线程到线程池*/
#define DEFAULT_THREAD_VARY 10      /*每次创建和销毁线程的个数*/
#define true  1
#define false 0
 
/*任务结构体*/
typedef struct
{
    void *(*function)(void *);    /*函数指针，回调函数*/
    void *arg;                      /*上面函数的参数*/
}threadpool_task_t; 
 
typedef struct threadpool_t
{
    pthread_mutex_t lock;               /*用于锁住当前这个结构体taskpoll*/
    pthread_mutex_t thread_counter;     /*记录忙状态线程个数*/
    pthread_cond_t queue_not_full;      /*当任务队列满时，添加任务的线程阻塞，等待此条件变量*/
    pthread_cond_t queue_not_empty;     /*任务队列里不为空，通知等待获取任务的线程*/
    pthread_t *threads;                 /*保存工作线程tid的数组*/
    pthread_t adjust_tid;               /*管理线程tid*/
    threadpool_task_t *task_queue;      /*任务队列*/
    int min_thr_num;                    /*线程组内默认最小线程数*/
    int max_thr_num;                    /*线程组内默认最大线程数*/
    int live_thr_num;                   /*当前存活线程个数*/
    int busy_thr_num;                   /*忙状态线程个数*/
    int wait_exit_thr_num;                   /*要销毁的线程个数*/
    int queue_front;                    /*任务队列队头索引下标*/
    int queue_rear;                     /*任务队列队末索引下标*/
    int queue_size;                     /*任务队列中元素个数*/
    int queue_max_size;                 /*队列中最大容纳个数*/
    int shutdown;                       /*线程池使用状态，true（工作）或（销毁）false*/
}TP_T;
 
void *threadpool_thread(void *threadpool);
void *adjust_thread(void *threadpool);
int is_thread_alive(pthread_t tid);
int threadpool_free(TP_T *pool);
 
/*
 *最小线程个数，最大线程个数，队列最大个数
 */
TP_T *threadpool_create(int min_thr_num,int max_thr_num,int queue_max_size)
{
    int i;
    TP_T *pool = NULL;
    do{
        if((pool = (TP_T *)malloc(sizeof(TP_T))) == NULL)
        {
            printf("malloc threadpool fail\n");
            break;
        }
 
        pool->min_thr_num = min_thr_num;
        pool->max_thr_num = max_thr_num;
        pool->busy_thr_num = 0;
        pool->live_thr_num = min_thr_num;       /*存活线程个数*/
        pool->queue_size = 0;                   /*目前任务队列个数*/
        pool->queue_max_size = queue_max_size;  /*最大任务个数*/
        pool->queue_front = 0;                  /*队列头索引*/
        pool->queue_rear = 0;                   /*队列尾索引*/
        pool->shutdown = false;                 /*线程池运行*/
 
        /*创建存放线程id数组*/
        pool->threads = (pthread_t *)malloc(sizeof(pthread_t)*max_thr_num);
        if(pool->threads == NULL)
        {
            printf("malloc threads fail\n");
            break;
        }
 
        memset(pool->threads,0,sizeof(pool->threads));
 
        /*创建存放队列内容的数组*/
        pool->task_queue = (threadpool_task_t *)malloc(sizeof(threadpool_task_t)*queue_max_size);
 
        if(pool->task_queue == NULL)
        {
            printf("malloc task_queue fail\n");
            break;
        }
 
        //初始化锁
        if(pthread_mutex_init(&(pool->lock),NULL) != 0
                || pthread_mutex_init(&(pool->thread_counter),NULL) != 0
                || pthread_cond_init(&(pool->queue_not_empty),NULL) != 0 
                || pthread_cond_init(&(pool->queue_not_full),NULL) != 0)
        {
            printf("init the lock or cond fail\n");
            break;
        }
 
        /*启动min_thr_num个work thread创建任务线程*/
        for(int i=0;i<min_thr_num;i++)
        {
            pthread_create(&(pool->threads[i]),NULL,threadpool_thread,(void *)pool);
            printf("start thread 0x%x...\n",(unsigned int)pool->threads[i]);
        }
        /*创建管理线程*/
        pthread_create(&(pool->adjust_tid),NULL,adjust_thread,(void *)pool);
        /*返回线程池首地址*/
        return pool;
 
    }while(0);
 
    threadpool_free(pool);
    return NULL;
}
 
/*
 *添加任务
 */
int threadpool_add(TP_T *pool,void *(*function)(void *arg),void *arg)
{
 
    pthread_mutex_lock(&(pool->lock));
 
    while((pool->queue_size == pool->queue_max_size) && (!pool->shutdown))
    {
        pthread_cond_wait(&(pool->queue_not_full),&(pool->lock));
    }
 
    if(pool->shutdown)
    {
        pthread_mutex_unlock(&(pool->lock));
    }
 
    /*添加任务到任务队列里*/
    if(pool->task_queue[pool->queue_rear].arg != NULL)
    {
        free(pool->task_queue[pool->queue_rear].arg);
        pool->task_queue[pool->queue_rear].arg = NULL;
    }
    pool->task_queue[pool->queue_rear].function = function;
    pool->task_queue[pool->queue_rear].arg = arg;
    pool->queue_rear = (pool->queue_rear + 1 )%pool->queue_max_size;
    pool->queue_size++;
 
    /*任务队列不为空，唤醒通知等待处理任务的线程*/
    pthread_cond_signal(&(pool->queue_not_empty));
    pthread_mutex_unlock(&(pool->lock));
 
    return 0;
}
 
/*
 *任务线程
 */
void *threadpool_thread(void *threadpool)
{
    TP_T *pool = (TP_T *)threadpool;
    threadpool_task_t task;
 
    while(true)
    {
        /*刚创建出线程，等待任务队列里有任务，否则阻塞等待任务队列里有任务后再唤醒接收任务*/
        pthread_mutex_lock(&(pool->lock));
 
        while((pool->queue_size == 0) && (!pool->shutdown))
        {
            printf("thread 0x%x is waiting\n",(unsigned int)pthread_self());
            /*条件变量表示当前队列不为空相当于生产者消费者，需要有任务才能继续*/
            pthread_cond_wait(&(pool->queue_not_empty),&(pool->lock));
            /*清除指定数目的空闲线程，如果要结束的线程个数大于0,结束线程*/
            if(pool->wait_exit_thr_num > 0)
            {
                pool->wait_exit_thr_num--;
                /*如果线程池里线程个数大于最小值时可以结束当前线程*/
                if(pool->live_thr_num > pool->min_thr_num)
                {
                    printf("thread 0x%x is exiting\n",(unsigned int)pthread_self());
                    pool->live_thr_num--;
                    pthread_mutex_unlock(&(pool->lock));
                    pthread_exit(NULL);
                }
            }
        }
 
        /*如果指定了true，要关闭线程池里的每个线程，自行退出处理*/
        if(pool->shutdown)
        {
            pthread_mutex_unlock(&(pool->lock));
            printf("thread 0x%x is exiting\n",(unsigned int)pthread_self());
            pthread_exit(NULL);
        }
        /*从任务队列里获得任务*/
        task.function = pool->task_queue[pool->queue_front].function;
        task.arg = pool->task_queue[pool->queue_front].arg;
        /*环形队列*/
        pool->queue_front = (pool->queue_front + 1)%pool->queue_max_size;
        pool->queue_size--;
 
        /*通知可以有新的任务添加进来*/
        pthread_cond_broadcast(&(pool->queue_not_full));
        pthread_mutex_unlock(&(pool->lock));
 
        /*执行任务*/
        printf("thread 0x%x start working\n",(unsigned int)pthread_self());
        pthread_mutex_lock(&(pool->thread_counter));
        pool->busy_thr_num++;                           /*忙状态线程数加1*/
        pthread_mutex_unlock(&(pool->thread_counter));  
        (*(task.function))(task.arg);                   /*执行回调函数任务*/
 
        /*任务结束处理*/
        printf("thread 0x%x end working\n",(unsigned int)pthread_self());
        pthread_mutex_lock(&(pool->thread_counter));
        pool->busy_thr_num--;                           /*忙状态数减1*/
        pthread_mutex_unlock(&(pool->thread_counter));
    }
    pthread_exit(NULL);
    return (NULL);
}
 
/*
 *管理线程
 *主要调整线程池里的线程个数，线程不够了，我去创建，线程太多了，我就销毁
 * */
void *adjust_thread(void *threadpool)
{
    int i;
    TP_T *pool = (TP_T *)threadpool;
    while(!pool->shutdown)
    {
        sleep(DEFAULT_TIME);                    /*延时10秒*/
        pthread_mutex_lock(&(pool->lock));
        int queue_size = pool->queue_size;      /*获取线程队列个数*/
        int live_thr_num = pool->live_thr_num;  /*获取存活的线程个数*/
        pthread_mutex_unlock(&(pool->lock));
 
        pthread_mutex_lock(&(pool->thread_counter));
        int busy_thr_num = pool->busy_thr_num;
        pthread_mutex_unlock(&(pool->thread_counter));
 
        /*任务数大于最小线程池个数并且存活的线程数少于最大线程个数时，创建新线程*/
        if(queue_size >= MIN_WAIT_TASK_NUM && live_thr_num < pool->max_thr_num)
        {
            pthread_mutex_lock(&(pool->lock));
            int add = 0;
            /*一次增加DEFAULT_THREAD个线程*/
            for(i = 0;i<pool->max_thr_num && add < DEFAULT_THREAD_VARY &&
                    pool->live_thr_num < pool->max_thr_num;i++)
            {
                if(pool->threads[i] == 0 || !is_thread_alive(pool->threads[i]))
                {
                    pthread_create(&(pool->threads[i]),NULL,threadpool_thread,(void *)pool);
                    add++;
                    pool->live_thr_num++;
                }
            }
            pthread_mutex_unlock(&(pool->lock));
        }
 
        /*销毁多余的空闲线程*/
        if((busy_thr_num * 2) < live_thr_num 
                && live_thr_num > pool->min_thr_num)
        {
            /*一次销毁DEFAULT_THREAD个线程*/
            pthread_mutex_lock(&(pool->lock));
            pool->wait_exit_thr_num = DEFAULT_THREAD_VARY;
            pthread_mutex_unlock(&(pool->lock));
 
            for(i=0;i<DEFAULT_THREAD_VARY;i++)
            {
                /*通知处在空闲状态的线程*/
                pthread_cond_signal(&(pool->queue_not_empty));
            }
        }
    }
}
 
int threadpool_destroy(TP_T *pool)
{
    int i;
    if(pool == NULL)
       return -1;
    
    pool->shutdown = true;
    /*先销毁管理线程*/
    pthread_join(pool->adjust_tid,NULL);
    /*通知所有的空闲线程*/
    pthread_cond_broadcast(&(pool->queue_not_empty));
    for(i=0; i<pool->min_thr_num;i++)
    {
        pthread_join(pool->threads[i],NULL);
    } 
    threadpool_free(pool);
    return 0;
}
 
int threadpool_free(TP_T *pool)
{
    if(pool == NULL)
        return -1;
 
    if(pool->task_queue)
        free(pool->task_queue);
 
    if(pool->threads)
    {
        free(pool->threads);
        pthread_mutex_lock(&(pool->lock));
        pthread_mutex_destroy(&(pool->lock));
        pthread_mutex_lock(&(pool->thread_counter));
        pthread_mutex_destroy(&(pool->thread_counter));
        pthread_cond_destroy(&(pool->queue_not_empty));
        pthread_cond_destroy(&(pool->queue_not_full));
    }
    free(pool);
    pool = NULL;
    return 0;
}
 
/*存活线程的个数*/
int threadpool_all_threadnum(TP_T *pool)
{
    int all_threadnum = -1;
    pthread_mutex_lock(&(pool->lock));
    all_threadnum = pool->live_thr_num;
    pthread_mutex_unlock(&(pool->lock));
    return all_threadnum;
}
 
/*返回忙的线程个数*/
int threadpool_busy_threadnum(TP_T *pool)
{
    int busy_threadnum = -1;
    pthread_mutex_lock(&(pool->thread_counter));
    busy_threadnum = pool->busy_thr_num;
    pthread_mutex_unlock(&(pool->thread_counter));
    return busy_threadnum;
}
 
/*测试线程是否存活*/
int is_thread_alive(pthread_t tid)
{
    //0号信号就是测试看是否存活
    int kill_rc = pthread_kill(tid,0);
    if(kill_rc == ESRCH)
        return false;
 
    return true;
}
/*测试使用，作成库时请注释掉下面代码*/
#if 1
void *process(void *arg)
{
    printf("thread 0x%x working on task %d\n",(unsigned int)pthread_self(),*(int *)arg);
    printf("task %d is end\n",*(int *)arg);
    return NULL;
}
 
int main()
{
    /*线程池里最小3个线程，最大100个，队列最大值12个*/
    TP_T *thp = threadpool_create(3,100,12);
    printf("pool inited\n");
 
    int *num = (int *)malloc(sizeof(int)*20);
 
    for(int i=0;i<10;i++)
    {
        num[i] = i;
        printf("add task %d\n",i);
        threadpool_add(thp,process,(void *)&num[i]);
    }    
    sleep(10);
    threadpool_destroy(thp);
    return 0;
}
#endif
