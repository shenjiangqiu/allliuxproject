#include"head.h"
int main()
{
	if(fork())
	{
		exit(0);
	}
	setsid();
	chdir("/");
	for(int i=0;i<3;++i)
	{
		close(i);
	}
	umask(0);
	while(1)
	{
		sleep(10);
	}
	return 0;
}
