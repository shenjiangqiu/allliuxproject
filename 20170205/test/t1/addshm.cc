///
/// @file    test.cc
/// @author  shenjiangqiu(ivy22233qiu@live.com)
/// @date    2017-02-05 09:49:30
///
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <iostream>
using std::cout;
using std::endl;
int main()
{
	int shmid=shmget(1234,4096,IPC_CREAT|0600);
	if(shmid==-1)
	{
		cout<<"error"<<endl;
		return -1;
	}
	if(fork())
	{
		int *pshm=(int *)shmat(shmid,NULL,0);
		if(pshm==(int *)-1)
		{
			cout<<"error"<<endl;
			return -1;
		}
		for(int i=0;i<100000;++i)
		{
			++*pshm;
		}
		wait(NULL);
		cout<<*pshm<<endl;
		shmdt(pshm);
		shmctl(1234,IPC_RMID,NULL);

		return 0;
	}
	int *pshm=(int *)shmat(shmid,NULL,0);
	if(pshm==(int *)(-1))
	{
		cout<<"error"<<endl;
		return -1;
	}
	for(int i=0;i<(100000);++i)
	{
		++*pshm;
	}
	shmdt(pshm);
	return 0;
}
