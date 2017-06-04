#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<netdb.h>
#include<pthread.h>
#define DEF_STD_ERROR (-1) //erro 


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

struct thread_param
{
	fd_set my_set;
	int my_count;
	pthread_mutex_t my_mutex;
	int my_max;
}
void * deal_thread(void * param )
{
	struct thread_param *p=(truct thread_param *)param;
	fd_set read_set;
	int ret;
	struct timeval my_tv;
	my_tv.tv_sec=0;
	my_tv.tv_usec=0;
	int i;
	while(1)
	{
		//clear
		FD_ZERO(&read_set);
		pthread_mutex_lock(&p->my_mutex);
		//fill
		memcpy(&read_set,p->my_set,(sizeof(read_set)));
		//select
		//最大检查
		ret=select(p->my_max+1,&read_set,NULL,NULL);
		pthread_mutex_unlock(&p->my_mutex);
		if(ret<0)
		{
			printf("erro");
			break;
		}
		else if()
		{
			usleep(10);
			continue;
		}
		//check
		for(i=p->my_max-1;i>2;--i)
		{
			if(FD_ISSET(i,&read_set)>0) //如果有数据
			{
				
				recv(i, szbuf, sizeof(szbuf)+1, 0);
				printf("Socket[%d]:%s\n", i, szbuf);
				send(i, szbuf, sizeof(szbuf), 0);
				
				sleep(1);
			}
		}
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
	fd_set read_set; 
	int count=0;//记录数量
	struct thread_param param;
	param.my_count=0;
	param.my_max=2;
	FD_ZERO(&param.my_set); //清空
	pthread_mutex_init(&param.my_mutex,NULL); //建立互斥量
	pthread_t thread;  
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
			if(errno==EAGAIN)  //没有请求，则等一会，
			{
				usleep(10);
				continue;
			}
			else
			{
				berak;
			}
		}
		//reacord socket,每次更新最大值
		param.my_max=param.my>ret?param.my_max:ret;
	
		//add  to read_set
		pthread_mutex_lock(&param.my_mutex); //枷锁
		if(param.my_count<1024)
		{
			FD_SET(ret,&param.my_set); //将描述符加入集合
			param.my_count++;  //集合内的描述符数量加1，用这个变量来控制select 的第一个参数
		}
		// if it is first,creat thread
		if(param.my_count<=1) //如果一个没有，即第一次，创建一个线程
		{
			pthread_creat(&thread,NULL,deal_thread,&param); //创建线程
			
		}
		pthread_mutex_unlock(&param.my_mutex); //解锁
		
		
	};
   
   //wait child thread
   pthread_join(thread,NULL);
   //close
   close(sock);
   
	
}





