 ///
 /// @file    sigaction.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-06 10:12:36


#include"head.h"

void sig(int signum,siginfo_t *p,void *p1)
{
	
	//cout<<signum<<endl;
	switch(signum)
	{
		case 2:
			cout<<"SIGINT"<<endl;
			break;
		case 3:
			cout<<"SIGQUIT"<<endl;
			break;
		default:
			break;
	}
}

int main()
{
	struct sigaction act;
	memset(&act,0,sizeof(act));
	act.sa_flags=SA_SIGINFO|SA_RESTART;
	act.sa_sigaction=sig;
	sigaction(SIGINT,&act,NULL);
	char buff[100];
	int ret=read(STDIN_FILENO,buff,100);
	if(ret>0)
		write(STDOUT_FILENO,buff,ret);
	else
		cout<<ret<<endl;
	return 0;
}
