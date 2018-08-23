#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc,char *argv[])
{
	if(argc < 2)
	{
		printf("./app n\n");
		exit(1);
	}

	int i = 0;
	int count = atoi(argv[1]);
	pid_t pid;
	while(i++ < count)
	{
		pid = fork();
		if(pid > 0)//father
		{
			sleep(1);
			continue;
		}
		else if(pid == 0) //child
		{
			printf("NUM:%d  PID:%d\n",i,getpid());
			return 1;
		}
		else
		{
			printf("fork ERROR");
			exit(1);
		}

	}
	while(i--)
	{
		wait(NULL);
	}
	return 0;
}
