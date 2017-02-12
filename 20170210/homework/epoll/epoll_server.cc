 /// @file    epoll.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-10 15:48:03
 ///
 
//server.cc
//

#include <head.h>


int main(int argc,char **argv)
{
	if(argc!=2)
	{
		cout<<"error args"<<endl;
		return -1;
	}


	//设置服务端监听sock
	int sfd=socket(AF_INET,SOCK_STREAM,0);
	sockaddr_in myaddr;
	myaddr.sin_addr.s_addr=INADDR_ANY;
	myaddr.sin_port=htons(atoi(argv[1]));
	myaddr.sin_family=AF_INET;
	if(-1==bind(sfd,(sockaddr*)&myaddr,sizeof(myaddr)))
		return -1;
	listen(sfd,10);



	//设置边沿触发epoll
	int efd=epoll_create(3);
	struct epoll_event event;
	event.data.fd=STDIN_FILENO;
	event.events=EPOLLIN|EPOLLET;
	int ret=epoll_ctl(efd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
	if(ret==-1)
	{
		perror("epoll_ctl");
		return -1;
	}
	event.data.fd=sfd;
	event.events=EPOLLIN;
	ret=epoll_ctl(efd,EPOLL_CTL_ADD,sfd,&event);
	if(-1==ret)
	{
		perror("epoll_ctl");
		return -1;
	}

	epoll_event mevent[3];
	memset(mevent,0,sizeof(mevent));
	

	//设置接收端addr
	sockaddr_in rmaddr;
	socklen_t rmlen=sizeof(rmaddr);


	//准备开始通信
	char buff[5]={0};
	int flags=fcntl(STDIN_FILENO,F_GETFL);
	flags=flags|O_NONBLOCK;
	fcntl(STDIN_FILENO,F_SETFL,flags);
	int newfd;
	int ret2;
	while(1)
	{
		//cout<<"waiting !"<<endl;
		ret=epoll_wait(efd,mevent,3,-1);
		for(int i=0;i<ret;++i)
		{
			if(mevent[i].data.fd==STDIN_FILENO)
			{
				//cout<<"in stdin"<<endl;
				if(newfd==0)
				{
					cout<<"havnt conneted!"<<endl;
					
					break;
				}
				while(1)
				{
					ret2=read(STDIN_FILENO,buff,sizeof(buff));
					if(ret2<=0)
					{
						//cout<<"ret="<<ret2<<endl;
						break;
					}
					
					send(newfd,buff,ret2,0);
				}
			}else if(mevent[i].data.fd==sfd)
			{
				//接受连接并且设置不阻塞
				newfd=accept(sfd,(sockaddr*)&rmaddr,&rmlen);
				if(newfd==-1)
				{
					perror("accept");
					break;
				}
				cout<<"connet!"<<endl;
				cout<<"ip: "<<inet_ntoa(rmaddr.sin_addr)<<"port: "<<ntohs(rmaddr.sin_port)<<endl;
				flags=fcntl(newfd,F_GETFL);
				flags=flags|O_NONBLOCK;
				fcntl(newfd,F_SETFL,flags);
				//cout<<"new fd:"<<newfd<<endl;
				
				//epoll添加新sock并删除监听
				event.events=EPOLLET|EPOLLIN;
				event.data.fd=newfd;
				epoll_ctl(efd,EPOLL_CTL_ADD,newfd,&event);
			}else if(mevent[i].data.fd==newfd)
			{
				//cout<<"in newfd"<<endl;
				while(1)
				{
					//cout<<"read from newfd"<<endl;
					ret2=recv(newfd,buff,sizeof(buff),0);
					if(ret2<=0)
					{
						if(ret2==-1)
						{
							break;
						}
						
						cout<<"disconnet!"<<endl;
						close(newfd);
						epoll_ctl(efd,EPOLL_CTL_DEL,newfd,NULL);
						newfd=0;
						event.data.fd=sfd;
						event.events=EPOLLIN;
						epoll_ctl(efd,EPOLL_CTL_ADD,sfd,&event);
						break;
					}else
					{
						write(STDOUT_FILENO,buff,ret2);
					}
					
				}
				//cout<<"out newfd"<<endl;
			}
			
		}
	}
	return 0;
}

