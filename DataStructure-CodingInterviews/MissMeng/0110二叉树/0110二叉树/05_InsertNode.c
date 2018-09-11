//#include<stdio.h>
//#include<stdlib.h>
//
//typedef struct node 
//{
//	int nValue;
//	struct node *pLeft;
//	struct node *pRight;
//}BinaryTree;
//
//enum DIRECTION{LEFT,RIGHT};
//
//void CreateBinaryTree(BinaryTree **pRoot)
//{
//	if(pRoot == NULL)return;
//
//	//根
//	*pRoot = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->nValue = 1;
//
//	//根的左
//	(*pRoot)->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pLeft->nValue = 2;
//
//	//左的左
//	(*pRoot)->pLeft->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pLeft->pLeft->nValue = 4;
//	(*pRoot)->pLeft->pLeft->pLeft = NULL;
//	(*pRoot)->pLeft->pLeft->pRight = NULL;
//
//	//左的右
//	(*pRoot)->pLeft->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pLeft->pRight->nValue = 5;
//	(*pRoot)->pLeft->pRight->pLeft = NULL;
//	(*pRoot)->pLeft->pRight->pRight = NULL;
//
//	//根的右
//	(*pRoot)->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pRight->nValue = 3;
//	
//	//右的左
//	(*pRoot)->pRight->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pRight->pLeft->nValue = 6;
//	(*pRoot)->pRight->pLeft->pLeft = NULL;
//	(*pRoot)->pRight->pLeft->pRight = NULL;
//
//	//右的右
//	(*pRoot)->pRight->pRight = NULL;
//	
//}
//
//typedef struct node3
//{
//	BinaryTree *pTree;
//	struct node3 *pNext;
//}MyQueue;
//
//typedef struct  node4
//{
//	MyQueue *pHead;
//	MyQueue *pTail;
//	int nCount;
//}Queue;
//
////辅助队列
//void q_Init(Queue **pQueue)
//{
//	if(pQueue == NULL)return;
//	*pQueue = (Queue*)malloc(sizeof(Queue));
//	(*pQueue)->nCount = 0;
//	(*pQueue)->pHead = NULL;
//	(*pQueue)->pTail = NULL;
//}
//
//void q_Push(Queue *pQueue,BinaryTree *pNode)
//{
//	MyQueue *pTemp = NULL;
//	if(pQueue == NULL || pNode == NULL)return;
//
//	pTemp = (MyQueue*)malloc(sizeof(MyQueue));
//	pTemp->pTree = pNode;
//	pTemp->pNext = NULL;
//
//	//尾添加
//	if(pQueue->pHead == NULL)
//	{
//		pQueue->pHead = pTemp;
//	}
//	else
//	{
//		pQueue->pTail->pNext = pTemp;
//	}
//	pQueue->pTail = pTemp;
//	pQueue->nCount++;
//}
//
//BinaryTree * q_Pop(Queue *pQueue)
//{
//	MyQueue *pDel = NULL;
//	BinaryTree *pTree = NULL;
//	if(pQueue == NULL || pQueue->pHead == NULL)return NULL;
//
//	pDel = pQueue->pHead;
//	pTree = pDel->pTree;
//
//	pQueue->pHead = pQueue->pHead->pNext;
//	free(pDel);
//	pDel = NULL;
//	pQueue->nCount--;
//
//	//队列里只有一个元素 被删除之后  尾也要被赋空值
//	if(pQueue->nCount == 0)
//	{
//		pQueue->pTail = NULL;
//	}
//	return pTree;
//}
//
//int q_IsEmpty(Queue *pQueue)
//{
//	if(pQueue == NULL)return	-1;
//	return (pQueue->nCount == 0)?1:0;
//}
//
//BinaryTree* LevelChop(BinaryTree *pRoot,int nValue)
//{
//	Queue *pQueue = NULL;
//	BinaryTree *pNode = NULL;
//
//	if(pRoot == NULL)return NULL;
//
//	//申请辅助队列
//	q_Init(&pQueue);
//
//	//根入队
//	q_Push(pQueue,pRoot);
//
//	while( !q_IsEmpty(pQueue))
//	{
//		//出队 打印
//		pNode = q_Pop(pQueue);
//		if(pNode->nValue == nValue)
//		{
//			return pNode;
//		}
//
//		//当前节点左右入队
//		q_Push(pQueue,pNode->pLeft);
//		q_Push(pQueue,pNode->pRight);
//	}
//	return NULL;
//}
//
//void InsertNode(BinaryTree *pRoot,int nValue,int nNum,int nDirection)
//{
//	BinaryTree *pNode = NULL;
//	BinaryTree *pTemp = NULL;
//
//	if(pRoot == NULL)return;
//
//	//查找
//	pNode = LevelChop(pRoot,nNum);
//
//	//检测节点情况
//	if(pNode == NULL)return;
//
//	//值装入节点
//	pTemp = (BinaryTree*)malloc(sizeof(BinaryTree));
//	pTemp->nValue = nValue;
//	pTemp->pLeft = NULL;
//	pTemp->pRight = NULL;
//
//	//判断插入方向  插入节点
//	if(nDirection == LEFT)
//	{
//		pTemp->pLeft = pNode->pLeft;
//		pNode->pLeft = pTemp;
//		return;
//	}
//	if(nDirection == RIGHT)
//	{
//		pTemp->pRight = pNode->pRight;
//		pNode->pRight = pTemp;
//		return;
//	}
//
//}
//
//void PreOrderTraversal(BinaryTree *pRoot)
//{
//	if(pRoot == NULL)return;
//
//	//根
//	printf("%d  ",pRoot->nValue);
//	//左
//	PreOrderTraversal(pRoot->pLeft);
//	//右
//	PreOrderTraversal(pRoot->pRight);
//}
//
//int main()
//{
//	BinaryTree *pRoot = NULL;
//	CreateBinaryTree(&pRoot);
//	InsertNode(pRoot,10000,2,1);
//	PreOrderTraversal(pRoot);
//	return 0;
//}