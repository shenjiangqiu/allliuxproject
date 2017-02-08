///
/// @file    con.cc
/// @author  shenjiangqiu(ivy22233qiu@live.com)
/// @date    2017-02-08 10:32:56
///

#include<head.h>
typedef struct info
{
	pthread_mutex_t mutex;
	pthread_cond_t cond;
}th,*pth;

void *th1 (void *p)
{
	pth p2=(pth)p;
	cout<<"start to wait!"<<endl;

	pthread_mutex_lock(&p2->mutex);
	pthread_cond_wait(&p2->cond,&p2->mutex);
	pthread_mutex_unlock(&p2->mutex);
	cout<<"wait OK!"<<endl;


	return NULL;
} 

int main()
{
	th mth1;
	pthread_t thid;
	pthread_mutex_init(&mth1.mutex,NULL);
	pthread_cond_init(&mth1.cond,NULL);
	pthread_create(&thid,NULL,th1,&mth1);
	sleep(1);
	pthread_cond_signal(&mth1.cond);
	pthread_join(thid,NULL);
	return 0;
}
