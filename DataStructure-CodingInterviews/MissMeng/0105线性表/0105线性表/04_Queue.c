#include<stdio.h>
#include<stdlib.h>

typedef struct node3
{
	int nValue;
	struct node3 *pNext;
}MyQueue;

typedef struct  node4
{
	MyQueue *pHead;
	MyQueue *pTail;
	int nCount;
}Queue;

void q_Init(Queue **pQueue)
{
	if(pQueue == NULL)return;
	*pQueue = (Queue*)malloc(sizeof(Queue));
	(*pQueue)->nCount = 0;
	(*pQueue)->pHead = NULL;
	(*pQueue)->pTail = NULL;
}

void q_Push(Queue *pQueue,int nNum)
{
	MyQueue *pTemp = NULL;
	if(pQueue == NULL)return;

	pTemp = (MyQueue*)malloc(sizeof(MyQueue));
	pTemp->nValue = nNum;
	pTemp->pNext = NULL;

	//尾添加
	if(pQueue->pHead == NULL)
	{
		pQueue->pHead = pTemp;
	}
	else
	{
		pQueue->pTail->pNext = pTemp;
	}
	pQueue->pTail = pTemp;
	pQueue->nCount++;
}


int q_Pop(Queue *pQueue)
{
	MyQueue *pDel = NULL;
	int nNum;
	if(pQueue == NULL || pQueue->pHead == NULL)return -1;

	pDel = pQueue->pHead;
	nNum = pDel->nValue;

	pQueue->pHead = pQueue->pHead->pNext;
	free(pDel);
	pDel = NULL;
	pQueue->nCount--;

	//队列里只有一个元素 被删除之后  尾也要被赋空值
	if(pQueue->nCount == 0)
	{
		pQueue->pTail = NULL;
	}
	return nNum;
}

int q_IsEmpty(Queue *pQueue)
{
	if(pQueue == NULL)return	-1;
	return (pQueue->nCount == 0)?1:0;
}

int main()
{
	Queue *pQueue = NULL;
	q_Init(&pQueue);

	q_Push(pQueue,1);
	q_Push(pQueue,2);
	q_Push(pQueue,3);
	q_Push(pQueue,4);
	q_Push(pQueue,5);

	printf("%d\n",q_Pop(pQueue));
	printf("%d\n",q_Pop(pQueue));
	printf("%d\n",q_Pop(pQueue));
	printf("%d\n",q_Pop(pQueue));

	return 0;
}

