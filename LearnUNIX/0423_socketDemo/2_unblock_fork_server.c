#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<netdb.h>
#include<wait.h>
//set socket
/****************
  @author:liyubo
  @time:2017.08.23
 ******************/
void set_block(int sock,int flag)
{
	int ret; 
	if(flag == 1)
	{
		ret = fcntl(sock,F_GETFL);
		ret &= (~O_NONBLOCK);
		fcntl(sock,F_SETFL,ret);
	}
	else
	{
		ret = fcntl(sock,F_GETFL);
		ret |= O_NONBLOCK;
		fcntl(sock,F_SETFL,ret);
	}
}
int main()
{
	int ret;
	int sock;
	int len;
	char buf[1024];
	struct sockaddr_in addr;
	//create socket
	sock = socket(AF_INET,SOCK_STREAM,0);
	if( -1 == sock)
	{
		perror("creat");
		return -1;
	}
	//init address
	addr.sin_family = AF_INET;
	addr.sin_port = htons(10240);//主机字节序转网络字节序
	//addr.sin_addr.s_addr = inet_addr("192.168.");
	addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//bind

	ret = bind(sock,(struct sockaddr *)&addr,sizeof(addr));
	if(ret == -1)
	{
		perror("bind");
		close(sock);
		return -1;
	}
	//listen

	ret = listen(sock , 5);
	if(-1 == ret)
	{
		perror("ret");
		close(sock);	
		return -1;
	}
	//set noblock
	set_block(sock,0);
	//accept
	while(1)//管理多练接时，用这个大循环
	{
		ret = accept(sock,NULL,NULL);
		if(ret == -1)
		{
			if(errno == EAGAIN)
			{
				//	printf("yibu...\n");
				usleep(1);
				continue;
			}
			else
			{
				perror("accept");
				close(sock);
				return -1;
			}
		}
		
		//creat child
		pid_t pdchild;
		pdchild=fork();
		if(pdchild < 0)
		{	
			//创建失败
			//send(ret,"creating child",sizeof("creating child"),0);
			//close(ret);
			perror("creat child");
			continue;
		}
		else if (pdchild == 0)
		{
			//子进程
			// 避免僵尸进程，再fork,变孤儿
			pdchild = fork();
			if(pdchild == 0 )
			{
				//子进程的子进程
				while(1)
				{
					set_block(ret,0);
					len = recv(ret,buf,sizeof(buf),0);
					if(len == -1)
					{

						if(errno == EAGAIN)
						{
							sleep(1);
							continue;
						}
						else
						{
							perror("recv: ");
							break;
						}
					}
					else if(len == 0)
					{
						printf("对段正常退出");
						break;
					}
					else
					{
						printf("sock:[%d]:%s\n",ret,buf);
						send(ret,buf,strlen(buf)+1,0);
					}
				}
				close(sock);
				close(ret);
				exit(0);
			}
			else if(pdchild > 0 )
			{
				//子进程本身，退出,使子进程的子进程变孤儿进程
				//close(ret);
				//close(sock);
				exit(0);
			}
		}
		else
		{
			//父进程
			wait(NULL);
			//waitpid(pdchild,0,0);
			//	close(ret);
		}
	}
	//close
	close(sock);
	return 0;
}
