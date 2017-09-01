#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
//如果父进程先结束，子进程变成孤儿，没有资源泄漏
//子进程退出后，系统会帮忙掉wait 函数
void signal_handler(int sig_num)
{
	switch(si_num)
	{
		case SIGCHLD:
		{
			wait();
		}
		break;
	}
}
int main()
{
	int status;
	pid_t pid;
	//通过信号机制，父进程可以自己做自己的事情，不用一直wait
	signal(SIGCHLD,signal_handler);
	signal();
	pid=fork();
	if(pid < 0)
	{
		printf("erro");
	}
	if(pid == 0)
	{
		printf("child--this[%d]\n",getpid());	
		exit(1);
	}
	else
	{	
		while(1)
		{
			printf("this is father father[%d] chile[ %d]\n",getpid(),pid);
		}
		//waitpid(-1,&status,0);
		//if(WIFEXITED(status))
		//{
		//printf("%d",WEXITSTATUS(status));
		//}
	//	wait(NULL);
	//	while(1);
	}
	exit(1);

}
