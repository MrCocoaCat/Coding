//设计一个类，只能创建一个实例

#include<iostream>
#include<pthread.h>
using namespace std;
//lazy man
class singleton
{
	protected:
		singleton()
		{
			pthread_mutex_init(&mutex,NULL) ;
		}
		singleton & operator =(singleton &singl);
	private:
		static singleton* p;
	public:
		static singleton* initance();
		static pthread_mutex_t mutex;
		void PRINT()
		{
			cout<<"sigleton 1"<<endl; 
		}
};
singleton* singleton::p = NULL;
pthread_mutex_t singleton::mutex;
singleton* singleton::initance()
{
//need  metux lock
	
	if (p == NULL)
	{
		pthread_mutex_lock(&mutex);
		if(p==NULL);
		p = new singleton();
		pthread_mutex_unlock(&mutex);
		
	}
	return p;
}



//hungery man
//在定义的时候就实例化,推荐写法
class singleton2
{
	protected:
		singleton2(){}
	private:	
		static singleton2* p;
	public:
		static singleton2* initance();
		void PRINT()
		{
			cout<<"sigleton 2   :"<<endl; 
		}
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
	p1->PRINT();
//	delete p1;
	cout<<p1<<endl<<p2<<endl;
	
	if(p1==p2)
	{
		cout<<"right"<<endl;
	}
	singleton * p11=singleton::initance();
	p11->PRINT();
	singleton * p22=singleton::initance();
	p22->PRINT();
	delete p11;
	cout<<p11<<endl<<p22<<endl;
	

}
