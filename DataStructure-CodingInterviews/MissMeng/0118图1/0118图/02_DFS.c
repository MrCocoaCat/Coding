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
//void MyDFS(Graph *pGraph,int nBegin,int *pMark)
//{
//	int i;
//	printf("%d  ",nBegin);
//	pMark[nBegin-1] = 1;
//
//	for(i = 0;i<pGraph->nVertex;i++)
//	{
//		//�ҵ��뵱ǰ������صĶ���
//		if(pGraph->pMatrix[(nBegin-1)*pGraph->nVertex + i] == 1)
//		{
//			//�ҵ���һ��δ����ӡ��
//			if(pMark[i] == 0)
//			{
//				MyDFS(pGraph,i+1,pMark);
//			}
//		}
//	}
//}
//
//void DFS(Graph *pGraph,int nBegin)
//{
//	int *pMark = NULL;
//	if(pGraph == NULL || nBegin<=0 ||nBegin >pGraph->nVertex)return;
//
//	//���ٱ������
//	pMark = (int *)malloc(sizeof(int) *pGraph->nVertex);
//	memset(pMark,0,sizeof(int) *pGraph->nVertex);
//	
//	//��ʼ����
//	MyDFS(pGraph,nBegin,pMark);
//
//	//�ͷſռ�
//	free(pMark);
//	pMark = NULL;
//}
//
//int main()
//{
//	int i;
//	Graph *pGraph = NULL;
//	pGraph = CreateGraph();
//	DFS(pGraph,3);
//
//	return 0;
//}