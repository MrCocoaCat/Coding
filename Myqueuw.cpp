#pragma once


#include<iostream>
#ifndef MYQUEUE_H
#define MYQUEUE_H
typedef int BOOL;
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
//初始化队列
template <typename T>
BOOL CMyQueue<T>::InitQueue(long nLength)
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
//放入队列
template <typename T>
BOOL CMyQueue<T>::Push(T* node)
{
	//校验参数
	if (!node)
		return false;
	//是否初始化队列
	if (m_flag == false)
		return false;
	long m_pNextIndex = (m_pHeadIndex + 1) % m_QueueLen;
	//CAutoLock lock(&m_lock);
	//队列满为空
	if (m_pNextIndex == m_pTailIndex)
		return false;
	else
	{
		//是否进到了循环队列
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
//从队列取出
template <typename T>
BOOL CMyQueue<T>::Pop(T*& node)
{
	//是否初始化队列
	if (m_flag == false)
		return false;
	//队列满为空
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