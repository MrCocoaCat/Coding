#include<iostream>
#include <windows.h>
#include "ThreadPool.h"
//#include "Sys.h"
using namespace std;

class AddItask:public Itask
{
public:
	AddItask(int a,int b)
	{
		m_a = a;
		m_b = b;
	}
private:
	int m_a;
	int m_b;
public:
	void Run()
	{
		cout << m_a << "+" << m_b << "=" << m_a + m_b << endl;
		Sleep(1000);
	}
};



int main()
{
	ThreadPool tp;
	tp.CreateThreadPool(4,2);

	Itask *pItask;
	for(int i = 0 ; i < 10; i++)
	{
		pItask = new AddItask(i,i+1);
		tp.PushItask(pItask);
	}

	system("pause");
	return 0;
}