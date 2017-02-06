#include"head.h"
int main()
{
	int shmid=shmget((key_t)1234,1<<21,IPC_CREAT|0600);
	if(shmid==-1)
	{
		perror("shmget()");
		return -1;
	}
	char *p=shmat(shmid,NULL,0);
	if(NULL==p)
	{
		perror("shmat");
		return -1;
	}
	strcpy(p,"hello world!");
	shmdt(p);
	return 0;
}
