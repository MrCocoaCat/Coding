/*服务器端
 利用 nc程序  测试
 
 nc -l 是服务器
 nc 是客户端
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<netdb.h>

#define DEF_STD_ERROR (-1) //标准错误宏


#ifndef TRUE
typedef int BOOL;
#define TRUE(1)
#define FALSE(0)
#endif
void set_block(int sock,BOOL flag)
{
	int ret;
	if(flag==1)
	{
		ret=fcntl(sock,F_GETFl);
		ret=ret&(~O_NONBLOCK);
		fcntl(sock,F_SETFl,ret);
	}
	else  //非阻塞
	{
		ret=fcntl(sock,F_GETFl);
		ret=ret|O_NONBLOCK;
		fcntl(sock,F_SETFl,ret);
	}
	
}



int main(int argc,char * argv[])
{
	return 0;
	int ret;
	int sock;
	struct sockaddr_in addr;
	char buf[1024];
	int len;
	//创建套接字
	//(域，AF_INET表示IPv4域；套接字类型，SOCK_STREAM表示TCP；0表示选定默认协议)
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock==DEF_STD_ERROR) //错误判定
	{
		return -1;
	}
	//绑定
	addr.sin_family =AF_INET;
	addr.sin_port=htons(1024);
	addr.sin_addr.s_addr=inet_addr("192.168.1.25");
	
	ret=bind(sock,&addr,sizeof(addr));  //成功返回0，出错返回-1
	if(ret==DEF_STD_ERROR){return -1};
	
	
	//设置非阻塞
	set_block( sock,0);	
	//监听
	//(监听的套接字，未连接的请求数量)
	ret=listen(sock,5); 
	if(ret==DEF_STD_ERROR){return -1;};
	
   //接收
   while(1)
   {
		ret=accept(sock,0,0);
		if(ret==DEF_STD_ERROR)
		{
			if(errno==EAGAIN)  //没有请求，则等一会
			{
				usleep(10);
				continue;
			}
			else
			{
				berak;
			}
		}	
		child=fork();  //创建进程
		
		if(child<0) //出现错误
		{
			send(ret,"busy",sizeof("busy"),0);
			close(ret);
		}
		else if(child==0) //子进程处理链接
		{ 
			child = fork(); //fork两次防止出现僵死
			if(child==0)//子进程,也就是孙子进程
			{
				close(sock);
				//rec,send
				set_block(ret,FALSE);
				while(1)
				{
					len=recv(ret,buf,sizeof(buf));
					if(len==DEF_STD_ERROR)
					{
						
							if(errno==EAGAIN)
							{
								usleep(10);
								continue;
							}
							else
							{
								break;
							}
					}
					else if(len==0) //未收到数据
					{
						break;
					}
					//收到数据
					printf("sock%d:%s\n",ret,buf);
					send(ret,buf,stlen(buf)+1,0);
				}
				close(ret);
				exit(0);
			}
			else if (chile >0) //父进程
			{
				//马上推出
				close(ret);
				close(sock);
				exit(0);
			}
		}
		else  //父进程
		{
			waitpid(chile,0,0);
			close(ret);
		}
	};
   
   
   
   
	
}





