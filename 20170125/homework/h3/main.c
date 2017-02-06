#include"head.h"
int main()
{
	if(fork())
	{
		int status;
		printf("now waiting for child...\n\n");
		wait(&status);
		if(WIFEXITED(status))
		{
			printf("the child s return is %d\n",WEXITSTATUS(status));
			exit(0);
		}
	}
	printf("i am child!!!\n\n");
	sleep (3);
	exit(0);
}
