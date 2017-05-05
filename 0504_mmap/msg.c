#include<stdio.h>
#include<stdlib.h>
#include<sys/mman.h>
#include<string.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<unistd.h>
#include<sys/types.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<errno.h>
struct my_msg
{
	long mtype;
	char mtext[512];
};
int main(int argc,char* argv[])
{
	key_t key;
	struct my_msg msg;
	int fd=0;
	size_t len=0;
	int msg_id=0;
	FILE * pf;
	char * chartemp="qwerqwrqwr";
	char * line;

	int ret;
	//creat key
	key=ftok(".",2);
	msg_id=msgget(key,IPC_CREAT);
	if(msg_id==-1)
	{
		perror("msgget");
	}
	if(atoi(argv[1])<1)
	{
		pf=fopen("./FMSG","r");
		while(-1!=getline(&line,&len,pf))
		{
			printf("%s",line);
			strcpy(msg.mtext,line);
			//creat msg
			ret=msgsnd(msg_id,&msg,strlen(line)+1,0);	
			//ret=msgsnd(msg_id,&msg,sizeof(msg),0);	
			if(ret==-1)
			{
				perror("msgsend ::");
			}
		}
	}
	else
	{
		if(fd==-1)
		{
			perror("open error is");
		}	
		while(1)
		{
			//msgrcv(msg_id,&msg,sizeof(msg),0,0);
			ret=msgrcv(msg_id,&msg,512,0,0);
			//	msgrcv(msg_id,msg.mtext,512,0,0);
			if(ret==-1)
			{
				perror("msgrcv");
			}
			if(msg.mtext=="END")
			{
				break;
			}
			printf("%s",msg.mtext);	
			pf=fopen("./ANS","ab+");
			ret=fwrite(&msg.mtext,sizeof(char),strlen(msg.mtext),pf);
			if(ret==-1)
			{
				perror("fwrite ::");
			}
				
		}
		//msgctl(msg_id,IPC_STAT,&msg_ds);
	}







}
