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

//set socket
/****************
  @author:liyubo
  @time:2017.08.24
 ******************/
struct thread_param
{
	fd_set m_set;
	int m_count;
	int m_max;
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

	struct timeval my_tv;
	my_tv.tv_sec = 0;
	my_tv.tv_usec = 10;
	int i;
	while(1)
	{
		//clear

		FD_ZERO(&temp_set);//初始化set
		//fill
		pthread_mutex_lock(&p->m_mutex);
		memcpy(&temp_set,&p->m_set,sizeof(temp_set));//1:拷贝到临时集合,I/O操作频繁
		//select
		pthread_mutex_unlock(&p->m_mutex);
		ret = select(p->m_max+1,&temp_set,NULL,NULL,&my_tv);//3：为防止select时用户操作setjihe,检测时会拷贝到内核一份,造成浪费
		//judge
		if(ret < 0 )
		{
			perror("selecti" );
			break;
		}
		else if( ret == 0)//等待超时；2:每次真正处理之前都要continue好多次，浪费。recv之前否continue了，如果连续发还没有直接recv高
		{
			sleep(1);
			continue;
		}
		//check
		for(i = p->m_max;i > 2;--i) //4:每次都要检测，需要重复检测所有集合,如果处理了也要重复检测。
		{
			if( FD_ISSET(i,&temp_set) >0)
			{
				printf("sock[%d]:\n",i);//6:没有记录上一次检测结构，所以重复检测。反复通知
				sleep(1);
				//处理，处理后关闭

			}
		}	
		//5：文件描述符限制，最多只能管理1024个
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
	param.m_max = 2;
	FD_ZERO(&param.m_set);//init fd_set
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
//				printf("yibu...\n");
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
		//add to read_set	
		if(param.m_count < 1024)
		{
			printf("%d",fd);
			FD_SET(fd,&param.m_set);//添加set
			param.m_count++;
		}
		param.m_max = param.m_max > fd ? param.m_max:fd;
		//if frist ,creat pthread
		if(param.m_count <= 1)
		{
			pthread_create(&tid,NULL,deal_thread,&param);//
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
