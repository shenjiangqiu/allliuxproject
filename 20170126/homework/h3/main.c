#include"head.h"
void cal(int shmid)
{
		int *num=(int *)shmat(shmid,NULL,0);
		printf("add %d\n",num);
		for(int i=0;i<10000000;i++)
		{
			++(*num);
		}



}
int main()
{
	int shmid=shmget(2234,4,IPC_CREAT|0600);
	if(shmid==-1)
	{
		perror("shmid");
		return -1;
	}
	int *temp=(int *)shmat(shmid,NULL,0);
	*temp=0;
	shmdt(temp);
	if(fork())
	{
		int *num=(int *)shmat(shmid,NULL,0);
		printf("add %d\n",num);
		for(int i=0;i<10000000;i++)
		{
			++(*num);
		}
		wait(NULL);

		printf("%d\n",*num);
		shmdt(num);
		return 0;

	}
	int *num=(int *)shmat(shmid,NULL,0);
	printf("add %d\n",num);
	for(int i=0;i<10000000;i++)
	{
		++(*num);
	}
	shmdt(num);

	return 0;

}

