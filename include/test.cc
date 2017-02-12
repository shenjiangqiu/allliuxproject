 ///
 /// @file    test.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-11 14:40:07
 ///
 
#include <head.h>
#include"mysock.h"

int main()
{
	int fd;
	if(-1==creatservsock(fd,"127.0.0.1","2000",5))
	{
		return -1;
	}
	cout<<fd<<endl;
	sockaddr_in myaddr;
	if(-1==creataddr(myaddr,"127.0.0.1","2000"))
	{
		return -1;

	}
	cout<<ntohs(myaddr.sin_port)<<endl;
	cout<<inet_ntoa(myaddr.sin_addr)<<endl;
	return 0;
}

