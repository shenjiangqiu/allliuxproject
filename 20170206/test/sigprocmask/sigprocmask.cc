 ///
 /// @file    sigprocmask.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-06 15:34:21
 ///
 
#include"head.h"
using std::cout;
using std::endl;
void sigqt(int signum,siginfo_t *act,void *pReserved)
{
	cout<<endl<<"start quit!"<<endl;
	sleep(5);
	cout<<"end quit"<<endl;

}
int main()
{
	struct sigaction act;
	act.sa_sigaction=sigqt;
	act.sa_flags=SA_SIGINFO;
	sigemptyset(&act.sa_mask);

	sigaction(SIGQUIT,&act,NULL);
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset,SIGINT);
	
	cout<<"before sleep!"<<endl;
	sigprocmask(SIG_BLOCK,&sigset,NULL);
	sleep(10);
	cout<<"end sleep!"<<endl;
	sigprocmask(SIG_UNBLOCK,&sigset,NULL);
	return 0;
}
