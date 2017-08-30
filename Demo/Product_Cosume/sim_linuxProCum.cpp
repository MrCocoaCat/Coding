#include<iostream>
            queue<int>* m_requests;  
            pthread_mutex_t m_mutex;  
            pthread_cond_t m_not_full_cond;  
            pthread_cond_t m_not_empty_cond;  
            int m_bufSize;  
            void SetMaxLength(uint32_t bufSize);  
            void Push(int req);  
            int Pop(uint32_t timeout);  

    void Push(int req)  
    {  
        /**  上锁  */  
        pthread_mutex_lock(&m_mutex);  
          
        // 如果队列满，等待信号 
        while ( m_requests->size() == m_bufSize)  
        {  
            pthread_cond_wait(&m_not_full_cond, &_mutex);  
        }  
        m_requests->push(req);  
          
        //* 发送非空信号 
        pthread_cond_signal(&m_not_empty_cond);  
      
        //* 解锁 
        pthread_mutex_unlock(&m_mutex);  
    }  

    int Pop()  
    {  
        int ret = 0;  
        int req = -1;  
        //* 上锁 
        pthread_mutex_lock(&_mutex);  
        //* 若队列空等待指定时间 
        while (ret == 0 && _requests->empty())  
        {  
            ret = pthread_cond_timedwait(&_not_empty_cond, &_mutex, &timepass);  
        }  
        //* 没有数据，返回没有数据标识 
        if(ret!=0)  
        {  
            pthread_mutex_unlock(&_mutex);  
            return req;  
        }  
        req = m_requests->front();  
        m_requests->pop();  
        //* 返回数据，发送队列非满信号 dddd
        pthread_cond_signal(&_not_full_cond); //拿走一个肯定不为满
       // * 解锁 
        pthread_mutex_unlock(&_mutex);  
        return req;  
    }  
