 ///
 /// @file    client.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-12 19:11:05
 ///
 
#include <head.h>
#include"/home/sjq/project-git/mylib/include/mysock.h"
#include"/home/sjq/project-git/mylib/include/mysendfd.h"
#include"/home/sjq/project-git/mylib/include/sendfile.h"
#include"/home/sjq/project-git/mylib/include/pool_n.h"
int main()
{
	int ret;
	sockaddr_in seraddr;
	ret=creataddr(seraddr,"192.168.4.232","2233");
	if(ret==-1)
	{
		cout<<"error creataddr"<<endl;
		return -1;
	}
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	if(sfd==-1)
	{
		perror("socket");
		return -1;
	}
	ret=connect(sfd,(sockaddr*)&seraddr,sizeof(seraddr));
	if(ret==-1)
	{
		perror("connet");
		return -1;
	}
	ret=recvfile(sfd);
	if(-1==ret)
	{
		cout<<"recvfile"<<endl;
		return -1;
	}
	return 0;

}

