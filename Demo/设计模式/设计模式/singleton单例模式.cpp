#include<iostream>
#include<windows.h>
#include<mutex> 
using namespace std;
//懒汉模式
class singleton
{
protected:
    singleton()
    {
       
    }
	singleton & operator =(singleton &singl);
private:
    static singleton* p;
public:
    static std::mutex mtx ;
	static singleton* initance()
	{
	
		if (p == NULL)
		{
			mtx.lock();
			if (p == NULL)
				p = new singleton();
			mtx.unlock();
		}
		return p;
	}
};
singleton* singleton::p = NULL;

//饿汉模式
class singleton2
{
protected:
	singleton2(){}
private:	
	static singleton2* p;
public:
	static singleton2* initance();
};
singleton2* singleton2::p = new singleton2;
singleton2* singleton2::initance()
{
   return p; 
}



int main()
{

	singleton2 * p1=singleton2::initance();
	p1->PRINT();
	singleton2 * p2=singleton2::initance();
	delete p1;
	p1->PRINT();
	cout<<p1<<endl<<p2<<endl;

}
