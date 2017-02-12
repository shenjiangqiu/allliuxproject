///
/// @file    myfcntl.cc
/// @author  shenjiangqiu(ivy22233qiu@live.com)
/// @date    2017-02-11 16:06:16
///

#include <head.h>
#include "myfcntl.h"
int myfcntl(int fd,int cmd)
{
	if(fd<0)
	{
		return -1;
	}
	if(cmd!=blk&&cmd!=noblk)
	{
		cout<<"error cmd"<<endl;
		return -1;
	}
	int flags=fcntl(fd,F_GETFL);
	if(-1==flags)
	{
		perror("fcntl");
		return -1;
	}
	if(cmd==blk)
		flags=flags&(~O_NONBLOCK);
	else
		flags=flags|O_NONBLOCK;
	if(-1==fcntl(fd,F_SETFL,flags))
	{
		perror("fcntl");
		return -1;
	}
	return 0;
}
