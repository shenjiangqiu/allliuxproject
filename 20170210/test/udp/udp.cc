 ///
 /// @file    udp.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-10 09:33:06
 ///
 
#include <head.h>
using std::cin;
int main(int argc,char **argv)
{
	if(argc!=2)
	{
		cout<<"wrong args"<<endl;
		return -1;
	}
	sockaddr_in myaddr;
	myaddr.sin_family=AF_INET;
	myaddr.sin_port=htons(atoi(argv[1]));
	myaddr.sin_addr.s_addr=INADDR_ANY;
	int sfd=socket(AF_INET,SOCK_DGRAM,0);
	bind(sfd,(struct sockaddr*)&myaddr,sizeof(myaddr));
	cout<<"my port is"<<argv[1]<<endl;
	cout<<"input rmote port!"<<endl;
	int rmport;
	char rmaddrch[20];
	cin>>rmport;
	cout<<"input rmote addr:"<<endl;
	cin>>rmaddrch;
	sockaddr_in rmaddr;
	rmaddr.sin_addr.s_addr=inet_addr(rmaddrch);
	rmaddr.sin_port=htons(rmport);
	rmaddr.sin_family=AF_INET;
	fd_set inset;
	char buff[100];
	int ret;
	while(1)
	{
		FD_ZERO(&inset);
		FD_SET(sfd,&inset);

		FD_SET(STDIN_FILENO,&inset);
		select(sfd+1,&inset,NULL,NULL,NULL);
		if(FD_ISSET(STDIN_FILENO,&inset))
		{
			ret=read(STDIN_FILENO,buff,sizeof(buff));
			sendto(sfd,buff,ret,0,(struct sockaddr*)&rmaddr,sizeof(rmaddr));
		}
		if(FD_ISSET(sfd,&inset))
		{
			socklen_t len=sizeof(rmaddr);
			ret=recvfrom(sfd,buff,sizeof(buff),0,(struct sockaddr*)&rmaddr,&len);
			write(STDOUT_FILENO,buff,ret);
		}
	}
	return 0;
	

}
