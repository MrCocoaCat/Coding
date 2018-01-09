#pragma once
#include <queue>
#include <list>
#include<pthread.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <iostream>
#include <semaphore.h>
#include"MyLock.h"
using namespace std;

class Itask
{
public:
	Itask(){};
	virtual ~Itask(){};
public:
	virtual void RunItask() = 0;
};

class ThreadPool
{
public:
	ThreadPool(void);
	~ThreadPool(void);
public:

	bool CreateThreadPool(long lMaxThreadNumber,long lMinThreadNumber);

	void DestoryThreadPool();

	static void * ThreadProc(void * lpParameter);
	bool PushItask(Itask* Itask);
public:
	queue<Itask*> m_qItask;
private:
	//HANDLE m_hSemaphore;
	sem_t sem;
	list<pthread_t> m_lstHandle;
	bool m_FlagQuit;
	long m_lRunThreadNum;
	long m_lCreateThreadNum;
	long m_lMaxThreadNum;
    CMyLock m_MyLock;
};