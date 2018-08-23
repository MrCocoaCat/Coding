#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{

  int fd;
  int len;
  char buf[8*1024]; 
  fd=open("./open.c",O_RDONLY);
  if(fd<0)
  {
	printf("erro");
	exit(1);
  }
  len=read(fd,buf,sizeof(buf));
  if(len<0)
  {
	printf("erro");
    
  }
  write(STDOUT_FILENO,buf,len); 
  close(fd);
  exit(1);
}
