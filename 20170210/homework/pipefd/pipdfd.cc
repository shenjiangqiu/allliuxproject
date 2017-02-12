///
/// @file    pipdfd.cc
/// @author  shenjiangqiu(ivy22233qiu@live.com)
/// @date    2017-02-10 22:30:09
///

#include <head.h>
void send_fd(int ,int);
void recv_fd(int ,int*);
int main()
{
	int fds[2];
	int ret=socketpair(AF_LOCAL,SOCK_STREAM,0,fds);
	if(-1==ret)
	{
		perror("socketpair");
		return -1;
	}
	if(!fork())
	{
		close(fds[1]);//关闭写端
		int fd;
		recv_fd(fds[0],&fd);//接收描述符
		printf("fd=%d\n",fd);
		char buf[20]={0};
		read(fd,buf,sizeof(buf));
		printf("buf=%s\n",buf);
		close(fds[0]);
		exit(0);
	}else{
		close(fds[0]);
		int fd;
		fd=open("file",O_RDWR);
		printf("parent fd=%d\n",fd);
		send_fd(fds[1],fd);//发送描述符	
		wait(NULL);
		return 0;
	}
}
