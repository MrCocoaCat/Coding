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
	m_hSemphore = CreateSemaphore(NULL,0,lMaxThreadNum,NULL); //创建最大线程数量的信号量

	//创建线程

	for(int i=0; i<lMinThreadNum; i++) //开启最小线程数量
	{
		HANDLE handle = (HANDLE)_beginthreadex(NULL,0,&ThreadProc,this,0,NULL); //将这个指针作为传入参数，回调函数
		if(handle)
		{
			m_lstHandle.push_back(handle); //如果创建成功，则放入队列中进行管理
		}
	}
	//给成员函数赋值
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
			TerminateThread(*ite,-1); //强制关闭
		}

		CloseHandle(*ite); //关线程句柄
		*ite=NULL;
		ite++;
	}

	m_lstHandle.clear(); //清空队列

	if(m_hSemphore)//关闭信号量
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
		InterlockedIncrement(&pthis->m_lRunThreadNum); //原子操作
		while(!pthis->m_qItask.empty())
		{
			pthis->m_MyLock.Lock(); 

			pItask = pthis->m_qItask.front();//从任务队列中拿任务
			pthis->m_qItask.pop();

			pthis->m_MyLock.UnLock();

			pItask->RunItask();//执行任务
		}

		
		InterlockedDecrement(&pthis->m_lRunThreadNum); //原子操作
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
	if(m_lRunThreadNum < m_lCreateThreadNum) //正在运行的线程数量 小于 创建的线程数量，释放信号量 
	{
		ReleaseSemaphore(m_hSemphore,1,NULL);
	}
	else if(m_lCreateThreadNum < m_lMaxThreadNum)  //创建线程数量 小于 最大线程数量，则创建线程
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
