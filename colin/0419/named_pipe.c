#include<stdio.h>
#include<sys/types.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
int main(int argc,char * argv[])
{
int ret;
//if argv>0,witer
ret=mkfifo("./FIFO",S_IWUSR|S_IRUSR);
if(ret==-1)
{
if(errno==EEXIST)
{
printf("FIFO always exit");

}
}
}


//if argv[1]<0,read




return 0;
}
