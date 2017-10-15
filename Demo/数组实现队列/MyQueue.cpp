#pragma once


#include<iostream>
#ifndef MYQUEUE_H
#define MYQUEUE_H

template <typename T>
class CMyQueue
{
public:
	CMyQueue();
	~CMyQueue();
	//��ʼ������
	bool InitQueue(long nLength);
	//�������
	bool Push(T* node);
	//�ó�����
	bool Pop(T*& node);
	//���г���
	long GetQueueLen();
	//���ٶ���
	bool UninitQueue();
private:
	//��̬����
	T** m_Queue;
	//ͷ����
	long m_pHeadIndex;
	//β����
	long m_pTailIndex;
	//��ʼ�����
	bool m_flag;
	//���г���
	long m_QueueLen;
	//��
//	CLock m_lock;
};

//-------------------------------------------------------------
template <typename T>
CMyQueue<T>::CMyQueue():m_Queue(NULL), m_pHeadIndex(0), m_pTailIndex(0),
m_flag(true), m_QueueLen(0)
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
bool CMyQueue<T>::InitQueue(long nLength)
{
	UninitQueue();
	if (nLength <= 0)
	{
		return false;
	}
	m_Queue = new T*[nLength + 1];
	memset(m_Queue, 0, sizeof(m_Queue));
	m_QueueLen = nLength + 1;
	m_flag = true;
	return true;
}

//-------------------------------------------------------------
//�������
template <typename T>
bool CMyQueue<T>::Push(T* node)
{
	//У�����
	if (!node)
		return false;
	//�Ƿ��ʼ������
	if (m_flag == false)
		return false;
	long m_pNextIndex = (m_pHeadIndex + 1) % m_QueueLen;
	//CAutoLock lock(&m_lock);
	//������Ϊ��
	if (m_pNextIndex == m_pTailIndex)
		return false;
	else
	{
		//�Ƿ������ѭ������
		/*if (m_Queue[m_pHeadIndex])
		{
			delete m_Queue[m_pHeadIndex];
			m_Queue[m_pHeadIndex] = NULL;
		}*/
		m_Queue[m_pHeadIndex] = node;
		m_pHeadIndex = m_pNextIndex;
	}
	return true;
}

//-------------------------------------------------------------
//�Ӷ���ȡ��
template <typename T>
bool CMyQueue<T>::Pop(T*& node)
{
	//�Ƿ��ʼ������
	if (m_flag == false)
		return false;
	//������Ϊ��
	//CAutoLock lock(&m_lock);
	if (m_pHeadIndex == m_pTailIndex)
		return false;
	else
	{
		node = m_Queue[m_pTailIndex];
		m_Queue[m_pTailIndex] = NULL;
		m_pTailIndex = (m_pTailIndex + 1) % m_QueueLen;
	}
	return true;
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
bool CMyQueue<T>::UninitQueue()
{
	//�Ƿ��ʼ������
	if (m_flag == false)
		return -1;
	for (int i = 0; i < m_QueueLen; ++i)
	{
		if (m_Queue[i])
		{
			delete m_Queue[i];
			m_Queue[i] = NULL;
		}
	}
	delete[] m_Queue;
	m_Queue = NULL;
	return true;
}

#endif //!MYQUEUE_H
int main()
{

	CMyQueue<int> qu;
	qu.InitQueue(4);

	bool ret =qu.Push(new int (1));
	ret=qu.Push(new int (2));
	std::cout<<ret<<std::endl;
	ret=qu.Push(new int (3));
	std::cout<<ret<<std::endl;
	ret=qu.Push(new int (4));
	std::cout<<ret<<std::endl;
	ret=qu.Push(new int (5));
	std::cout<<ret<<std::endl;
	int * p = new int; 
	qu.Pop(p);
	std::cout<<*p<<std::endl;
	qu.Pop(p);
	std::cout<<*p<<std::endl;
	system("pause");
	return 0;
}