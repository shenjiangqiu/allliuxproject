#include<iostream>
using std::cout;
using std::endl;
	
class point
{
	private:
		int a;
		int b;
	public:
		void set(const  int sa,const int sb);
		point();
		point(const int sa,const int sb){a=sa;b=sb;}
		~point(){}
		void show()const{cout<<"a= "<<a<<" b= "<<b<<endl;}
};
int main()
{
	const point mp;
	
	mp.show();
	const point hp(3,4);
	hp.show();
	//mp.set(3,4);
	//mp.show();
	point *kp=new point[2](point(3,4));
	kp[1].show();
	kp[0].show();
	return 0;

}
point::point()
{
	a=0;
	b=0;
}
void point::set(int sa,int sb)
{
	a=sa;
	b=sb;
}
