 ///
 /// @file    client.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-09 18:57:35
 ///
 
#include <head.h>
int main()
{
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in seraddr;
	seraddr.sin_family=AF_INET;
	seraddr.sin_port=htons(2233);
	seraddr.sin_addr.s_addr=inet_addr("127.0.0.1");
	if(-1==connect(sfd,(struct sockaddr*)&seraddr,sizeof(seraddr)))
	{
		perror("connect");
		exit(-1);
	}
	printf("the serip is%s,the port is %d\n",inet_ntoa(seraddr.sin_addr),ntohs(seraddr.sin_port));
	fd_set fdin; 
	char chatbuff[100];
	int ret=0;
	while(1)
	{
		FD_ZERO(&fdin);
		FD_SET(STDIN_FILENO,&fdin);
		FD_SET(sfd,&fdin);
		select(sfd+1,&fdin,NULL,NULL,NULL);
		if(FD_ISSET(STDIN_FILENO,&fdin))
		{
			ret=read(STDIN_FILENO,chatbuff,sizeof(chatbuff));
			write(sfd,chatbuff,ret);
		}
		if(FD_ISSET(sfd,&fdin))
		{
			//cout<<"coming!"<<endl;
			ret=read(sfd,chatbuff,sizeof(chatbuff));
			if(ret<=0)
			{
				cout<<"bye bye"<<endl;
				exit(0);

			}
			write(STDOUT_FILENO,chatbuff,ret);
		}
	}
	return 0;
}
