///
/// @file    main.cc
/// @author  shenjiangqiu(ivy22233qiu@live.com)
/// @date    2017-02-05 17:05:07
///

#include "head.h"
using std::cout;
using std::endl;
int count=0;
void sig(int num)
{
//	cout<<"hello world!!!   "<<num<<endl;
//	cout<<count<<endl;
//	++count;
	sleep(10); 
}
int main()
{
	signal(SIGINT,sig);
	signal(SIGQUIT,sig);
	while(1)
	{
		if(count>=10)
			break;
	}
	return 0;
}
