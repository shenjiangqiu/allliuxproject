 ///
 /// @file    poll_n.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-11 17:08:06
 ///
 

#include"../include/pool_n.h"
int send_n(int fd,char*buff,int size)
{
	int total=0;
	int ret=0;
	while(total<size)
	{
		ret=send(fd,buff+total,size-total,0);
		total+=ret;

	}
	return 0;

}
int recv_n(int fd,char *buff,int size)
{
	int total=0;
	int ret=0;
	while(total<size)
	{
		ret=recv(fd,buff+total,size-total,0);
		total+=ret;
	}
	return 0;
}
