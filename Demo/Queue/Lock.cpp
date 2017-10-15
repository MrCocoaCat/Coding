#pragma once

#ifndef CMYLOCK_H
#define CMYLOCK_H

#include <windows.h>

class CLock
{
public:
	CLock()
	{
		InitializeCriticalSection(&m_cs);
	}
	~CLock()
	{
		DeleteCriticalSection(&m_cs);
	}
	void Lock()
	{
		EnterCriticalSection(&m_cs);
	}
	void unLock()
	{
		LeaveCriticalSection(&m_cs);
	}
private:
	CRITICAL_SECTION m_cs;
};

class CAutoLock
{
public:
	CAutoLock(CLock* lock)
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
			m_myLock->unLock();
		}

	}
private:
	CLock* m_myLock;
};

#endif	//!CMYLOCK_H