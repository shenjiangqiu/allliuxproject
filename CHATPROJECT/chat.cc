///
/// @file    char.cc
/// @author  shenjiangqiu(ivy22233qiu@live.com)
/// @date    2017-02-06 21:06:30
///

#include"head.h"
int main(int argc,char **argv)
{
	if(argc!=3)
	{
		cout<<"invalid number of args!"<<endl;
		return -1;
	}
	if(strcmp(argv[1],"c")&&strcmp(argv[1],"s"))
	{
		cout<<"mode must be c=chart s=show"<<endl;
		return -1;
	}
	if(strcmp(argv[2],"u1")&&strcmp(argv[2],"u2"))
	{
		cout<<"user name must be u1 or u2!"<<endl;
		return -1;
	}
	return ShowWindow(argv);
	
}
