#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void do_sig_child(int signo)
{
	int status;
	pid_t pid;
	while ((pid = waitpid(0, &status, WNOHANG)) > 0)
	{
		if (WIFEXITED(status))
			printf("child %d exit %d\n", pid, WEXITSTATUS(status));
		else if (WIFSIGNALED(status))
			printf("child %d cancel signal %d\n", pid, WTERMSIG(status));
	}
}

int main(int argc,char * argv[])
{
	int pid;
	int i=0;
	for(i=0;i<10;i++)
	{
		pid=fork();
		if(pid==0)
		{
			break;
		}
		else if(pid<0)
		{
			perror("fork");
		}

	}	
	if(pid==0) //child
	{	
		int n=7;
		while(1)
		{
			printf("I'm chiled . pid[ %d] i[%d] \n",getpid(),i);
			sleep(4);
			n--;
		}
		return i;
	}
	else if(pid>0)//parent
	{
		struct sigaction act;
		act.sa_handler = do_sig_child;
		sigemptyset(&act.sa_mask);
		act.sa_flags = 0;
		sigaction(SIGCHLD, &act, NULL);
		while(1)
		{
			printf("I'm Father.my pid is %d\n",getpid());
			sleep(4);
		}
	}

	return 0;
}
