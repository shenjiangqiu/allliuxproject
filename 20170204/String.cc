 ///
 /// @file    String.cc
 /// @author  shenjiangqiu(ivy22233qiu@live.com)
 /// @date    2017-02-04 10:08:59
 ///
#include<string.h>
#include <iostream>
using std::cout;
using std::endl;
using std::cin;
class String
{
	private:
		char * _buf;
		int _size;
		int _space;
	public:
		String();
		String(const char *);
		String(const String &);
		~String();
		String & operator =(const String& cp);
		friend String operator +(const String &a,const String &b);	
		friend String operator +(const String &a,const char *b);
		//friend String operator +(const char *,const String &b);
		friend std::ostream& operator <<(std::ostream &ost,const String &a);
		friend std::istream& operator >>(std::istream &ist,String &a);
};
int main()
{
	String st1("hello");
	String st2("world!");
	String st3;
	st3=st1+" "+st2;
	st3=" "+st3;
	cout<<st3<<endl;
	String st4;
	cin>>st4;
	cout<<"st4: "<<st4<<endl;
	return 0; 
}

String::String():_buf(new char[10]),_size(0),_space(10){}

String::String(const char * buf)
:_buf(new char[strlen(buf)+1])
,_size(strlen(buf))
,_space(strlen(buf)+1)
{
	strcpy(_buf,buf);

}

String::String(const String & cp):
_buf(new char[cp._space])
,_size(cp._size)
,_space(cp._space)
{
	strcpy(_buf,cp._buf);
}

String::~String()
{
	if(_space!=0)
		delete[] _buf;
}

String& String::operator=(const String& cp)
{
	if(this!=&cp)
	{
		if(this->_space!=0)
			delete[] _buf;
		this->_size=cp._size;
		this->_space=cp._space;
		this->_buf=new char[this->_space];
		strcpy(_buf,cp._buf);
	}
	return *this;
}

String operator +(const String& a,const String& b)
{
	String tmp;
	delete[] tmp._buf;
	tmp._buf=new char[a._size+b._size+1];
	tmp._size=a._size+b._size;
	tmp._space=a._size+b._size+1;
	strcpy(tmp._buf,a._buf);
	strcat(tmp._buf,b._buf);
	return tmp;
}

String operator +(const String &a,const char *b)
{
	String tmp;
	delete[] tmp._buf;
	tmp._size=a._size+strlen(b);
	tmp._space=tmp._size+1;
	tmp._buf=new char[tmp._space];
	strcpy(tmp._buf,a._buf);
	strcat(tmp._buf,b);
	return tmp;
}
/*String operator +(const char *b,const String &a)
{	
	String tmp;
	delete[] tmp._buf;
	tmp._size=a._size+strlen(b);
	tmp._space=tmp._size+1;
	tmp._buf=new char[tmp._space];
	strcpy(tmp._buf,b);
	strcat(tmp._buf,a._buf);
	return tmp;


}*/
std::ostream& operator <<(std::ostream &ost,const String &a)
{
	ost<<a._buf;
	return ost;
}
std::istream& operator >>(std::istream &ist,String &a)
{
	char buf[100];
	ist>>buf;
	String tmp(buf);
	a=tmp;
	return ist;
}
