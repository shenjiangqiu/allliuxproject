#include<iostream>
#include<string>
using namespace std;
int main()
{
	string a1("helloworld!");
	cout<<a1<<endl;
	string a2(a1);
	cout<<a2<<endl;
	a2.append(a2);
	cout<<a2<<endl;
	a2.insert(3,a2);
	cout<<a2<<endl;
	return 0;
}
