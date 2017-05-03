#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{

	int fd;

	fd=open("./test",O_RDWR,0664);
	if(fd<0)
	{
		perror("");
	}
	exit(1);
}
