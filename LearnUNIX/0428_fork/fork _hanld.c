#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<signal.h>
//����������Ƚ������ӽ��̱�ɹ¶���û����Դй©
//�ӽ����˳���ϵͳ���æ��wait ����
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
	//ͨ���źŻ��ƣ������̿����Լ����Լ������飬����һֱwait
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
