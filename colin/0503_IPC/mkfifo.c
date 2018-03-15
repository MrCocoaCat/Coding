#include<stdio.h>
#include<errno.h>
#include<sys/unistd.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

int main(int argc,char * argv[])
{
	int pd;
	int ret;
	int len;
	char str[1024];
	char str2[1024];
	if(atoi(argv[1])>0)	
	{

		ret=mkfifo("./FIFO",S_IWUSR|S_IRUSR);
		if(ret<0)
		{
			if(errno==EEXIST)
			{
				printf("FIFO exit");
			}
			else
			{
				return -1;
			}

		}

		pd=open("./FIFO",O_WRONLY);
		if(pd<0)
		{
			printf("%s",strerror(errno));
			unlink("./FIFO");
			return -1;
		}
		while(1)
		{
			printf("please inpute:   ");
			scanf("%s",str);
			write(pd,str,strlen(str)+1);
		}
		close(pd);
	}
	else
	{
		ret=access("./FIFO",W_OK);
		if(ret==-1)
		{
			printf("%s\n",strerror(errno));
			return -1;
		}
		pd=open("./FIFO",O_RDONLY);

		while(1)
		{

			len=read(pd,str2,sizeof(str2));
			//write(STDOUT_FILENO,str2,len);
			printf("receive date:%s\n",str2);



		}
		close(pd);
	}

	return 0;
}

