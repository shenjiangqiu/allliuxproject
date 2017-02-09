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
	bind(sockfd,(struct sockaddr*)&sockaddr,sizeof(sockaddr));
	listen(sockfd,10);
	sockaddr_in newaddr;
	socklen_t newaddrlen=sizeof(newaddr);
	int newfd=accept(sockfd,(struct sockaddr*)&newaddr,&newaddrlen);
	int ret;	
	char buff[100]; 
	while(1)
	{
		fd_set inset;
		FD_ZERO(&inset);
		FD_SET(STDIN_FILENO,&inset);
		FD_SET(newfd,&inset);
		select(newfd+1,&inset,NULL,NULL,NULL);
		if(FD_ISSET(STDIN_FILENO,&inset))
		{
			ret=read(STDIN_FILENO,buff,sizeof(buff));
			if(ret<=0)
			{
				cout<<"bye bye"<<endl;
				exit(0);
			}
			send(newfd,buff,ret-1,0);

		}
		if(FD_ISSET(newfd,&inset))
		{
			ret=read(newfd,buff,sizeof(buff));
			if(ret<=0)
			{
				cout<<"bye bye"<<endl;
				exit(0);
			}
			write(STDOUT_FILENO,buff,ret);
		}
	}
	return 0;
}
