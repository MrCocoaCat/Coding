#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
int  main(int argc,char* argv [])
{
	pid_t childpid;
	printf("1 %d\n",getpid());
	printf("2 %d\n",getppid());
	childpid=fork();
	if(childpid<0)
	{
		printf("erro");
	}
	else if(childpid==0)
	{

		printf("child\n");
		printf("3 %d\n",getpid());
		printf("4 %d\n",getppid());
		exit(0);
	}
	else
	{
		printf("sdsdsssds");
		sleep(2);
	}
	printf("5 %d\n",getpid());

	sleep(1);
	return 0;
}
