 ///
 /// @file    sigprocmast.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-06 19:41:56
 ///
 
#include"head.h"
using std::cout;
using std::endl;


void sig(int signum)
{
	cout<<signum<<endl;

}

int main()
{
	//set signal
	signal(SIGINT,sig);

	//set sigset_t for block	
	sigset_t sigset;
	sigemptyset(&sigset);
	sigaddset(&sigset,SIGINT);
	sigaddset(&sigset,SIGQUIT);
	//start block	
	sigprocmask(SIG_BLOCK,&sigset,NULL);
	cout<<"start to block!"<<endl;	
	
	sleep(5);


	//set sigset_t to judge signal_pending
	sigset_t pend;
	sigemptyset(&pend);
	sigpending(&pend);
	if(sigismember(&pend,SIGINT))
		cout<<"SIGINT IS PENDING!"<<endl;
	else
		cout<<"NOT PENDING!"<<endl;

	//end block
	sigprocmask(SIG_UNBLOCK,&sigset,NULL);
	cout<<"end block"<<endl;

	return 0;
}
