#include<iostream>
using namespace std;
class CA
{
	private:
		static CA *pA;
		int x;
		int y;
		CA(int x = 0, int y = 0)
		{
			this->x = x;
			this->y = y;
			cout << "构造函数被调用" << this << endl;
		}	
	public:
		static CA* GetInstance(int x = 0, int y = 0)
		{
			if(pA == NULL)
			{
				pA = new CA(x, y);
			}
			return pA;
		}
		void disp() const
		{
			cout << "(" << this->x << "," << this->y << ")" << endl;
		}
};
CA* CA::pA = NULL;//静态成员要在外面初始化
int main()
{
	CA *p1 = CA::GetInstance(3, 4);
	CA *p2 = CA::GetInstance(2, 1);
	CA *p3 = CA::GetInstance(6, 2);
	cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;
	p1->disp();
	p2->disp();
	p3->disp();
	return 0;
}
//此时p1、p2、p3是同一个，输出来的值相等，所以调用disp都输出同样的内容


