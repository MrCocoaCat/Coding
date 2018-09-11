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
	printf("�����붥��ĸ���:\n");
	scanf("%d",&nV);
	printf("������ߵ�����:\n");
	scanf("%d",&nE);

	pGraph = (Graph*)malloc(sizeof(Graph));
	pGraph->nEdge = nE;
	pGraph->nVertex = nV;

	pGraph->pMatrix = (int *) malloc(sizeof(int) *pGraph->nVertex *pGraph->nVertex);
	//��������
	memset(pGraph->pMatrix,0,sizeof(int) *pGraph->nVertex *pGraph->nVertex);

	//���ݱ�  ����ֵ
	for(i = 0;i<pGraph->nEdge;i++)
	{
		printf("�������������㣺\n");
		scanf("%d%d",&a,&b);

		//�����ں���Χ֮��
		if(a>0 && a<=pGraph->nVertex && b>0 &&b <=pGraph->nVertex  && a!=b 
			&& pGraph->pMatrix[ (a-1)*pGraph->nVertex +b-1 ] == 0)
		{
			pGraph->pMatrix[ (a-1)*pGraph->nVertex + b-  1 ] = 1;
			pGraph->pMatrix[ (b-1)*pGraph->nVertex + a-  1 ] = 1;
		}
		else
		{
			printf("������������������!\n");
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