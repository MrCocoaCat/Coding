#include<unistd.h>
#include<stdio.h>
#include<ctype.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<fcntl.h>

#define PORT 8000
#define LISTENNUM 128
/* 这个模型只能连接一个，因为连接时阻塞了*/

void set_block(int sock,int flag)
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
int main()
{
	int serverfd,clientfd;
	int len;
	struct sockaddr_in serveraddr, clientaddr;
	char ipbuf[32];
	char buf[0x1000];

	//init serveraddr
	bzero(&serveraddr,sizeof(serveraddr));

	//creat socket	
	serverfd=socket(AF_INET,SOCK_STREAM,0);

	//构造serveraddr
	serveraddr.sin_family=AF_INET;
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	serveraddr.sin_port=htons(PORT);

	//bind
	bind(serverfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

	//listen
	listen(serverfd,LISTENNUM);

//        set_block(serverfd,0);
	//accept
	while(1)
	{
		int clientsize = sizeof(clientaddr);
		clientfd = accept(serverfd,(struct sockaddr *)&clientaddr,&clientsize);
		//核心工作
		printf("client IP : %s\t client PORT:%d\n",inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ipbuf,sizeof(ipbuf)),ntohs(clientaddr.sin_port));
		while(len=read(clientfd,buf,sizeof(buf)))
		{
			int i=0;
			while(i<len)
			{
				buf[i]=toupper(buf[i]);
				i++;
			}
			write(clientfd,buf,len);
		};
	}
	//close client_sockiet
	close(clientfd);
	close(serverfd);
	
}
 //htonl()
//h 表示host n表示network  l表示32 s表示short
