 ///
 /// @file    myepoll.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-11 15:57:51
 ///
 
#include <head.h>
#include "myepoll.h"

int addepoll(int fd,int efd)
{
	if(fd<0||efd<0)
		return -1;

	epoll_event myevent;
	myevent.data.fd=fd;
	myevent.events=EPOLLIN;
	if(-1==epoll_ctl(efd,EPOLL_CTL_ADD,fd,&myevent))
	{
		perror("epoll_ctl");
		return -1;
	}
	return 0;
}
int delepoll(int fd,int efd)
{
	if(fd<0||efd<0)
		return -1;
	if(-1==epoll_ctl(efd,EPOLL_CTL_DEL,fd,NULL))
	{
		perror("epoll");
		return -1;
	}
	return 0;
}
