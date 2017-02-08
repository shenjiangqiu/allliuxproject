 ///
 /// @file    cleanup.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-07 20:18:13
 ///
 
#include<head.h>
void clean(void *p)
{
	delete[] (int *)p;
	cout<<"succeed cleanup!"<<endl;
}
void *pth(void *p)
{
	int *temp=new int[100];
	pthread_cleanup_push(clean,temp);
	sleep(5);
	pthread_cleanup_pop(1);
	return NULL;
}
int main()
{
	pthread_t pthid;
	
	pthread_create(&pthid,NULL,pth,NULL); 
	sleep(1);
	pthread_cancel(pthid);
	pthread_join(pthid,NULL);

	return 0;


}
