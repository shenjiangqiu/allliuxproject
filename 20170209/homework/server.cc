 ///
 /// @file    server.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-09 18:57:16
 ///
 
#include <head.h>
int main()
{
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in seraddr;
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(2233);
	seraddr.sin_addr.s_addr=0;

	bind(sfd,(struct sockaddr*)&seraddr,(socklen_t)sizeof(seraddr));
	listen(sfd,10);
	
	fd_set tempset;
	fd_set fdin;
	FD_ZERO(&tempset);
	FD_ZERO(&fdin);
	FD_SET(STDIN_FILENO,&tempset);
	FD_SET(sfd,&tempset);
	int newfd=-1;
	char chatbuff[100];
	int ret=0;
	while(1)
	{
		memcpy(&fdin,&tempset,sizeof(fdin));
		select(14,&fdin,NULL,NULL,NULL);
		if(FD_ISSET(sfd,&fdin))
		{
			sockaddr_in clientaddr;
			socklen_t clientlen=sizeof(clientaddr);
			newfd=accept(sfd,(struct sockaddr*)&clientaddr,&clientlen);
			FD_SET(newfd,&tempset);
			FD_CLR(sfd,&tempset);
			printf("the ip is %s,the port is %d\n",inet_ntoa(clientaddr.sin_addr),ntohs(clientaddr.sin_port));
			 
		}
		if(FD_ISSET(newfd,&fdin))
		{
			ret=recv(newfd,chatbuff,sizeof(chatbuff),0);
			if(ret<=0)
			{
				cout<<"bye bye"<<endl;
				FD_CLR(newfd,&tempset);
				newfd=-1;
				FD_SET(sfd,&tempset);
			}
			else
			{
				write(STDOUT_FILENO,chatbuff,ret);
			}

		}
		if(FD_ISSET(STDIN_FILENO,&fdin))
		{
			ret=read(STDIN_FILENO,chatbuff,sizeof(chatbuff));
			//cout<<"ret= "<<ret<<endl;
			if(ret<=0)
			{
				cout<<"error read"<<endl;
				exit(0);
			}
			if(newfd>0)
				//write(newfd,chatbuff,ret);
			{
			//	cout<<"send to new fd:"<<newfd<<endl;	
			ret=send(newfd,chatbuff,ret,0);
			if(ret==-1)
			{
				perror("send");
				exit(0);
			}
			}
			else
				cout<<"error newfd: "<<newfd<<endl;
		}
	}

	return 0;
}

