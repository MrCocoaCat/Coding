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
	//��ʼ������
	BOOL InitQueue(long nLength);
	//�������
	BOOL Push(T* node);
	//�ó�����
	BOOL Pop(T*& node);
	//���г���
	long GetQueueLen();
	//���ٶ���
	BOOL UninitQueue();
private:
	//��̬����
	T** m_Queue;
	//ͷ����
	long m_pHeadIndex;
	//β����
	long m_pTailIndex;
	//��ʼ�����
	BOOL m_flag;
	//���г���
	long m_QueueLen;
	//��
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
//��ʼ������
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
//�������
template <typename T>
BOOL CMyQueue<T>::Push(T* node)
{
	//У�����
	if (!node)
		return FALSE;
	//�Ƿ��ʼ������
	if (m_flag == FALSE)
		return FALSE;
	long m_pNextIndex = (m_pHeadIndex + 1) % m_QueueLen;
	CAutoLock lock(&m_lock);
	//������Ϊ��
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
//�Ӷ���ȡ��
template <typename T>
BOOL CMyQueue<T>::Pop(T*& node)
{
	//�Ƿ��ʼ������
	if (m_flag == FALSE)
		return FALSE;
	//������Ϊ��
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
//�õ����г���
template <typename T>
long CMyQueue<T>::GetQueueLen()
{
	//�Ƿ��ʼ������
	if (m_flag == FALSE)
		return -1;
	long iQueueLen = (m_pHeadIndex - m_pTailIndex + m_QueueLen) % m_QueueLen;
	return iQueueLen;
}

//-------------------------------------------------------------
//���ٶ���
template <typename T>
BOOL CMyQueue<T>::UninitQueue()
{
	//�Ƿ��ʼ������
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
