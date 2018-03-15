#include<stdio.h>
#include<unistd.h>
#include<signal.h>
#include<errno.h>
int main()
{
	int n=0;
	int ret=0;
	int i=0;
	sigset_t set;

	ret=sigemptyset(&set);
	if(ret==-1)
	{
		perror("sigemptyset");
	}
	ret=sigaddset(&set,SIGINT);
	if(ret==-1)
	{
		perror("sigaddset");
	}
	ret=sigprocmask(SIG_BLOCK,&set,NULL);
	if(ret==-1)
	{
		perror("sigprocmask");
	}
	//alarm(4);
	sigset_t pset;
	while(1)
	{
		
		sigpending(&pset);
		for(i=1;i<32;i++)
		{
			if(sigismember(&pset,i)==1)
			{
				putchar('1');
			}
			else
			{
				putchar('0');
			}
			//printf("%d    ",n);
			n++;
		}
		sleep(1);
		printf("\n");
	}
	sigdelset(&set,SIGINT);
	sigprocmask(SIG_BLOCK,&set,NULL);
	return 0;
}
