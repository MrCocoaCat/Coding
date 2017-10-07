#include "ThreadPool.h"
#include <process.h>


ThreadPool::ThreadPool(void)
{
	m_FlagQuit = false;
	m_hSemphore = NULL;
	m_lCreateThreadNum = 0;
	m_lRunThreadNum = 0;
	m_lMaxThreadNum = 0;
}


ThreadPool::~ThreadPool(void)
{
}

bool ThreadPool::CreateThreadPool(long lMinThreadNum,long lMaxThreadNum)
{
	if(lMinThreadNum < 0 || lMaxThreadNum < lMinThreadNum)
	{
		return false;
	}

	//初始化变量
	m_FlagQuit = true;
	m_hSemphore = CreateSemaphore(NULL,0,lMaxThreadNum,NULL);

	//创建线程

	for(int i=0; i<lMinThreadNum; i++)
	{
		HANDLE handle = (HANDLE)_beginthreadex(NULL,0,&ThreadProc,this,0,NULL);
		if(handle)
		{

			m_lstHandle.push_back(handle);
		}
	}

	m_lMaxThreadNum = lMaxThreadNum;
	m_lCreateThreadNum = lMinThreadNum;
	return true;
}

void ThreadPool::DestoryThreadPool()
{
	m_FlagQuit = false;
	std::list<HANDLE>::iterator ite = m_lstHandle.begin();
	while(ite != m_lstHandle.end())
	{
		if(WaitForSingleObject(*ite,100)== WAIT_TIMEOUT)
		{
			TerminateThread(*ite,-1);
		}
		CloseHandle(*ite);
		*ite=NULL;
		ite++;
	}
	m_lstHandle.clear();
	if(m_hSemphore)
	{
		CloseHandle(m_hSemphore);
		m_hSemphore=NULL;
	}

}

unsigned _stdcall ThreadPool::ThreadProc (void *lpvoid)
{
	ThreadPool *pthis = (ThreadPool *)lpvoid;
	Itask *pItask = NULL;
	while(pthis->m_FlagQuit)
	{
		//等信号
		WaitForSingleObject(pthis->m_hSemphore,INFINITE);
		InterlockedIncrement(&pthis->m_lRunThreadNum);
		while(!pthis->m_qItask.empty())
		{
			pthis->m_MyLock.Lock();
			pItask = pthis->m_qItask.front();
			pthis->m_qItask.pop();
			pthis->m_MyLock.UnLock();
			pItask->RunItask();
		}

		//执行任务
		InterlockedDecrement(&pthis->m_lRunThreadNum);
	}
	return 0;
}

bool ThreadPool::PushItask(Itask *pItask)
{
	if(NULL == pItask)
	{
		return false;
	}
	m_MyLock.Lock();
	m_qItask.push(pItask);
	m_MyLock.UnLock();
	if(m_lRunThreadNum < m_lCreateThreadNum)
	{
		ReleaseSemaphore(m_hSemphore,1,NULL);
	}
	else if(m_lCreateThreadNum < m_lMaxThreadNum)
	{
		HANDLE handle = (HANDLE)_beginthreadex(NULL,0,&ThreadProc,this,0,NULL);
		if(handle)
		{
			m_lstHandle.push_back(handle);
		}
		m_lCreateThreadNum++;
		ReleaseSemaphore(m_hSemphore,1,NULL);
	}
	else
	{
		//等待
		return false;
	}

	return true;
}
