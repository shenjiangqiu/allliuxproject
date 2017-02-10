 /// @file    epoll.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-10 15:48:03
 ///
 
#include <head.h>
int main()
{
	int efd=epoll_create(3);
	struct epoll_event event;
	event.data.fd=STDIN_FILENO;
	event.events=EPOLLIN|EPOLLET;
	int ret=epoll_ctl(efd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
	epoll_event mevent[1];
	char buff[5];
	int flags=fcntl(STDIN_FILENO,F_GETFL);
	flags=flags|O_NONBLOCK;
	fcntl(STDIN_FILENO,F_SETFL,flags);
	while(1)
	{
		ret=epoll_wait(efd,mevent,1,-1);
		for(int i=0;i<ret;++i)
		{
			int ret2;
			if(mevent[i].data.fd==STDIN_FILENO)
			{
				while(1)
				{
					ret2=read(STDIN_FILENO,buff,sizeof(buff));
					if(ret2<=0)
					{
						break;
					}
					
					write(STDOUT_FILENO,buff,ret2);
				}
			}
			
		}
	}
	return 0;
}

