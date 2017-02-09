 ///
 /// @file    test.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-09 22:11:06
 ///
 
#include <head.h>
int main()
{
	int fd=open("test.txt",O_WRONLY|O_CREAT,0666);
	int ret=lseek(fd,1000000000,SEEK_SET);
	if(-1==ret)
	{
		perror("lseek");
		return -1;
	}
	write(fd,"1",1);
	close(fd);
	return 0;
}
