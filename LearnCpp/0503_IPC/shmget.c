#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<errno.h>
#include<sys/ipc.h>
#include<fcntl.h>
#include<sys/types.h>
#include<sys/shm.h>
int main(int argc,char * argv[])
{
	key_t key;
	int shm_id;
	void * addr;
	key=ftock("./SHM",atoi(argv[1]);
	if(key==-1)	
	{
	printf("%s\n",strerror(errno));
	return -1;
	}
	shm_id=shmget(key,1024,IPC_CREAT);	
	if(shm_id==-1)
	{
	printf("%s",strerror(errno));	
	return -1;			
        }
	addr=shmat(shm_id,NULL,0);
	if(addr==NULL)
	{
	printf("%s",(char *)addr);
	scanf("%s",(char *)addr);

	}
     	shmdt(addr);
	return 0;
}
