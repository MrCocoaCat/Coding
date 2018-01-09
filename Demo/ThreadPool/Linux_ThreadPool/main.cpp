#include <iostream>
#include "ThreadPool.h"
using namespace std;

class AddItask :public Itask
{
private:
	int m_a;
	int m_b;
public:
	AddItask(int a,int b)
	{
		m_a = a;
		m_b = b;
	}
public:
	void RunItask()
	{
		cout << m_a << "+" << m_b << "=" << m_a + m_b << endl;
	}
};


class TestItask:public Itask
{
public:
	TestItask(int a,int b)
	{
		m_a = a;
		m_b = b;
	}
private:
	int m_a;
	int m_b;
public:
	void RunItask()
	{
        int a=0;
		for(int i=0;i<65530;i++)
		{
			for(int j=0;j<65530;j++)
			{
				a++;
			}
		}
		cout << m_a << "+" << m_b << "=" << m_a + m_b << endl;
        sleep(1);
	}
};
int main()
{
	ThreadPool tp;
	tp.CreateThreadPool(1,4);

	Itask *pItask;
	for(int i = 0 ; i < 10000 ; i++)
	{
		pItask = new TestItask(i,i+1);
		tp.PushItask(pItask);

	}
	return 0;
}