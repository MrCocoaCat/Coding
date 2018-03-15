#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netdb.h>
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

struct thread_sock
{
	fd_set my_set;
	int my_count;
	int my_max;
	pthread_mutex_t my_mutex;
};

void* Select_thread(void *p)
{
	struct thread_sock *param  = (struct thread_sock*)p;
	fd_set read_set;
	struct timeval my_tv;
	int ret;
	int i;
	char szbuf[1024];
	my_tv.tv_sec = 0;
	my_tv.tv_usec = 10;
	while(1)
	{
		//zero read_set
		FD_ZERO(&read_set);
		//copy fd_set
		pthread_mutex_lock(&param->my_mutex);
		memcpy(&read_set, &param->my_set, sizeof(read_set));
		//select
		pthread_mutex_unlock(&param->my_mutex);
		ret = select(param->my_max + 1, &read_set, NULL, NULL, &my_tv);
		if(ret < 0)
		{
			printf("No user connect!\n");
			break;
		}
		else if(ret == 0)
		{
			usleep(10);
			continue;
		}
		else
		{
			for(i = param->my_max; i>2; --i)
			{
				if(FD_ISSET(i, &read_set) > 0)
				{
					recv(, szbuf, sizeof(szbuf)+1, 0);
					printf("Socket[%d]:%s\n", i, szbuf);
					send(i, szbuf, sizeof(szbuf), 0);
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
	char szbuf[1024];
	pthread_t thread;
	struct thread_sock p;
	FD_ZERO(&p.my_set);
	p.my_count = 0;
	p.my_max = 2;
	pthread_mutex_init(&p.my_mutex, NULL);
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
			printf("accept error [%s] \n", strerror(errno));
			break;
		}
		//let newsock join in fd_set
		p.my_max = p.my_max > newsock ? p.my_max : newsock;
		pthread_mutex_lock(&p.my_mutex);
		if(p.my_count < 1024)
		{
			FD_SET(newsock, &p.my_set);
			p.my_count++;
		}
		pthread_mutex_unlock(&p.my_mutex);
		if(p.my_count <= 1)
		{
			pthread_create(&thread, NULL, Select_thread, &p);
		}
	}
	
	pthread_join(thread, NULL);
	pthread_mutex_destroy(&p.my_mutex);
	close(sock);
	
	return 0;
}
