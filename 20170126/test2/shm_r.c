#include"head.h"
int main()
{
	int shmid=shmget(1234,1<<21,IPC_CREAT|0600);
	char *p;
	printf(p=shmat(shmid,NULL,0));
	shmdt(p);
	return 0;

}
