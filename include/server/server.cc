///
/// @file    test.cc
/// @author  shenjiangqiu(ivy22233qiu@live.com)
/// @date    2017-02-11 14:40:07
///

#include <head.h>
#include"/home/sjq/project-git/mylib/include/mysock.h"
#include"/home/sjq/project-git/mylib/include/myprocpool.h"
#include"/home/sjq/project-git/mylib/include/sendfile.h"
#include"/home/sjq/project-git/mylib/include/myepoll.h"
#include"/home/sjq/project-git/mylib/include/mysendfd.h"
int main(int argc,char **argv)
{
	int ret;


	int count=4;
	pch mychild=new ch[count];
	make_child(mychild,count);
	int sfd;
	creatservsock(sfd,"192.168.4.17","2233",5);
	int efd=epoll_create(1);	
	addepoll(sfd,efd);
	int i;
	for(i=0;i<count;++i)
	{
		addepoll(mychild[i].fdw,efd);		
	}
	epoll_event myevent[count+1];
	int j;
	int inret;
	while(1)
	{
		ret=epoll_wait(efd,myevent,count+1,-1);
		for(i=0;i<ret;++i)
		{
			if(myevent[i].data.fd==sfd)
			{
				int newfd=accept(sfd,NULL,NULL);
				if(newfd==-1)
				{
					perror("accept");
					continue;
				}
				for(j=0;j<count;++j)
				{
					if(mychild[j].isbusy==false)
					{

						send_fd(mychild[j].fdw,newfd);
						mychild[j].isbusy=true;
						break;
					}
				}
				close(newfd);
			}else
				for(j=0;j<count;++j)
				{
					if(myevent[i].data.fd==mychild[j].fdw)
					{
						cout<<"return from child!  "<<j<<endl;
						char tempbuff[10];
						inret=recv(mychild[j].fdw,tempbuff,sizeof(tempbuff),0);
						if(inret<=0)
						{

						}
						mychild[j].isbusy=false;
						break;
					}
				}
		}
	}
}
