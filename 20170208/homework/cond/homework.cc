 ///
 /// @file    homework.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-08 22:38:51
 ///
 

#include<head.h>
typedef struct tag_info
{
	pthread_mutex_t *pmutex;
	pthread_cond_t *pcond;
}*pinfo,info;

void *pth(void* p)
{
	pinfo mpinfo=(pinfo)p;
	pthread_mutex_lock(mpinfo->pmutex);
	cout<<"waiting..."<<endl;
	pthread_cond_wait(mpinfo->pcond,mpinfo->pmutex);
	pthread_mutex_unlock(mpinfo->pmutex);


	return NULL;
}
int main()

{
	pthread_t pthid;
	pthread_mutex_t mutex;
	pthread_cond_t cond;
	pthread_cond_init(&cond,NULL);
	pthread_mutex_init(&mutex,NULL);
	info myinfo;
	myinfo.pmutex=&mutex;
	myinfo.pcond=&cond;
	pthread_create(&pthid,NULL,pth,&myinfo);
	sleep(2);
	pthread_cond_signal(&cond);
	pthread_join(pthid,NULL);
	return 0;
}
