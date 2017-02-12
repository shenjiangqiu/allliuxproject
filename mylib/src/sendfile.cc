 ///
 /// @file    sendfile.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-12 15:52:34
 ///
 
#include"../include/sendfile.h"
#include"../include/pool_n.h"
int sendfile(const char* filename,int sfd)
{
	int ret=0;
	int fd=open(filename,O_RDONLY);
	if(fd==-1)
	{
		perror("open");
		return -1;
	}

	bftype mybuff;
	strcpy(mybuff.buff,filename);
	mybuff.len=strlen(filename);
	cout<<"filename len="<<mybuff.len;
	send_n(sfd,(char*)&mybuff,mybuff.len+4);
	struct stat mystat;
	ret=fstat(fd,&mystat);
	if(ret==-1)
	{
		perror("fstat");
		return -1;
	}
	mybuff.len=sizeof(mystat.st_size);
	
	memcpy(mybuff.buff,&mystat.st_size,sizeof(mystat.st_size));
	send_n(sfd,(char*)&mybuff,mybuff.len+4);
	cout<<"stat to send"<<endl;
	while((ret=read(fd,mybuff.buff,sizeof(mybuff.buff)))>0)
	{
		mybuff.len=ret;

		send_n(sfd,(char*)&mybuff,mybuff.len+4);
	}
	cout<<"end send"<<endl;
	mybuff.len=0;
	send_n(sfd,(char*)&mybuff,mybuff.len+4);
	close(fd);
	return 0;
}
int recvfile(int sfd)
{
	
	bftype mybuff;
	recv_n(sfd,(char*)&mybuff.len,4);
	if(mybuff.len==0)
	{
		return 0;
	}
	recv_n(sfd,(char*)mybuff.buff,mybuff.len);
	mybuff.buff[mybuff.len]=0;
	int fd=open(mybuff.buff,O_WRONLY|O_CREAT,0666);
	
	
	if(-1==fd)
	{
		perror("open");
		return -1;
	}
	__off_t st_size;
	recv_n(sfd,(char*)&mybuff.len,4);
	recv_n(sfd,(char*)&st_size,mybuff.len);
	int prossecc=0;
	int total=0;
	while(1)
	{
		recv_n(sfd,(char*)&mybuff.len,4);
		prossecc+=mybuff.len;
		total+=mybuff.len;
		if(mybuff.len==0)
		{
			system("clear");
			cout<<"100%"<<endl;
			return 0;
		}
		if((double)prossecc/(double)st_size>0.01)
		{
			system("clear");
			printf("%5.2lf%%\n",100*(double)total/(double)st_size);
			prossecc=0;
		}
		recv_n(sfd,(char*)mybuff.buff,mybuff.len);
		write(fd,mybuff.buff,mybuff.len);
	}
	close(fd);
	return 0;

}
