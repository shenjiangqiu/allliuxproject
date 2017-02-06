 ///
 /// @file    test2.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-02 15:12:40
 ///
 
#include <iostream>
using std::cout;
using std::endl;
class A
{
	public:
		A(int a,int b)
		{
			cout<<"A!"<<endl;
		}
};
class B
{
	public:
		B(int a,int b){
		cout<<"B!"<<endl;
		}
};
class TEST
{
	private:
		A a;
		B b;
	public:
		//TEST():a(),b(){
		//cout<<"test!"<<endl;
		//}
		TEST():a(1,2),b(3,4){
		}
};

int main()
{
	TEST tst;
	return 0;
}

