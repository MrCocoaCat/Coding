#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/unistd.h>
#include<errno.h>
#include<fcntl.h>
#include<wait.h>
int main(  int argc, char*argv[])
{

	int fds[2];
	int pid;
	if(pipe(fds)<0)
	{
		exit(-1);
	}
	pid=fork();
	if(pid>0)
	{
		close(fds[0]);
		char * str="test iii";
		sleep(5);
		write(fds[1],str,strlen(str));
		wait(NULL);
	}
	else if(pid==0)
	{
		char buf[1024];
		int len;
		int flag;
		close(fds[1]);
		flag=fcntl(fds[0],F_GETFL);
//		flag=flag|O_NONBLOCK;
		flag|=O_NONBLOCK;
		fcntl(fds[0],F_SETFD,flag);
try:
		len=read(fds[0],buf,sizeof(buf)); 
		if(len<0)
		{
			if(errno==EAGAIN)
			{
				printf("try again \n");
				sleep(1);
				goto try;
			}
			else{exit(-1);}
		}
		write(STDOUT_FILENO,buf,len);
	}
}
