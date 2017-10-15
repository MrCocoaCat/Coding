#pragma once

#include "MyLock.h"

#ifndef MYQUEUE_H
#define MYQUEUE_H

template <typename T>
class CMyQueue
{
public:
	CMyQueue();
	~CMyQueue();
	//初始化队列
	BOOL InitQueue(long nLength);
	//放入队列
	BOOL Push(T* node);
	//拿出队列
	BOOL Pop(T*& node);
	//队列长度
	long GetQueueLen();
	//销毁队列
	BOOL UninitQueue();
private:
	//动态数组
	T** m_Queue;
	//头索引
	long m_pHeadIndex;
	//尾索引
	long m_pTailIndex;
	//初始化标记
	BOOL m_flag;
	//队列长度
	long m_QueueLen;
	//锁
	CMyLock m_lock;
};

//-------------------------------------------------------------
template <typename T>
CMyQueue<T>::CMyQueue():m_Queue(NULL), m_pHeadIndex(0), m_pTailIndex(0),
m_flag(FALSE), m_QueueLen(0)
{

}

//-------------------------------------------------------------
template <typename T>
CMyQueue<T>::~CMyQueue()
{

}

//-------------------------------------------------------------
//初始化队列
template <typename T>
BOOL CMyQueue<T>::InitQueue(long nLength)
{
	UninitQueue();
	if (nLength <= 0)
	{
		return FALSE;
	}
	m_Queue = new T*[nLength + 1];
	memset(m_Queue, 0, sizeof(m_Queue));
	m_QueueLen = nLength + 1;
	m_flag = TRUE;
	return TRUE;
}

//-------------------------------------------------------------
//放入队列
template <typename T>
BOOL CMyQueue<T>::Push(T* node)
{
	//校验参数
	if (!node)
		return FALSE;
	//是否初始化队列
	if (m_flag == FALSE)
		return FALSE;
	long m_pNextIndex = (m_pHeadIndex + 1) % m_QueueLen;
	CAutoLock lock(&m_lock);
	//队列满为空
	if (m_pNextIndex == m_pTailIndex)
		return FALSE;
	else
	{
		m_Queue[m_pHeadIndex] = node;
		m_pHeadIndex = m_pNextIndex;
	}
	return TRUE;
}

//-------------------------------------------------------------
//从队列取出
template <typename T>
BOOL CMyQueue<T>::Pop(T*& node)
{
	//是否初始化队列
	if (m_flag == FALSE)
		return FALSE;
	//队列满为空
	CAutoLock lock(&m_lock);
	if (m_pHeadIndex == m_pTailIndex)
		return FALSE;
	else
	{
		node = m_Queue[m_pTailIndex];
		m_Queue[m_pTailIndex] = NULL;
		m_pTailIndex = (m_pTailIndex + 1) % m_QueueLen;
	}
	return TRUE;
}

//-------------------------------------------------------------
//得到队列长度
template <typename T>
long CMyQueue<T>::GetQueueLen()
{
	//是否初始化队列
	if (m_flag == FALSE)
		return -1;
	long iQueueLen = (m_pHeadIndex - m_pTailIndex + m_QueueLen) % m_QueueLen;
	return iQueueLen;
}

//-------------------------------------------------------------
//销毁队列
template <typename T>
BOOL CMyQueue<T>::UninitQueue()
{
	//是否初始化队列
	if (m_flag == FALSE)
		return -1;
	/*for (int i = 0; i < m_QueueLen; ++i)
	{
		if (m_Queue[i])
		{
			delete m_Queue[i];
			m_Queue[i] = NULL;
		}
	}*/
	delete[] m_Queue;
	m_Queue = NULL;
	return TRUE;
}

#endif //!MYQUEUE_H
