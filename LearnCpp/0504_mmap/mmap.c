#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<unistd.h>
//#include<sys.types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
typedef struct MST
{
	int id;
	char name[20];
	char sex;
}ST;
int main(int argc,char* argv[])
{
	int fd;
	int len=0x1000;
	int i=0;
	//int * p;
	ST *p; 
	if(atoi(argv[1])<1)
	{
		fd=open("./temp",O_CREAT|O_RDWR,0664);
		if(fd==-1)
		{
			perror("open error is");

		}
		if(lseek(fd,len-1,SEEK_SET)<0)
		{
			perror("lseek error is");
		}	
		if(write(fd,"\0",1)<0)
		{
			perror("writen error is ");
		}
		p=mmap(NULL,len ,PROT_READ| PROT_WRITE, MAP_SHARED,fd,0);
		close(fd);
		while(1)
		{
			p->id=i;
			sprintf(p->name,"aaa-%d",i);
			if(i%3==0)
			{
				p->sex='M';
			}
			else
			{
				p->sex='F';
			}
			i++;
			sleep(1);
		}
		munmap(p,len);

	}
	else
	{
		fd=open("./temp",O_RDWR);
		if(fd==-1)
		{
			perror("open error is");
		}	
		p=mmap(NULL, len, PROT_WRITE|PROT_READ, MAP_SHARED,fd, 0);
		close(fd);
		unlink("./temp");
		while(1)
		{	

			//	write(STDOUT_FILE,)
			printf("ID:%d \n NAMR: %s\n SEX:%c\n",p->id,p->name,p->sex);
			sleep(1);

		}
	}







}
