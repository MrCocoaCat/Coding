#include<stdio.h>
#include<stdlib.h>
#include<memory>

typedef struct node
{
	int nVertex;
	int nEdge;
	int *pMatrix;
}Graph;

Graph* CreateGraph()
{
	Graph *pGraph = NULL;

	int nV;
	int nE;
	int i;
	int a,b;
	printf("请输入顶点的个数:\n");
	scanf("%d",&nV);
	printf("请输入边的条数:\n");
	scanf("%d",&nE);

	pGraph = (Graph*)malloc(sizeof(Graph));
	pGraph->nEdge = nE;
	pGraph->nVertex = nV;

	pGraph->pMatrix = (int *) malloc(sizeof(int) *pGraph->nVertex *pGraph->nVertex);
	//矩阵清零
	memset(pGraph->pMatrix,0,sizeof(int) *pGraph->nVertex *pGraph->nVertex);

	//根据边  矩阵赋值
	for(i = 0;i<pGraph->nEdge;i++)
	{
		printf("请输入两个顶点：\n");
		scanf("%d%d",&a,&b);

		//顶点在合理范围之内
		if(a>0 && a<=pGraph->nVertex && b>0 &&b <=pGraph->nVertex  && a!=b 
			&& pGraph->pMatrix[ (a-1)*pGraph->nVertex +b-1 ] == 0)
		{
			pGraph->pMatrix[ (a-1)*pGraph->nVertex + b-  1 ] = 1;
			pGraph->pMatrix[ (b-1)*pGraph->nVertex + a-  1 ] = 1;
		}
		else
		{
			printf("输入有误，请重新输入!\n");
			i--;
		}
	}
	return pGraph;
}

int main()
{
	int i;
	Graph *pGraph = NULL;
	pGraph = CreateGraph();

	for(i = 0;i<(pGraph->nVertex*pGraph->nVertex);i++ )
	{
		printf("%d  ",pGraph->pMatrix[i]);

		if((i+1)%6 == 0)
		{
			printf("\n");
		}
	}

	return 0;
}