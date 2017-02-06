#include"head.h"
int main()
{
	if(fork())
	{
		sleep(10);
		return 0;
	}
	return 0;//主进程还没推出，子进程先退出，产生僵尸

}
