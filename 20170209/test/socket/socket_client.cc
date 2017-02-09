 ///
 /// @file    socket.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-09 10:33:00
 ///
 
#include<head.h>
int main()
{
	int sockfd;

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in sockaddr;
	sockaddr.sin_port=htons(2233);
	sockaddr.sin_family=AF_INET;
	sockaddr.sin_addr.s_addr=0;
	connect(sfd,&sockaddr,
}
