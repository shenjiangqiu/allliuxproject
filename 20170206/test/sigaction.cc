 ///
 /// @file    sigaction.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-06 10:12:36


#include"head.h"

void sig(int signum,siginfo_t **p,void *p1)
{
	cout<<signum<<endl;
}

int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.
}
