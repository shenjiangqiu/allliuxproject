 ///
 /// @file    setzero.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-05 10:25:22
 ///
#include<sys/shm.h>
#include<sys/ipc.h>
#include<sys/types.h>
#include <iostream>
using std::cout;
using std::endl;
int main()
{
	int shmid=shmget(1234,4096,IPC_CREAT|0600);
	if(shmid==-1)
	{
		cout<<"error1"<<endl;
		return -1;
	}
	int *psh=(int *)shmat(shmid,NULL,0);
	if(psh==(int *)-1)
	{
		cout<<"error2"<<endl;
		return -1;
	}
	*psh=0;
	shmdt(psh);
	return 0;
}
