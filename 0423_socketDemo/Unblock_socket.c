/*��������
 ���� nc����  ����
 
 nc -l �Ƿ�����
 nc �ǿͻ���
*/
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<fcntl.h>
#include<netdb.h>

#define DEF_STD_ERROR (-1) //��׼�����


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



int main(int argc,char * argv[])
{
	return 0;
	int ret;
	int sock;
	struct sockaddr_in addr;
	char buf[1024];
	int len;
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
			if(errno==EAGAIN)  //û���������һ��
			{
				usleep(10);
				continue;
			}
			else
			{
				berak;
			}
		}	
		child=fork();  //��������
		
		if(child<0) //���ִ���
		{
			send(ret,"busy",sizeof("busy"),0);
			close(ret);
		}
		else if(child==0) //�ӽ��̴�������
		{ 
			child = fork(); //fork���η�ֹ���ֽ���
			if(child==0)//�ӽ���,Ҳ�������ӽ���
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
					else if(len==0) //δ�յ�����
					{
						break;
					}
					//�յ�����
					printf("sock%d:%s\n",ret,buf);
					send(ret,buf,stlen(buf)+1,0);
				}
				close(ret);
				exit(0);
			}
			else if (chile >0) //������
			{
				//�����Ƴ�
				close(ret);
				close(sock);
				exit(0);
			}
		}
		else  //������
		{
			waitpid(chile,0,0);
			close(ret);
		}
	};
   
   
   
   
	
}





