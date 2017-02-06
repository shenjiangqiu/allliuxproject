 ///
 /// @file    signal.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-06 17:39:02
 ///
 
#include"head.h"
void sig(int signum)
{
	cout<<"the signum is "<<signum<<endl; 
	sleep(10);
	cout<<"end "<<signum<<endl;
}
int main()
{
	signal(SIGINT,sig);
	signal(SIGQUIT,sig);
	char buff[10];
	read(STDIN_FILENO,buff,sizeof(buff));
	return 0;
}
