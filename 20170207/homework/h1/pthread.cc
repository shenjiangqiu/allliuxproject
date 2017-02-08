 ///
 /// @file    pthread.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-07 19:44:28
 ///


#include<head.h>

void *pth(void *p)
{
	cout<<(long int)p<<endl;
	return (void *)2;

}

int main()
{
	pthread_t pthid;
	pthread_create(&pthid,NULL,pth,(void *)1);
	int a;
	pthread_join(pthid,(void **)&a);
	cout<<a<<endl;
	return 0;

}
