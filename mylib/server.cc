 ///
 /// @file    server.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-13 20:43:22
 ///
 
#include <head.h>
#include "include/mypthreadpool.h"
#include"include/mysock.h"
int main()
{
	int sfd;
	int newfd;
	factory myfac(4,10);
	myfac.init();
	creatservsock(sfd,"192.168.4.232","2233",10);
	while(1)
	{
		newfd=accept(sfd,NULL,NULL);
		myfac._que.push(newfd,&myfac);
		pthread_cond_signal(&myfac._cond);
	}
	return 0;
}
