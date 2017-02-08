///
/// @file    add.cc
/// @author  shenjiangqiu(ivy22233qiu@live.com)
/// @date    2017-02-07 19:50:37
///

#include<head.h>

pthread_mutex_t mutex;
void* th1(void *p)
{
	int *p1=(int*)p;
	for(int i=0;i<10000000;++i)
	{
		pthread_mutex_lock(&mutex);
		++*p1;
		pthread_mutex_unlock(&mutex);
	}
	return NULL;
}

int main()
{
	pthread_mutex_init(&mutex,NULL);

	pthread_t pthid;
	int num=0;
	pthread_create(&pthid,NULL,th1,&num);

	for(int i=0;i<10000000;++i)
	{
		pthread_mutex_lock(&mutex);
		++num;
		pthread_mutex_unlock(&mutex);
	}
	pthread_join(pthid,NULL);
	cout<<num<<endl;
	return 0;
}

