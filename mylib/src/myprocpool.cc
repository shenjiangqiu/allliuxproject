#include"../include/myprocpool.h"
#include"../include/sendfile.h"
#include"../include/mysendfd.h"
int handle(int fdw)
{
	cout<<"i am handling..."<<endl;
	int fdnew;
	while(1)
	{
		recv_fd(fdw,&fdnew);
		cout<<"start to work!"<<endl;
		sendfile("file",fdnew);
		int flag=1;
		send(fdw,(char*)&flag,sizeof(flag),0);
		cout<<"end work"<<endl;
	}
	return 0;
}
int make_child(pch child,int count)
{
	int i;
	int ret;
	int fd[2];
	int pid=0;
	for(i=0;i<count;++i)
	{

		ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fd);
		if(ret==-1)
		{
			perror("socketpair");
			return -1;
		}
		if(0!=(pid=fork()))
		{
			close(fd[0]);
			child[i].fdw=fd[1];
			child[i].pid=pid;
			child[i].isbusy=false;
		}
		else
		{
			close(fd[1]);
			if(-1==handle(fd[0]))
			{
				cout<<"handle error!"<<endl;
				exit(-1);
			}
			exit(0);
		}
	}
	return 0;
}
