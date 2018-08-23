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
#include<poll.h>

/****************
  @author:liyubo
  @time:2017.08.24
 ******************/
struct thread_param
{
	int m_count;
	struct pollfd fds[2000];
	pthread_mutex_t m_mutex;
};
void  set_block(int sock,int flag)
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
void *deal_thread (void *param)
{
	struct thread_param *p = (struct thread_param *)param;
	fd_set temp_set;
	int ret;
	int i,j=0;
	char buf[1024];
	while(1)
	{
		//poll
		ret = poll(p->fds,p->m_count,10);
		//judge
		if(ret < 0 )
		{
			perror("selecti" );
			break;
		}
		else if( ret == 0)//待超时；2:每次真正处理之前都要continue好多次，浪费。recv之前否continue了，如果连续发还没有直接recv高
		{
			sleep(1);
			continue;
		}
		//check
		for(i = 0;i < p->m_count; ++i) //
		{
			if( POLLERR & p->fds[i].revents)//出错,捕获对端退出，强制关闭
			{
				//delete client
				pthread_mutex_lock(&p->m_mutex);
				close(p->fds[i].fd);
				printf("client:force :[%d] quite!\n",p->fds[i].fd);
				p->fds[i] = p->fds[p->m_count];				
				pthread_mutex_unlock(&p->m_mutex);
			}
			if( POLLHUP & p->fds[i].revents)//主动关闭，close socket
			{
				//delete client
				pthread_mutex_lock(&p->m_mutex);
				close(p->fds[i].fd);
				printf("client:hup :[%d] quite!\n",p->fds[i].fd);
				p->fds[i] = p->fds[--p->m_count];				
				pthread_mutex_unlock(&p->m_mutex);
			}
			else if(POLLIN & p->fds[i].revents)
			{
				//recv
				recv (p->fds[i].fd,buf,sizeof(buf),0);
				printf("client:[%d] : %s \n",p->fds[i].fd,buf);
				p->fds[i].events = POLLOUT;
			}
			else if(POLLOUT & p->fds[i].revents)
			{
				//sned
				send(p->fds[i].fd,buf,strlen(buf)+1,0);
				p->fds[i].events = POLLIN|POLLERR|POLLHUP;
			}
		}	
	}
}
int main()
{
	int ret;
	int sock;
	int len;
	char buf[1024];
	pthread_t tid;
	int count =0;
	int fd;
	struct sockaddr_in addr;
	struct thread_param param;
	param.m_count = 0;
	pthread_mutex_init(&param.m_mutex,NULL);//init pthread_mutex_t
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
	while(1)
	{
		fd = accept(sock,NULL,NULL);//阻塞到有一个链接到来
		if(fd == -1)
		{
			if(errno == EAGAIN)
			{
				//printf("yibu...\n");
				sleep(1);
				continue;
			}
			else
			{
				perror("accept");
				close(sock);
				return -1;
			}
		}

		pthread_mutex_lock(&param.m_mutex);
		//fill once socket
		if(param.m_count < 2000)
		{
			param.fds[param.m_count].fd = fd;
			param.fds[param.m_count].events = POLLIN|POLLERR|POLLHUP;//POLLIN关心是否可以读，POLLERR关心是否出错
			param.m_count++;
		}
		//if frist ,creat pthread
		if(param.m_count <= 1)
		{
			pthread_create(&tid,NULL,deal_thread,&param);
			//处理结束后需要删除
		}
		pthread_mutex_unlock(&param.m_mutex);

	}
	//wait
	pthread_join(tid,NULL);
	pthread_mutex_destroy(&param.m_mutex);
	//close
	close(sock);
	return 0;
}
