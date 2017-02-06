 ///
 /// @file    signalpending.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-06 19:25:34
 ///
 
#include"head.h"
void sig(int signum,siginfo_t *siginfo,void *p)
{
	cout<<"this is "<<signum<<endl;
	sleep(3);
	sigset_t st;
	sigemptyset(&st);
	sigpending(&st);
	if(sigismember(&st,SIGQUIT))
		cout<<"SIGQUIT is pending!"<<endl;
	else
		cout<<"NO PENDING"<<endl;
	cout<<"end "<<signum<<endl;
}
int main()
{
	struct sigaction act;
	act.sa_flags=SA_SIGINFO;
	sigemptyset(&act.sa_mask);
	sigaddset(&act.sa_mask,SIGQUIT);
	act.sa_sigaction=sig;
	sigaction(SIGINT,&act,NULL);
	sigaction(SIGQUIT,&act,NULL);
	char buff[10];
	read(STDIN_FILENO,buff,sizeof(buff));
	return 0;
}
