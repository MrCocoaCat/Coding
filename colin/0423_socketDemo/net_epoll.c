#define _GNU_SOURCE 1
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <pthread.h>
#include <sys/epoll.h>
#include <poll.h>
#ifndef TRUE
typedef int BOOL;
#define TRUE (1)
#define FALSE (0)
#endif

#define DEF_STD_ERROR (-1)
#define PORT (1234)
#define SERVER_IP ("192.168.1.211")


void Set_block(int sock, BOOL nflag)
{
	int ret;
	if(nflag == TRUE)
	{
		ret = fcntl(sock, F_GETFL);
		ret &= (~O_NONBLOCK);
		fcntl(sock, F_SETFL, ret);
	}
	else
	{
		ret = fcntl(sock, F_GETFL);
        ret |= O_NONBLOCK;
        fcntl(sock, F_SETFL, ret);
	}
}


int main(int argc, char* argv[])
{
	int sock;
	int newsock;
	int ret;
	struct sockaddr_in addr;
	int addr_len = sizeof(addr);
	int len;
	int epoll_id;
	int count = 0;
	struct epoll_event event;
	char buf[1024];
	struct epoll_event ret_events[100];
	int i;
	//1.create socket
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if(sock == DEF_STD_ERROR)
	{
		printf("create socket failed [%s]\n", strerror(errno));
		return -1;
	}
	
	//2.init address
	addr.sin_family = AF_INET;
	addr.sin_port = htons(PORT);
	addr.sin_addr.s_addr = inet_addr(SERVER_IP);
	//3.bind
	ret = bind(sock, (struct sockaddr *)&addr, sizeof(addr));
	if(ret == DEF_STD_ERROR)
    {
        printf("bind failed [%s]\n", strerror(errno));
		close(sock);
        return -1;
    }
	//4.listen
	ret = listen(sock, 5);
	if(ret == DEF_STD_ERROR)
    {
        printf("listen failed [%s]\n", strerror(errno));
		close(sock);
        return -1;
    }

	//create epoll
	epoll_id = epoll_create(100);
	event.events = EPOLLIN;
	event.data.fd = sock;
	epoll_ctl(epoll_id, EPOLL_CTL_ADD, sock, &event);
	printf("listen socket [%d]\n", sock);
	//6.accept
	while(1)
	{
		ret = epoll_wait(epoll_id, ret_events, 100, 10);	
		if(ret == 0)
		{
			usleep(10);
			continue;
		}
		else if(ret <0)
		{
			printf("[%s]\n",strerror(errno));
			break;
		}

		for(i = 0; i < ret; ++i)
		{
			if(EPOLLERR & ret_events[i].events)
			{
				epoll_ctl(epoll_id, EPOLL_CTL_DEL, ret_events[i].data.fd, NULL);
				close(ret_events[i].data.fd);
				printf("clinet:[%d] force quit\n", ret_events[i].data.fd);
			}
			else if(EPOLLRDHUP & ret_events[i].events)
			{
				epoll_ctl(epoll_id, EPOLL_CTL_DEL, ret_events[i].data.fd, NULL);
                close(ret_events[i].data.fd);
                printf("clinet:[%d] gracefully quit\n", ret_events[i].data.fd);
			}
			else if(EPOLLIN & ret_events[i].events)
			{
				if(ret_events[i].data.fd == sock)
				{
					newsock = accept(sock, NULL, NULL);
					event.events = EPOLLIN | EPOLLERR | EPOLLRDHUP | EPOLLET;
					event.data.fd = newsock;
					epoll_ctl(epoll_id, EPOLL_CTL_ADD, newsock, &event);
				}
				else
				{
					memset(buf, 0, sizeof(buf));
					recv(ret_events[i].data.fd, buf, sizeof(buf), 0);
					printf("client[%d]: %s", ret_events[i].data.fd, buf);
					event.events = EPOLLOUT;
					event.data.fd = ret_events[i].data.fd;
					epoll_ctl(epoll_id, EPOLL_CTL_MOD, ret_events[i].data.fd, &event);
				}
			}
			else if(EPOLLOUT & ret_events[i].events)
			{
				send(ret_events[i].data.fd, buf, strlen(buf)+1, 0);
				event.events = EPOLLIN | EPOLLERR | EPOLLRDHUP | EPOLLET;
				event.data.fd = ret_events[i].data.fd;
				epoll_ctl(epoll_id, EPOLL_CTL_MOD, ret_events[i].data.fd, &event);
			}
		}
		memset(ret_events, 0, sizeof(ret_events));
	}
	close(sock);
	
	return 0;
}
