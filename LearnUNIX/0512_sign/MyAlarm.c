#include<stdio.h>
#include<stdlib.h>
#include<signal.h>
#include<unistd.h>
void sigaction_fun()
{
}
unsigned int mysleep(unsigned int n)
{
	int unsleep;
	sigset_t newset,oldset,sigsuset;
	sigemptyset(&newset);
	sigaddset(&newset,SIGALRM);
	sigprocmask(SIG_BLOCK,&newset,&oldset);
	alarm(n);
	sigsuset=oldset;
	
	sigdelset(&sigsuset,SIGALRM);
	sigsuspend(&sigsuset);
	//pause();
	unsleep=alarm(0);


}
int main(int argc,char * argv[])
{
	struct sigaction act;
	act.sa_handler=sigaction_fun;
	sigemptyset(&act.sa_mask);
	act.sa_flags=0;
	sigaction(SIGALRM,&act,NULL);
	
	while(1)
	{
		mysleep(2);
		printf("hello\n");
	}
}
