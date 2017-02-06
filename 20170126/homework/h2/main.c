#include<apue.h>
#include<sys/shm.h>
#include<unistd.h>
#include<stdio.h>
int main(int argc,char** argv)
{
	int ret=0;
	int shmid;
	char *shmchar;
	if(argc!=2)
	{
		return -1;
	}
	if(argv[1][0]=='w')
	{
		printf("start to write sharedmem!\n");
		shmid=shmget(1234,20,IPC_CREAT|0600);
		if(-1==shmid)
		{
			perror("shmget");
			return -1;
		}
		shmchar=(char*)shmat(shmid,NULL,0);
		if((char*)-1==shmchar)
		{
			perror("shmat");
			return -1;
		}
		strcpy(shmchar,"how are you?");
		shmdt(shmchar);
		printf("done!\n\n");
		return 0;
	}
	if(argv[1][0]=='r')
	{
		shmid=shmget(1234,20,IPC_CREAT|0600);
		if(shmid==-1)
		{
			perror("shmat");
			return -1;
		}
		shmchar=shmat(shmid,NULL,0);
		if(shmchar==(char*)-1)
		{
			perror("shmat");
			return -1;
		}
		ret=write(STDOUT_FILENO,shmchar,strlen(shmchar));
		if(ret==-1)
		{
			perror("write");
			return -1;
		
		}
		printf("\n");
		ret=shmdt(shmchar);
			
		if(ret==-1)
		{
			perror("shmdt");
			return -1;
		}
		printf("dt succeed!\n");
		ret=shmctl(shmid,IPC_RMID,NULL);
		if(ret==-1)
		{
			perror("shmctl,IPC_RMID");
			return -1;
		}
		printf("rm succeed!\n");

		return 0;
	}
	return 0;

}
