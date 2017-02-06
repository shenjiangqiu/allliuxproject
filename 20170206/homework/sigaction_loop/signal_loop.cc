 ///
 /// @file    signal_loop.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-06 19:02:56
 ///
 
#include"head.h"
using std::cout;
using std::endl;
void sig(int signum,siginfo_t *info,void *p)
{
	cout<<"the begin of "<<signum<<endl;
	sleep(4);
	cout<<"end of "<<signum<<endl;
}
int main()
{
	struct sigaction act;
	act.sa_flags=SA_SIGINFO|SA_NODEFER;//定义无限入栈，立即打断
	sigemptyset(&act.sa_mask);
	act.sa_sigaction=sig;
	sigaction(SIGINT,&act,NULL);
	sleep(10);
	return 0;
}
