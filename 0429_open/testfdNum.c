#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
int main()
{

  int fd=0;
  char  name[20];  
  int poit=0;
  while(fd!=-1)
 {
 // itoa(fd,name);
 
  fd=open(name,O_RDWR|O_CREAT,0664);
 
 }  
  exit(1);
}
