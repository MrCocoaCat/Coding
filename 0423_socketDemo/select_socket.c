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
	else  //������
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
		//�����
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
			if(FD_ISSET(i,&read_set)>0) //���������
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
	int count=0;//��¼����
	struct thread_param param;
	param.my_count=0;
	param.my_max=2;
	FD_ZERO(&param.my_set); //���
	pthread_mutex_init(&param.my_mutex,NULL); //����������
	pthread_t thread;  
	//�����׽���
	//(��AF_INET��ʾIPv4���׽������ͣ�SOCK_STREAM��ʾTCP��0��ʾѡ��Ĭ��Э��)
	sock=socket(AF_INET,SOCK_STREAM,0);
	if(sock==DEF_STD_ERROR) //�����ж�
	{
		return -1;
	}
	//��
	addr.sin_family =AF_INET;
	addr.sin_port=htons(1024);
	addr.sin_addr.s_addr=inet_addr("192.168.1.25");
	
	ret=bind(sock,&addr,sizeof(addr));  //�ɹ�����0��������-1
	if(ret==DEF_STD_ERROR){return -1};
	
	
	//���÷�����
	set_block( sock,0);	
	//����
	//(�������׽��֣�δ���ӵ���������)
	ret=listen(sock,5); 
	if(ret==DEF_STD_ERROR){return -1;};
	
   //����
   while(1)
   {
		ret=accept(sock,0,0);
		if(ret==DEF_STD_ERROR)
		{
			if(errno==EAGAIN)  //û���������һ�ᣬ
			{
				usleep(10);
				continue;
			}
			else
			{
				berak;
			}
		}
		//reacord socket,ÿ�θ������ֵ
		param.my_max=param.my>ret?param.my_max:ret;
	
		//add  to read_set
		pthread_mutex_lock(&param.my_mutex); //����
		if(param.my_count<1024)
		{
			FD_SET(ret,&param.my_set); //�����������뼯��
			param.my_count++;  //�����ڵ�������������1�����������������select �ĵ�һ������
		}
		// if it is first,creat thread
		if(param.my_count<=1) //���һ��û�У�����һ�Σ�����һ���߳�
		{
			pthread_creat(&thread,NULL,deal_thread,&param); //�����߳�
			
		}
		pthread_mutex_unlock(&param.my_mutex); //����
		
		
	};
   
   //wait child thread
   pthread_join(thread,NULL);
   //close
   close(sock);
   
	
}





