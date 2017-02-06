 ///
 /// @file    set0.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-05 13:53:31
 ///
 
#include"head.h"
int main()
{
	int shmid=shmget(1234,4096,IPC_CREAT|0600);
	if(-1==shmid)
	{
		return -1;
	}
	int *num=(int *)shmat(shmid,NULL,0);
	if((int *)-1==num)
	{
		return -1;
	}
	*num=0;
	cout<<"num is "<<*num<<endl;
	return 0;
	
}
