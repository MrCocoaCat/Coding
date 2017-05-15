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
	virtual ~Itask(){};//������ �Ա�ִ�����๹��
public:
	virtual void Run() = 0;//����ִ�к���
};

class ThreadPool
{
public:
	ThreadPool(void);
	~ThreadPool(void);
public:
	//1.�����̳߳�
	bool CreateThreadPool(long lMaxThreadNumber,long lMinThreadNumber);
	//2.�����̳߳�
	void DestoryThreadPool();
	//3.�̺߳���
	static unsigned __stdcall ThreadProc(void * lpParameter);
	//4.Ͷ������
	bool PushItask(Itask* Itask);
public:
	queue<Itask*> m_quItask; //�������
private:
	HANDLE m_hSemaphore; //�ź���
	list<HANDLE> m_lstThread; //�����߳̾��
	bool IsExit;
	long m_RunThreadNum;
	long m_CreateThreadNum;
	long m_MaxThreadNum;
    CMyLock m_lock;

};