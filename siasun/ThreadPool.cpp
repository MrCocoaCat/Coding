#include "ThreadPool.h"
using namespace std;


ThreadPool::ThreadPool(void)
{
	m_FlagQuit = false;
	m_PathLock = new CMyLock;
    m_qFindPath = new queue<string> ;
	m_FindFlag = false;
}

ThreadPool::~ThreadPool(void)
{
	if(m_PathLock == nullptr)
	{
		delete(m_PathLock);
	}
	if(m_qFindPath == nullptr)
	{
		delete(m_qFindPath);
	}

}

bool ThreadPool::CreateThreadPool(long lThreadNumber)
{
	this->m_FlagQuit = true;
	for(int i = 0; i < lThreadNumber; i++)
	{
		pthread_t  thread_id;
        pthread_create(&thread_id, nullptr, &ThreadProc, (void*)this);
        m_lstThread.push_back(thread_id);
	}
	return true;
}
bool ThreadPool::SetFind(string path,string name)
{
	this->m_PathLock->Lock();

    cout<< "压入路径 "  <<path<<endl;
	this->m_qFindPath->push(path);
    cout<<m_qFindPath->size()<<endl;

	this->m_PathLock->UnLock();
	this->m_FindFile = name;

	return true;
}
bool ThreadPool::SetFlag()
{
	this->m_FindFlag = true;
}
bool ThreadPool::JudgeFlag()
{
	return(this->m_FindFlag);
}

void * ThreadPool::ThreadProc (void *lpvoid)
{
	ThreadPool *pthis = (ThreadPool *)lpvoid;
	Itask *pItask = nullptr;
	while(pthis->m_FlagQuit != 0)
	{
		while(!pthis->m_qItask.empty())
		{
			pItask = pthis->m_qItask.front();

			pthis->m_MyLock.Lock();
			pthis->m_qItask.pop();
			pthis->m_MyLock.UnLock();

			pItask->RunItask(); //线程运行,
		}
	}
	return nullptr;
}

bool ThreadPool::PushItask(Itask *pItask)
{
	if(nullptr == pItask)
	{
		return false;
	}
	m_MyLock.Lock();
	m_qItask.push(pItask);
	m_MyLock.UnLock();
}


void ThreadPool::DestoryThreadPool()
{
	m_FlagQuit = false;
	auto ite = m_lstThread.begin();
	while(ite != m_lstThread.end())
	{
		pthread_join(*ite,NULL);
		ite++;
	}
    m_lstThread.clear();
}
