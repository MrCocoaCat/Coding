#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<pthread.h>
#include<string.h>
void * thread_proc(void * param)
{
	int* p=(int*)malloc(sizeof(int));
	*p=123;
	pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
	
	printf("p:%d\n",*p);
	printf("%ld thread trart\n",pthread_self());
	sleep(5);
	//quit myself
	pthread_exit(p);
	printf("i will return \n");
	
	return p;

}
int main(int argc,char * argv[])
{
	void * threadret=NULL;
	int ret=0;
	pthread_t thread;
	ret=pthread_create(&thread,NULL,thread_proc,NULL);
	if(0!=ret)
	{
		perror("thread_creat");
		return -1;
	}
	//wait thread quit
	printf("creat thread :%ld\n",thread);
	sleep(2);
//	pthread_cancel(thread);
	pthread_join(thread,&threadret);
	printf("return value:%d\n",*(int*)threadret);
	free((int *)threadret);
	return 0;
}
