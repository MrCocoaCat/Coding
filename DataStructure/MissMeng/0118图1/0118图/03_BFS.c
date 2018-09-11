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
//	printf("�����붥��ĸ���:\n");
//	scanf("%d",&nV);
//	printf("������ߵ�����:\n");
//	scanf("%d",&nE);
//
//	pGraph = (Graph*)malloc(sizeof(Graph));
//	pGraph->nEdge = nE;
//	pGraph->nVertex = nV;
//
//	pGraph->pMatrix = (int *)malloc(sizeof(int) *pGraph->nVertex *pGraph->nVertex);
//	//��������
//	memset(pGraph->pMatrix,0,sizeof(int) *pGraph->nVertex *pGraph->nVertex);
//
//	//���ݱ�  ����ֵ
//	for(i = 0;i<pGraph->nEdge;i++)
//	{
//		printf("�������������㣺\n");
//		scanf("%d%d",&a,&b);
//
//		//�����ں���Χ֮��
//		if(a>0&&a<=pGraph->nVertex &&b>0&&b<=pGraph->nVertex && a!=b
//			&& pGraph->pMatrix[ (a-1)*pGraph->nVertex +b-1 ] == 0)
//		{
//			pGraph->pMatrix[ (a-1)*pGraph->nVertex +b-1 ] = 1;
//			pGraph->pMatrix[ (b-1)*pGraph->nVertex +a-1 ] = 1;
//		}
//		else
//		{
//			printf("������������������!\n");
//			i--;
//		}
//	}
//	return pGraph;
//}
//
////��������------------------------------------------------------------------------------------------------------------------
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
//	//β���
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
//	//������ֻ��һ��Ԫ�� ��ɾ��֮��  βҲҪ������ֵ
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
//	//��������
//	q_Init(&pQueue);
//
//	//�������
//	pMark = (int *)malloc(sizeof(int) * pGraph->nVertex);
//	memset(pMark,0,sizeof(int) * pGraph->nVertex);
//
//	//��ʼ�������
//	q_Push(pQueue,nBegin);
//	pMark[nBegin-1] = 1;
//
//	while( !q_IsEmpty(pQueue))
//	{
//		//���� ��ӡ
//		nBegin = q_Pop(pQueue);
//		printf("%d  ",nBegin);
//
//		//������ص� δ������Ķ�������
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