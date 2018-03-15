#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/wait.h>
int main()
{
	pid_t pid;
	pid=fork();
	int status;
	if(pid<0)
	{
		printf("erro");
	}
	if(pid==0)
	{
		printf("child--this[%d]\n",getpid());	
		exit(1);
	}
	else
	{	
		
		printf("this is father father[%d] chile[ %d]\n",getpid(),pid);
		waitpid(-1,&status,0);
		if(WIFEXITED(status))
		{
		printf("%d",WEXITSTATUS(status));
		}
	//	wait(NULL);
	//	while(1);
	}
	exit(1);

}
