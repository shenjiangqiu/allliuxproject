///
/// @file    func.cc
/// @author  shenjiangqiu(ivy22233qiu@live.com)
/// @date    2017-02-10 22:30:21
///

#include"mysendfd.h"
void send_fd(int fdw,int fd)
{
	struct msghdr msg;
	memset(&msg,0,sizeof(msg));
	char buf[10]="hello";
	struct iovec iov[1];
	iov[0].iov_base=buf;
	iov[0].iov_len=5;
	msg.msg_iov=iov;
	msg.msg_iovlen=1;
	struct cmsghdr *cmsg;
	int len=CMSG_LEN(sizeof(int));
	cmsg=(struct cmsghdr *)calloc(1,len);
	cmsg->cmsg_len=len;
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	*(int*)CMSG_DATA(cmsg)=fd;
	msg.msg_control=cmsg;
	msg.msg_controllen=len;
	int ret;
	ret=sendmsg(fdw,&msg,0);
	if(-1==ret)
	{
		perror("sendmsg");
		return;
	}
}		

void recv_fd(int fdr,int* fd)
{
	struct msghdr msg;
	memset(&msg,0,sizeof(msg));
	char buf[10]="hello";
	struct iovec iov[1];
	iov[0].iov_base=buf;
	iov[0].iov_len=5;
	msg.msg_iov=iov;
	msg.msg_iovlen=1;
	struct cmsghdr *cmsg;
	int len=CMSG_LEN(sizeof(int));
	cmsg=(struct cmsghdr *)calloc(1,len);
	cmsg->cmsg_len=len;
	cmsg->cmsg_level = SOL_SOCKET;
	cmsg->cmsg_type = SCM_RIGHTS;
	msg.msg_control=cmsg;
	msg.msg_controllen=len;
	int ret;
	ret=recvmsg(fdr,&msg,0);
	if(-1==ret)
	{
		perror("recvmsg");
		return;
	}
	*fd=*(int*)CMSG_DATA(cmsg);
}		

