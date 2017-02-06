#include"head.h"
int main()
{
	int fd[2];
	int ret=pipe(fd);
	if(ret==-1)
	{
		perror("pipe");
		return -1;
	}
	if(fork())
	{
		char buff[100];
		close(fd[1]);
		read(fd[0],buff,100);
		write(STDOUT_FILENO,buff,strlen(buff));
		close(fd[0]);
		return 0;
	}
	close(fd[0]);
	write(fd[1],"hello",6);
	close(fd[1]);
	return 0;
}
			

