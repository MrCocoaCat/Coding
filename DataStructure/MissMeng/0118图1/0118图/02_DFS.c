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
//void MyDFS(Graph *pGraph,int nBegin,int *pMark)
//{
//	int i;
//	printf("%d  ",nBegin);
//	pMark[nBegin-1] = 1;
//
//	for(i = 0;i<pGraph->nVertex;i++)
//	{
//		//找到与当前顶点相关的顶点
//		if(pGraph->pMatrix[(nBegin-1)*pGraph->nVertex + i] == 1)
//		{
//			//找到第一个未被打印的
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
//	//开辟标记数组
//	pMark = (int *)malloc(sizeof(int) *pGraph->nVertex);
//	memset(pMark,0,sizeof(int) *pGraph->nVertex);
//	
//	//开始遍历
//	MyDFS(pGraph,nBegin,pMark);
//
//	//释放空间
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