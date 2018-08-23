#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<errno.h>
int main(int argc,char * argv[])
{

	int fd;
	int len=1;
	char buf[1024]; 
	//	if(argc==2)
	//	{
	//		fd=open(argv[1],O_RDONLY);
	//		len=read(fd,buf,sizeof(buf));
	//		 write(STDOUT_FILENO,buf,len);
	//	}
	//	else


	fd=open("/dev/tty",O_RDONLY|O_NONBLOCK);
	while(1)
	{


		len=read(fd,buf,sizeof(buf));
		if(len==-1)
		{
			if(errno==EAGAIN)
			{
				printf("try again\n");
				sleep(1);
				continue;
			}
			else
			{
				break;
			}

		}
		write(STDOUT_FILENO,buf,len); 
	}
	close(fd);
	exit(1);
}
