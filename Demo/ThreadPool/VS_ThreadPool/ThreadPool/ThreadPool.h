#pragma once
#include <Windows.h>
#include <queue>
#include <list>
#include"MyLock.h"
using namespace std;

class Itask
{
public:
	Itask(){};
	virtual ~Itask(){};//虚析构 以便执行子类构造
public:
	virtual void Run() = 0;//任务执行函数
};

class ThreadPool
{
public:
	ThreadPool(void);
	~ThreadPool(void);
public:
	//1.创建线程池
	bool CreateThreadPool(long lMaxThreadNumber,long lMinThreadNumber);
	//2.销毁线程池
	void DestoryThreadPool();
	//3.线程函数
	static unsigned __stdcall ThreadProc(void * lpParameter);
	//4.投递任务
	bool PushItask(Itask* Itask);
public:
	queue<Itask*> m_quItask; //任务队列
private:
	HANDLE m_hSemaphore; //信号量
	list<HANDLE> m_lstThread; //管理线程句柄
	bool IsExit;
	long m_RunThreadNum;
	long m_CreateThreadNum;
	long m_MaxThreadNum;
    CMyLock m_lock;

};