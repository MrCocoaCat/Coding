#pragma once
#include <Queue>
#include <list>

#include "MyLock.h"
#include "MyQueue.h"
#include <Windows.h>

class Itask
{
public:
	Itask()
	{

	}
	virtual ~Itask()
	{

	}
public:
	virtual void RunItask() = 0;
};


class ThreadPool
{
public:
	ThreadPool(void);
	~ThreadPool(void);
public:
	//1.�����̳߳�
	bool CreateThreadPool(long lMinThreadNum,long lMaxThreadNum);
	//2.�����̳߳�
	void DestoryThreadPool();
	//3.�̺߳���
	static unsigned _stdcall ThreadProc (void *lpvoid);
	//4.Ͷ������
	bool PushItask(Itask *);

	
private:
	CMyQueue<Itask > m_MyQueueItask;
	//std::queue<Itask *> m_qItask;
	std::list<HANDLE> m_lstHandle;
	HANDLE m_hSemphore;
	bool m_FlagQuit;
	long m_lCreateThreadNum;
	long m_lRunThreadNum;
	long m_lMaxThreadNum;
	CMyLock m_MyLock;
};

