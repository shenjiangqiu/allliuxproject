 ///
 /// @file    setitimer.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-06 20:08:26
 ///
 
#include"head.h"
using std::cout;
using std::endl;
void sig(int signum)
{
	time_t tm=time(NULL);
	cout<<ctime(&tm);
}
int main()
{
	signal(SIGALRM,sig);
	struct itimerval it;
	memset(&it,0,sizeof(it));
	it.it_value.tv_sec=2;
	it.it_interval.tv_sec=3;
	setitimer(ITIMER_REAL,&it,NULL);
	char buff[10];
	read(STDIN_FILENO,buff,sizeof(buff));
	return 0;
}
