#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>

void str_error(char *err_str,int err_no)
{
		perror(err_str);
		exit(err_no);
}

//需要源文件路径、目标文件路径、想要的进程数
int main(int argc,char * argv[])
{		
		int process;
		if(argc < 3)
		{
				str_error("./apk SrcFileName DesFileName",1);
		}
		if(argv[4] != NULL)
				process = atoi(argv[4]);
		else
				process = 3;

		int blocksize = 0;
		int pos = 0;

		int FileSize = 0;
		int fd;
		if((fd = open(argv[1],O_RDONLY)) < 0)
		{
				str_error("open ERROR",1);
		}
		FileSize = lseek(fd,0,SEEK_END); 

		close(fd);
		if(FileSize % process == 0)
		{
				blocksize = FileSize / process;
		}
		else
		{
				blocksize = FileSize / process + 1;
		}
		//创建进程
		pid_t pid;
		int i = 0;
		for(i = 0 ; i < process ; i++)
		{
				pid = fork();
				if(pid > 0)
				{
						pos = pos + blocksize;
				}
				else if(pid == 0)
				{
						break;
				}
				else
				{
						str_error("fork ERROR",1);
				}
		}
		char BlockSize[100];
		char Pos[100];
		sprintf(BlockSize,"%d",blocksize);
		sprintf(Pos,"%d",pos);
		if(pid == 0)
		{
				execl("./app","app",argv[1],argv[2],BlockSize,Pos,NULL);
		}
		return 0;
}
