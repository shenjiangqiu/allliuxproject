///
/// @file    add1000.cc
/// @author  shenjiangqiu(ivy22233qiu@live.com)
/// @date    2017-02-05 13:53:14
///
#include"head.h"
#define N 1000000
int main()
{
	int shmid=shmget(1234,4096,IPC_CREAT|0600);
	if(shmid==-1)
	{
		perror("shmid");
		return -1;

	}
	int semid=semget(1234,1,IPC_CREAT|0600);
	if(semid==-1)
	{
		perror("semid");
		return -1;
	}
	semctl(semid,0,SETVAL,1);
	struct sembuf buf_p;
	buf_p.sem_op=-1;
	buf_p.sem_num=0;
	buf_p.sem_flg=SEM_UNDO;

	struct sembuf buf_v=buf_p;
	buf_v.sem_op=1;
	if(!fork())
	{
		int *num;

		if((num=(int *)shmat(shmid,NULL,0))==(int *)-1)
		{
			perror("shmat");
			return -1;
		}
		for(int i=0;i<N;++i)
		{
			semop(semid,&buf_p,1);
			++*num;
			semop(semid,&buf_v,1);
		}
		shmdt(num);
		return 0;
	}
	int *num_2;
	if((num_2=(int *)shmat(shmid,NULL,0))==(int *)-1)
	{
		perror("shmat");
		return -1;
	}

	for(int i=0;i<N;++i)
	{
		semop(semid,&buf_p,1);
		++*num_2;
		semop(semid,&buf_v,1);
	}
	wait(NULL);
	cout<<"end is"<<*num_2;
	shmdt(num_2);
	return 0;

}	

