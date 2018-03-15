#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/unistd.h>
int main()
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
write(fds[1],str,strlen(str));
}
else if(pid==0)
{
char buf[1024];
int len;
close(fds[1]);
len=read(fds[0],buf,sizeof(buf));
write(STDOUT_FILENO,buf,len);
}
}
