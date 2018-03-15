#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char * argv[])
{

	int fd;
	int len;
	char buf[1024]; 
	if(argc==2)
	{
		fd=open(argv[1],O_RDONLY);
		len=read(fd,buf,sizeof(buf));
		 write(STDOUT_FILENO,buf,len);
	}
	else
	{
	while(1)
	{
		len=read(STDIN_FILENO,buf,sizeof(buf));
		if(len<0)
		{
			printf("erro");

		}
		write(STDOUT_FILENO,buf,len); 
	}
        }
	close(fd);
	exit(1);
}
