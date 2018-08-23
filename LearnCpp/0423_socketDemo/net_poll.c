#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <poll.h>
#include <pthread.h>

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

struct thread_param
{
	struct pollfd my_poll[2000];
	int my_count;
	pthread_mutex_t my_mutex;
};

void* Poll_thread(void * p)
{
	struct thread_param* param = (struct thread_param*)p;
	int ret;
	char buf[1024];
	int i;
	while(1)
	{
		ret = poll(param->my_poll, param->my_count+1, 10);
		if(ret < 0)
		{
			printf("[%s]\n", strerror(errno));
			break;
		}
		else if(ret == 0)
		{
			usleep(10);
			continue;
		}
		else if(ret > 0)
		{
			for(i = 0; i < param->my_count; ++i)
			{
				if(param->my_poll[i].revents & POLLERR)
				{
					printf("clinet[%d] sock:[%d]quit\n", i, param->my_poll[i].fd);
					close(param->my_poll[i].fd);
					param->my_poll[i].fd = param->my_poll[--(param->my_count)].fd;
					param->my_poll[i].events = POLLIN | POLLERR | POLLHUP;
				}
				else if(param->my_poll[i].revents & POLLHUP)
				{
					printf("clinet[%d] sock:[%d] gracefully quit\n", i, param->my_poll[i].fd);
                    close(param->my_poll[i].fd);
                    param->my_poll[i].fd = param->my_poll[--(param->my_count)].fd;
                    param->my_poll[i].events = POLLIN | POLLERR | POLLHUP;
				}
				else if(param->my_poll[i].revents & POLLIN)
				{
					recv(param->my_poll[i].fd, buf, sizeof(buf)+1, 0);
					printf("sock[%d]:%s\n", param->my_poll[i].fd, buf);
					param->my_poll[i].events = POLLOUT;
				}
				else if(param->my_poll[i].revents & POLLOUT)
				{
					send(param->my_poll[i].fd, buf, strlen(buf)+1, 0);
					param->my_poll[i].events = POLLIN | POLLERR | POLLHUP;
				}
			}
		}
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
	pthread_t thread;
	struct thread_param tp;
	tp.my_count = 0;
	pthread_mutex_init(&tp.my_mutex, NULL);
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
	//5.set noblock	
	Set_block(sock, FALSE);
	//6.accept
	while(1)
	{
		newsock = accept(sock, 0 , 0);
		if(newsock == DEF_STD_ERROR)
		{
			if(errno == EAGAIN)
			{
				usleep(10);
				continue;
			}
			else
			{
				printf("accept failed [%s]\n", strerror(errno));
				break;
			}
		}
		if(tp.my_count < 2000)
		{
			tp.my_poll[tp.my_count].fd = newsock;
			tp.my_poll[tp.my_count].events = POLLIN | POLLERR | POLLHUP;
			tp.my_count++;
		}
		if(tp.my_count == 1)
		{
			ret = pthread_create(&thread, NULL, Poll_thread, &tp);
			if(ret != 0)
			{
				printf("create pthread failed [&s]\n", strerror(errno));
				break;
			}
		}
		
	}

	pthread_join(thread, NULL);
	pthread_mutex_destroy(&tp.my_mutex);
	close(sock);
	
	return 0;
}
