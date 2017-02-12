 ///
 /// @file    creatthread..cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-11 14:17:17
 ///
 
#include "mysock.h"
int creataddr(sockaddr_in &saddr,const char*addr,const char*port)
{
	if(addr==NULL||port==NULL)
	{
		cout<<"error args :int creataddr()!"<<endl;
	}
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=inet_addr(addr);
	saddr.sin_port=htons(atoi(port));
	return 0;
}

int creatservsock(int &fd,const char*addr,const char*port,int count)
{
	fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd==-1)
	{
		cout<<"error socket()!"<<endl;
		return -1;
	}
	sockaddr_in tempaddr;
	if(-1==creataddr(tempaddr,addr,port))
	{
		cout<<"error creataddr()!"<<endl;
		return -1;
	}
	if(-1==bind(fd,(sockaddr*)&tempaddr,sizeof(tempaddr)))
	{
		cout<<"error bind()"<<endl;
		perror("bind:");
		return -1;
	}
	if(-1==listen(fd,count))
	{
		perror("listen:");
		return -1;
	}
	return 0;
}
