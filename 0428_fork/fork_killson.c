 #include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
	pid_t pid;
	//pid_t pidChild;
	pid = fork();
	if(pid < 0)
	{
		printf("erro");
	}
	if( pid == 0)
	{
		slepp(3);
		printf("child--this[%d]\n",getpid());
		pid = fork();	
		if(pid == 0)
		{
			while(1)
			{
				printf("childs child [%d]",getpid());
				sleep(1);
			}
		}
		else
		{
			exit(1);
		}
		
	}
	else
	{	
		waitpid(pid,NULL,0);
		printf("this is father father[%d] chile[ %d]\n",getpid(),pid);
		
	}
	exit(1);

}
