#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{

	pid_t child;
	int fd[2];
	int iRead;
	int iWrite;

	//creat pipe
	pipe(fd);
	child=fork();
	if(child==0)
	{
		close(fd[1]);
		while(1)
		{
			read(fd[0],&iWrite,sizeof(iWrite));//fd[0]
			printf("iWrite : %d\n",iWrite);
		}
		close(fd[0]);
		exit(0);	

	}
	else
	{
		close(fd[0]);
		while(1)
		{
			printf("please input");
			scanf("%d",&iRead);
			write(fd[1],&iRead,sizeof(iRead));	
		}

		close(fd[1]);
	}
	return 0;
}
