 /// @file    epoll.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-10 15:48:03
 ///
 
//client.cc
//

#include <head.h>


int main(int argc,char **argv)
{
	if(argc!=3)
	{
		cout<<"error args"<<endl;
		return -1;
	}
	
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	



	//设置边沿触发epoll
	int efd=epoll_create(2);
	struct epoll_event event;
	event.data.fd=STDIN_FILENO;
	event.events=EPOLLIN|EPOLLET;
	int ret=epoll_ctl(efd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
	if(ret==-1)
	{
		perror("epoll_ctl");
		return -1;
	}
	
	//设置远端地址
	sockaddr_in rmaddr;
	socklen_t rmlen=sizeof(rmaddr);
	rmaddr.sin_addr.s_addr=inet_addr(argv[1]);
	rmaddr.sin_port=htons(atoi(argv[2]));
	rmaddr.sin_family=AF_INET;

	ret=connect(sfd,(sockaddr*)&rmaddr,rmlen);
	if(ret==-1)
	{
		perror("connect");
		return -1;
	}


	event.data.fd=sfd;
	event.events=EPOLLET|EPOLLIN;
	ret=epoll_ctl(efd,EPOLL_CTL_ADD,sfd,&event);
	if(-1==ret)
	{
		perror("epoll_ctl");
		return -1;
	}

	epoll_event mevent[2];
	memset(mevent,0,sizeof(mevent));
	

	//远端addr
	//准备开始通信
	char buff[5]={0};
	int flags=fcntl(STDIN_FILENO,F_GETFL);
	flags=flags|O_NONBLOCK;
	ret=fcntl(STDIN_FILENO,F_SETFL,flags);
	if(-1==ret)
	{
		perror("fcntl");
		return -1;
	}
	flags=fcntl(sfd,F_GETFL);
	flags=flags|O_NONBLOCK;
	ret=fcntl(sfd,F_SETFL,flags);
	if(-1==ret)
	{
		perror("fcntl");
		return -1;
	}
	int ret2;
	while(1)
	{
		//cout<<"sfd="<<sfd<<endl;
		ret=epoll_wait(efd,mevent,2,-1);
		for(int i=0;i<ret;++i)
		{
			if(mevent[i].data.fd==STDIN_FILENO)
			{
				while(1)
				{	
					//cout<<"read stdin"<<endl;
					ret2=read(STDIN_FILENO,buff,sizeof(buff));
					//cout<<"read"<<endl;
					//cout<<"ret2="<<ret2<<endl;
					if(ret2<=0)
					{
						//cout<<"ret2<0"<<ret2<<endl;
						if(ret2==-1)
						{
							//perror("read");
							//cout<<errno<<endl;
							break;
						}
						//cout<<"read stdin error"<<endl;
						break;
					}
					
					ret2=send(sfd,buff,ret2,0);
					if(ret2==-1)
					{
						perror("write");
						return -1;
					}
				}
			}else if(mevent[i].data.fd==sfd)
			{
				//cout<<"read sfd"<<endl;
				while(1)
				{
					ret2=recv(sfd,buff,sizeof(buff),0);
					if(ret2<=0)
					{
						if(ret2==0)
						{
							cout<<"error"<<endl;
							exit(0);
						}
						break;
					}
					write(STDOUT_FILENO,buff,ret2);
				}

			}
			
		}
	}
	return 0;
}

