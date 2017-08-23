#includ<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/sypes.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<string.h>
#include<string.h>

#define PORT 8000
#define LISTENNUM 128

int main()
{
	int socketfd;
	int len;
	struct sockaddr_in serveraddr ;
	char ipbuf[32];
	char buf[0x1000];
	//init serveraddr
	bzero(&serveraddr,sizeof(serveraddr));
	//creat socket
	clientfd=socket(AF_INET,SOCKET_TREAM,0);
	//构造serveraddr
	serveraddr.family=AF_INRT;
	serveraddr.sin_addr.s_addr=htonl(INADDR_ANY);
	serveraddr.sin_port=htons(PORT)
	//bind
	bind(socketfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
	//listen
	listen(socketfd,LISTENNUM);
	//accept
	while(1)
	{
		clientsize = sizeof(clientaddr);
		clientfd=accept(socketfd,(struct sockaddr *)&clientaddr,&clientsize);
		//核心工作
		printf("client IP : %s\t client PORT:%d\n",inet_ntop(AF_INET,&clientaddr.sin_addr.s_addr,ipbuf,sizeof(ipbuf)),ntohs(clientaddr.sin_port));
		while(len=read(clientf,buf,sizeof(buf)))
		{
			int i=0;
			while(i<len)
			{
				buf[i]=toupper(buf[i]);
				i++;
			}
			write(clientf,buf,len);
		};
	}
	//close client_sockiet
	 
	close(clientfd);
	close(serverfd);
	
}
 //htonl()
//h 表示host n表示network  l表示32 s表示short