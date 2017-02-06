#include"head.h"
int main()
{
	if(fork())
	{
		return 0;
	}
	else
	{
		sleep(1);

		printf("\nmy id is%d,my ppid is %d\n",getpid(),getppid());
		return 0;
	}
}
