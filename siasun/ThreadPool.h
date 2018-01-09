#pragma once

#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include <iostream>
#include <queue>
#include <list>
#include<pthread.h>
#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <semaphore.h>
#include"MyLock.h"

using namespace std;

class Itask
{
public:
	Itask( ){};
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

	bool CreateThreadPool(long lThreadNumber);
	void DestoryThreadPool();
	static void * ThreadProc(void * lpParameter);
	bool PushItask(Itask* Itask);
	bool SetFind(string path,string name);
	bool SetFlag();
	bool JudgeFlag();
public:
	queue<Itask*> m_qItask;
    CMyLock * m_PathLock;
    queue<string> * m_qFindPath;
    string m_FindFile;

private:
	bool m_FindFlag;
	bool m_FlagQuit;
    CMyLock m_MyLock;
    list<pthread_t> m_lstThread;
};