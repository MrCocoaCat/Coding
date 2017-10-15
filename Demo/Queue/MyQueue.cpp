#pragma once
#include<iostream>
#include "Lock.h"
#include <queue>
#ifndef MYQUEUE_H
#define MYQUEUE_H
using namespace std;
template <typename T>
class CMyQueue
{
public:
	CMyQueue();
	~CMyQueue();
	//初始化队列
	bool InitQueue(long nLength);
	//放入队列
	bool Push(T* node);
	//拿出队列
	bool Pop(T*& node);
	//队列长度
	long GetQueueLen();
	//销毁队列
	bool UninitQueue();
private:
	//动态数组
	T** m_Queue;
	//头索引
	long m_pHeadIndex;  //构造赋值为0
	//尾索引
	long m_pTailIndex;  //构造赋值为0
	//初始化标记
	bool m_flag;
	//队列长度
	long m_QueueLen;
	//锁
	CLock m_lock;
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
//放入队列
template <typename T>
bool CMyQueue<T>::Push(T* node)
{
	//校验参数
	if (!node)
	{
		return false;
	}	
	//是否初始化队列
	if (m_flag == false)
	{
		return false;
	}	
	long m_pNextIndex = (m_pHeadIndex + 1) % m_QueueLen; //m_pHeadIndex + 1
	CAutoLock lock(&m_lock);
	//队列满
	if (m_pNextIndex == m_pTailIndex)//m_pNextIndex是下次存放的位置，如果等于尾，那么就没有位置放
	{
		return false;
	}
		
	else
	{
		/*if (m_Queue[m_pHeadIndex])
		{
			delete m_Queue[m_pHeadIndex];
			m_Queue[m_pHeadIndex] = NULL;
		}*/
		//先放后移动，支持双进程读写
		m_Queue[m_pHeadIndex] = node;  //放入新值
		m_pHeadIndex = m_pNextIndex; //队列头移位
	}
	return true;
}

//-------------------------------------------------------------
//从队列取出
template <typename T>
bool CMyQueue<T>::Pop(T* & node)
{
	//是否初始化队列
	if (m_flag == false)
		return false;
	//队列满为空
	CAutoLock lock(&m_lock);
	if (m_pHeadIndex == m_pTailIndex)
	{
		return false;
	}	
	else
	{
		node = m_Queue[m_pTailIndex]; //直接给节点赋值
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
bool CMyQueue<T>::UninitQueue()
{
	//是否初始化队列
	if (m_flag == false)
	{
		return -1;
	}
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
	CMyQueue<int> myQueue;
	myQueue.InitQueue(10000);
	
	DWORD startTime = GetTickCount();
	for (int i = 0; i < 1000; ++i)
	{
		for (int i = 0; i < 10; ++i)
		{
			int * node = new int(i);
			myQueue.Push(node);
		}
		for (int i = 0; i < 10; ++i)
		{
			int * node = new int(100);
			myQueue.Pop(node);
		//	cout<<*node<<endl;
			delete  node;
		}

	}
		
	std::cout << "use Time: " << GetTickCount() - startTime << std::endl;

	queue<int> Queue;
	startTime = GetTickCount();
	for (int i = 0; i < 1000; ++i)
	{
			for (int i = 0; i < 100; ++i)
		{
			int * node = new int(100);
			Queue.push(i);
		}
		for (int i = 0; i < 100; ++i)
		{
			int * node = new int(100);
			Queue.pop();
			
			delete  node;
		}
	}
	
	std::cout << "use Time: " << GetTickCount() - startTime << std::endl;

	system("pause");
	return 0;
}



//int main()
//{
//
//	CMyQueue<int> qu;
//	qu.InitQueue(4);
//
//	bool ret =qu.Push(new int (1));
//	ret=qu.Push(new int (2));
//	std::cout<<ret<<std::endl;
//	ret=qu.Push(new int (3));
//	std::cout<<ret<<std::endl;
//	ret=qu.Push(new int (4));
//	std::cout<<ret<<std::endl;
//	ret=qu.Push(new int (5));
//	std::cout<<ret<<std::endl;
//	int * p = new int; 
//	qu.Pop(p);
//	std::cout<<*p<<std::endl;
//	qu.Pop(p);
//	std::cout<<*p<<std::endl;
//	system("pause");
//	return 0;
//}

