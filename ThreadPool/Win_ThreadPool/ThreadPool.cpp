#include "ThreadPool.h"
#include <Process.h>

CRITICAL_SECTION cs;

ThreadPool::ThreadPool(void)
{
	m_hSemaphore = NULL;
	m_RunThreadNum = 0;
	m_CreateThreadNum = 0;
	m_MaxThreadNum = 0;
	IsExit = true;
	InitializeCriticalSection(&cs);
}


ThreadPool::~ThreadPool(void)
{
}

bool ThreadPool::CreateThreadPool(long lMaxThreadNumber,long lMinThreadNumber)
{
	//校验参数
	if(lMaxThreadNumber < lMinThreadNumber || lMinThreadNumber <= 0)
		return false;
	//创建线程所需资源
	m_hSemaphore = CreateSemaphore(NULL,0,lMaxThreadNumber,NULL);
	IsExit = false;
	//创建线程
	for(int i = 0; i < lMinThreadNumber ; i++)
	{
		HANDLE m_hThread = (HANDLE)_beginthreadex(NULL,0,&ThreadProc,this,0,NULL);
		if(m_hThread)
		{
			m_lstThread.push_back(m_hThread);
		}
	}
	m_CreateThreadNum = lMinThreadNumber;
	m_MaxThreadNum = lMaxThreadNumber;
	return true;
}

unsigned __stdcall ThreadPool::ThreadProc(void * lpParameter)
{
	ThreadPool *pThis = (ThreadPool*)lpParameter;
	Itask* pItask = NULL;

	while(pThis->IsExit == false)
	{
		//等信号
		WaitForSingleObject(pThis->m_hSemaphore,INFINITE);
		//等到任务 准备执行		

		pThis->m_RunThreadNum++;
		//执行
		EnterCriticalSection(&cs);
		while(pThis->m_quItask.empty() == false)
		{			
			pItask = pThis->m_quItask.front();
			pThis->m_quItask.pop();			

			pItask->Run();
			
			delete pItask;
			pItask = NULL;
		}
		LeaveCriticalSection(&cs);
		//执行完任务 进入休息状态
		pThis->m_RunThreadNum--;		
	}
	return 0;
}

void ThreadPool::DestoryThreadPool()
{
	IsExit = true;
	//销毁线程资源
	list<HANDLE>::iterator ite = m_lstThread.begin();
	while(ite != m_lstThread.end())
	{
		//等待线程结束 如果超时
		if(WAIT_TIMEOUT == WaitForSingleObject(*ite,100))
		{
			TerminateThread(*ite,-1);
		}
		CloseHandle(*ite);
		*ite = NULL;
		++ite;
	}
	m_lstThread.clear();
	//销毁信号量
	if(m_hSemaphore)
	{
		CloseHandle(m_hSemaphore);
		m_hSemaphore = NULL;
	}
	DeleteCriticalSection(&cs);
}

bool ThreadPool::PushItask(Itask* Itask)
{
	if(Itask == NULL) 
		return false;

	//将任务加入任务队列 C++不支持多线程操作 不能同时对队列进行push和pop
	EnterCriticalSection(&cs);
	m_quItask.push(Itask);
	LeaveCriticalSection(&cs);
	//释放信号
	//如果有空闲线程 释放信号量
	if(m_RunThreadNum < m_CreateThreadNum)
	{
		ReleaseSemaphore(m_hSemaphore,1,NULL);
	}
		//如果没有空闲线程 但是有CPU空闲 创建新线程并释放信号量 
	else if(m_RunThreadNum < m_MaxThreadNum)
	{
		m_CreateThreadNum++;
		HANDLE m_hThread = (HANDLE)_beginthreadex(NULL,0,&ThreadProc,this,0,NULL);
		if(m_hThread)
		{
			m_lstThread.push_back(m_hThread);
		}
		ReleaseSemaphore(m_hSemaphore,1,NULL);
	}
		//如果没有线程或CPU资源了等待
	else
	{
		//没有特殊操作
	}
	return true;
}