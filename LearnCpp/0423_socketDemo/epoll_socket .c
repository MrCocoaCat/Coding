
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
int main(int argc,char * argv[])
{
	return 0;
	int ret;
	int sock;
	struct sockaddr_in addr;
	char buf[1024];
	int len;
	int epoll_id;
	struct epoll_event event;
	struct epoll_event  ret_events[100];
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
		
	//监听
	//(监听的套接字，未连接的请求数量)
	ret=listen(sock,5); 
	if(ret==DEF_STD_ERROR)
	{
		printf("%s",strerror(errno));
		return -1;
	};
	
	//creat epoll
	epoll_id=epoll_create(100); //管理100个
	//promote sock to poll
	event.events=EPOLLIN|EPOLLERR|POLLRDHUP;
	epoll_ctl(epoll_id,EPOLL_CTL_ADD,sock,&events);
	
   //accept
   
	while(1)
	{
		//
		ret=epoll_wait(epoll_id,ret_event,100,10);
		if(ret==0)
		{
			usleep(10);
			continue;
		}
		else if(ret <0)
		{
			printf("%s",strerror(errno));
			break;
		}
		
		//deal
		for(i=0;i<ret;++i)
		{
			if(EPOLLIN&ret_event[i].events)
			{
				if(ret_events[i].date.fd==sock)
				{
					client=accept(sock,NULL,NULL);
					event.events=EPOLLIN|EPOLLERR|POLLRDHUP;
					epoll_ctl(epoll_id,EPOLL_CTL_ADD,client,&events);
				}
				else
				{
					recv(ret_events[i].date.fd,buf,sizeof(buf),0);
					printf("");
					event.events=EPOLLOUT;
					epoll_ctl(epoll_id,EPOLL_CTL_MOD,ret_events[i].date.fd,&events);
				}
			}
			else if(EPOLLOUT&ret_event[i].events)
			{
				send(ret.events[i].date.fd,buf,strlen(buf)+1,0);
				event.events=EPOLLIN|EPOLLERR|POLLRDHUP;
				epoll_ctl(epoll_id,EPOLL_CTL_MOD,ret_events[i].date.fd,&events);
			}
			memset(ret_events,sizeof(ret_events),0);
		}
		
		
	};
	close(sock);   
	return 0;
}





