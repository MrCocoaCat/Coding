#pragma once 
#include <Windows.h>


class CMyLock
{
private:
	CRITICAL_SECTION m_cs;
public:
	CMyLock()
	{
		InitializeCriticalSection(&m_cs);
	}
	~CMyLock()
	{
		DeleteCriticalSection(&m_cs);
	}
	void Lock()
	{
		EnterCriticalSection(&m_cs);
	}
	void UnLock()
	{
		LeaveCriticalSection(&m_cs);
	}
};

class CAutoLock
{
public:
	CAutoLock(CMyLock* lock)
	{
		m_myLock = lock;
		if (m_myLock)
		{
			m_myLock->Lock();
		}
	}
	~CAutoLock()
	{
		if (m_myLock)
		{
			m_myLock->UnLock();
		}

	}
private:
	CMyLock* m_myLock;
};
