#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<signal.h>
#include<string.h>
#include<errno.h>
int main()
{

	pid_t child;
	signal(SIGINT,SIG_IGN);
	while(1)
	{
		printf("qqqn");
	//	sleep(1);
	}
	//child=fork();
	if(child<0)
	{
		printf("error");
	}
	else if(child==0)
	{
		printf("child %d parent %d runing \n", getpid(),getppid());
		exit(0);
	}
	else
	{
	//	wait();
		//while(1)
		//{
		sleep(1);
		printf("i am %d", getpid());
		//}
	}
	return 0;

}


