#include<stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd;
	fd=open("test_file",O_CREAT|,0664);
	printf("%d",fd);
}
