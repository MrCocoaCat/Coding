#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

void str_error(char *err_str,int err_no)
{
		perror(err_str);
		exit(err_no);
}

//需要源文件路径、目标文件路径、块大小、读写指针位置
int main(int argc,char *argv[])
{	
		if(argc < 5)
		{	
				printf("need src des blocksize pos\n");
				exit(1);
		}

		int fd_src = open(argv[1],O_RDONLY);
		if(fd_src < 0)
				str_error("src open ERROR",1);
		int fd_des = open(argv[2],O_WRONLY | O_CREAT,0664);
		if(fd_des < 0)
				str_error("des open ERROR",1);
		
		lseek(fd_src,atoi(argv[4]),SEEK_SET);
		lseek(fd_des,atoi(argv[4]),SEEK_SET);
		
		char buf[atoi(argv[3])];
		int read_len;
		while( (read_len = read(fd_src,buf,atoi(argv[3]))))
		{
				write(fd_des,buf,read_len);
		}
		return 0;
}
