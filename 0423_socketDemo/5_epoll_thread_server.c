#define _GNU_SOURCE 1
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
#include<pthread.h>
#include<sys/epoll.h>
#include<poll.h>

/****************
  @author:liyubo
  @time:2017.08.24
 ******************/
int main()
{
	int ret;
	int sock;
	int len;
	char buf[1024];
	int clientfd;
	struct sockaddr_in addr;
	int i;     
   	int epoll_id;
	struct epoll_event ep_event;
	struct epoll_event ret_events[100];
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
	//creat epoll
	epoll_id=epoll_create(100);//管理100个

	//promote sock to epoll
/**************************************************************
	EPOLL_CTL_ADD 注册新的fd到epfd中
	EPOLL_CTL_MOD 修改已经注册的fd的监听事件
	EPOLL_CTL_DEL 从epfd中删除一个fd
***************************************************************/
//	ep_event.events = EPOLLIN | EPOLLET; //ET模式，不重复通知 
	ep_event.events = EPOLLIN;
	epoll_ctl(epoll_id,EPOLL_CTL_ADD,sock,&ep_event);
	//accept
	while(1)
	{
		//wait epoll
		ret = epoll_wait(epoll_id,ret_events,100,10);//等该，结果放入ret_eventsi,等100个，10毫秒;返回要处理的事件个数，如果为0,则超时
		if(ret == 0)
		{
			usleep(10);
			continue;
		}
		else if( ret < 0)
		{
			perror("epoll");
		}
		for( i = 0; i < ret; ++i)
		{
			if(EPOLLIN & ret_events[i].events)
			{
				if(ret_events[i].data.fd == sock)
				{
					//accept
					clientfd = accept(sock,NULL,NULL);
					ep_event.events = EPOLLIN | EPOLLERR | POLLHUP;
					epoll_ctl(epoll_id,EPOLL_CTL_ADD,clientfd,&ep_event);//添加
				}	
				else
				{
					recv(ret_events[i].data.fd,buf,sizeof(buf),0);
					printf("client :[%d] %s",ret_events[i].data.fd , buf);
					fflush(NULL);
					ep_event.events = EPOLLOUT;
					epoll_ctl(epoll_id,EPOLL_CTL_MOD,ret_events[i].data.fd,&ep_event);
				}
			}
			if(EPOLLOUT & ret_events[i].events)
			{
				send(ret_events[i].data.fd,buf,strlen(buf)+1,0);
				ep_event.events = EPOLLIN | EPOLLERR | POLLHUP;
				epoll_ctl(epoll_id,EPOLL_CTL_MOD,ret_events[i].data.fd,&ep_event);
				
			}
		}
	}
	//close
	close(sock);
	return 0;
}
