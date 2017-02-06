///
/// @file    test.cc
/// @author  shenjiangqiu(ivy22233qiu@live.com)
/// @date    2017-02-04 09:50:24
///

#include <iostream>
using std::cout;
using std::endl;
class A
{
	private:
		int _a;
	public:
		//A(int)
		
		A(const int &a):_a(a){}

		//A(A)
		
		A(const A &cp):_a(cp._a){}

		void print() const{
			cout<<_a<<endl;
		}

		A& operator =(const A &tp)
		{
			if(this!=&tp)//!!!
			{
			this->_a=tp._a;
			}
			return *this;
		}

		void set(const int &a){
			_a=a;
		}
		
};
int main()
{
	A a(3);
	a.print();
	A b(a);
	b.print();
	a.set(5);
	a.print();
	b=a;
	b.print();

	return 0;
}
