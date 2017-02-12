 ///
 /// @file    udp.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-10 09:33:06
 ///
//server 
#include <head.h>

int main(int argc,char **argv)
{
	if(argc!=3)
	{
		cout<<"wrong args"<<endl;
		return -1;
	}


	int sfd=socket(AF_INET,SOCK_DGRAM,0);

	sockaddr_in rmaddr;
	memset(&rmaddr,0,sizeof(rmaddr));
	rmaddr.sin_port=htons(atoi(argv[2]));
	rmaddr.sin_family=AF_INET;
	rmaddr.sin_addr.s_addr=inet_addr(argv[1]);


	char buff[100];
	int ret;
	fd_set  inset;
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
