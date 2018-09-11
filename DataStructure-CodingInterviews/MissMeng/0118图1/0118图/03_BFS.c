//#include<stdio.h>
//#include<stdlib.h>
//#include<windows.h>
//
//typedef struct node
//{
//	int nVertex;
//	int nEdge;
//	int *pMatrix;
//}Graph;
//
//Graph* CreateGraph()
//{
//	Graph *pGraph = NULL;
//
//	int nV;
//	int nE;
//	int i;
//	int a,b;
//	printf("请输入顶点的个数:\n");
//	scanf("%d",&nV);
//	printf("请输入边的条数:\n");
//	scanf("%d",&nE);
//
//	pGraph = (Graph*)malloc(sizeof(Graph));
//	pGraph->nEdge = nE;
//	pGraph->nVertex = nV;
//
//	pGraph->pMatrix = (int *)malloc(sizeof(int) *pGraph->nVertex *pGraph->nVertex);
//	//矩阵清零
//	memset(pGraph->pMatrix,0,sizeof(int) *pGraph->nVertex *pGraph->nVertex);
//
//	//根据边  矩阵赋值
//	for(i = 0;i<pGraph->nEdge;i++)
//	{
//		printf("请输入两个顶点：\n");
//		scanf("%d%d",&a,&b);
//
//		//顶点在合理范围之内
//		if(a>0&&a<=pGraph->nVertex &&b>0&&b<=pGraph->nVertex && a!=b
//			&& pGraph->pMatrix[ (a-1)*pGraph->nVertex +b-1 ] == 0)
//		{
//			pGraph->pMatrix[ (a-1)*pGraph->nVertex +b-1 ] = 1;
//			pGraph->pMatrix[ (b-1)*pGraph->nVertex +a-1 ] = 1;
//		}
//		else
//		{
//			printf("输入有误，请重新输入!\n");
//			i--;
//		}
//	}
//	return pGraph;
//}
//
////辅助队列------------------------------------------------------------------------------------------------------------------
//
//typedef struct node3
//{
//	int nValue;
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
//void q_Init(Queue **pQueue)
//{
//	if(pQueue == NULL)return;
//	*pQueue = (Queue*)malloc(sizeof(Queue));
//	(*pQueue)->nCount = 0;
//	(*pQueue)->pHead = NULL;
//	(*pQueue)->pTail = NULL;
//}
//
//void q_Push(Queue *pQueue,int nNum)
//{
//	MyQueue *pTemp = NULL;
//	if(pQueue == NULL)return;
//
//	pTemp = (MyQueue*)malloc(sizeof(MyQueue));
//	pTemp->nValue = nNum;
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
//int q_Pop(Queue *pQueue)
//{
//	MyQueue *pDel = NULL;
//	int nNum;
//	if(pQueue == NULL || pQueue->pHead == NULL)return -1;
//
//	pDel = pQueue->pHead;
//	nNum = pDel->nValue;
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
//	return nNum;
//}
//
//int q_IsEmpty(Queue *pQueue)
//{
//	if(pQueue == NULL)return	-1;
//	return (pQueue->nCount == 0)?1:0;
//}
//
////------------------------------------------------------------------------------------------------------------------
//
//void BFS(Graph *pGraph,int nBegin)
//{
//	Queue *pQueue = NULL;
//	int *pMark = NULL;
//	int i;
//
//	if(pGraph == NULL || nBegin <=0||nBegin > pGraph->nVertex)return;
//
//	//辅助队列
//	q_Init(&pQueue);
//
//	//标记数组
//	pMark = (int *)malloc(sizeof(int) * pGraph->nVertex);
//	memset(pMark,0,sizeof(int) * pGraph->nVertex);
//
//	//开始顶点入队
//	q_Push(pQueue,nBegin);
//	pMark[nBegin-1] = 1;
//
//	while( !q_IsEmpty(pQueue))
//	{
//		//弹出 打印
//		nBegin = q_Pop(pQueue);
//		printf("%d  ",nBegin);
//
//		//与其相关的 未被处理的顶点均入队
//		for(i = 0;i<pGraph->nVertex;i++)
//		{
//			if(pGraph->pMatrix[(nBegin-1)*pGraph->nVertex + i] == 1)
//			{
//				if(pMark[i] == 0)
//				{
//					pMark[i] = 1;
//					q_Push(pQueue,i+1);
//				}
//			}
//		}
//	}
//}
//
//int main()
//{
//	int i;
//	Graph *pGraph = NULL;
//	pGraph = CreateGraph();
//
//	BFS(pGraph,1);
//	return 0;
//}