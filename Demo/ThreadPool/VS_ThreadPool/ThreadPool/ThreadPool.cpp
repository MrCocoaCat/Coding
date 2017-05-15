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
	//У�����
	if(lMaxThreadNumber < lMinThreadNumber || lMinThreadNumber <= 0)
		return false;
	//�����߳�������Դ���������������ź���
	m_hSemaphore = CreateSemaphore(NULL,0,lMaxThreadNumber,NULL);
	//�˳����
	IsExit = false;
	//�����̣߳���С�߳���
	for(int i = 0; i < lMinThreadNumber ; i++)
	{
		HANDLE m_hThread = (HANDLE)_beginthreadex(NULL,0,&ThreadProc,this,0,NULL);
		//���߳̾������������й���
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
	//����˳����Ϊ��
	while(pThis->IsExit == false)
	{
		//���ź�
		WaitForSingleObject(pThis->m_hSemaphore,INFINITE);
		//�ȵ����� ׼��ִ��	�����е��߳�������һ	
		pThis->m_RunThreadNum++;
		//ִ��
		EnterCriticalSection(&cs); //����ؼ���
		//��������в�Ϊ�գ���ѭ��ִ��
		while(pThis->m_quItask.empty() == false)
		{			
			//ȡ��������еĵ�һ������,��ֵ��pItask
			pItask = pThis->m_quItask.front();
			pThis->m_quItask.pop();			
			//������߳�������
			pItask->Run();
			//����֮��ɾ������
			delete pItask;
			pItask = NULL;
		}
		LeaveCriticalSection(&cs); //�˳��ؼ���
		//ִ�������� ������Ϣ״̬
		//���е��߳�������һ
		pThis->m_RunThreadNum--;		
	}
	return 0;
}

void ThreadPool::DestoryThreadPool()
{
	IsExit = true;
	//�����߳���Դ
	list<HANDLE>::iterator ite = m_lstThread.begin();
	while(ite != m_lstThread.end())
	{
		//ӦΪIsExit����Ѿ�����Ϊtrue,���ʱ����𲽵��˳�
		//�ȴ��߳̽��� �����ʱ
		if(WAIT_TIMEOUT == WaitForSingleObject(*ite,100))
		{
			//��һ�ᣬ��δ�˳���ǿ��ɱ��
			TerminateThread(*ite,-1);
		}
		CloseHandle(*ite);
		*ite = NULL;
		++ite;
	}
	//�������
	m_lstThread.clear(); 
	//�����ź���
	if(m_hSemaphore)
	{
		CloseHandle(m_hSemaphore);
		m_hSemaphore = NULL;
	}
	//ɾ���ؼ���
	DeleteCriticalSection(&cs);
}

bool ThreadPool::PushItask(Itask* Itask)
{
	if(Itask == NULL) 
		return false;

	//���������������� C++��֧�ֶ��̲߳��� ����ͬʱ�Զ��н���push��pop
	EnterCriticalSection(&cs);
	m_quItask.push(Itask);
	LeaveCriticalSection(&cs);
	//�ͷ��ź�
	//����п����߳� �ͷ��ź���
	if(m_RunThreadNum < m_CreateThreadNum)
	{
		ReleaseSemaphore(m_hSemaphore,1,NULL);
	}
		//���û�п����߳� ������CPU���� �������̲߳��ͷ��ź��� 
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
		//���û���̻߳�CPU��Դ�˵ȴ�
	else
	{
		//û���������
	}
	return true;
}