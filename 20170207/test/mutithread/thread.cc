 ///
 /// @file    thread.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-07 10:19:37
 ///
 
#include <head.h>
void * th1(void *p)
{
	cout<<"good!"<<endl;
	cout<<((long int)p)<<endl;
	return NULL;
}
int main() 
{
	pthread_t pthid;
	int ret;
	char *p=new char;
	*p='p';
	ret=pthread_create(&pthid,NULL,th1,p);
	if(ret!=0)
	{
		cout<<ret<<endl;
		return -1;
	}
	cout<<"this is main!!"<<endl;

	pthread_join(pthid,NULL);



	return 0;
}
