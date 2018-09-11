#include<stdio.h>
#include<stdlib.h>

typedef struct node 
{
	int nValue;
	struct node *pLeft;
	struct node *pRight;
}BinaryTree;

void AddNode(BinaryTree **pRoot,int nValue)
{
	BinaryTree *pTemp = NULL;
	BinaryTree *pMark = NULL;

	if(pRoot == NULL)return;

	pTemp = (BinaryTree*)malloc(sizeof(BinaryTree));
	pTemp->nValue = nValue;
	pTemp->pLeft = NULL;
	pTemp->pRight = NULL;

	if(*pRoot == NULL)
	{
		*pRoot = pTemp;
		return;
	}

	pMark = *pRoot;

	while(1)
	{
		if(pMark->nValue > nValue)
		{
			if(pMark->pLeft == NULL)
			{
				pMark->pLeft = pTemp;
				return;
			}
			pMark = pMark->pLeft;  //继续向左走
		}
		else if(pMark->nValue < nValue)
		{
			if(pMark->pRight == NULL)
			{
				pMark->pRight = pTemp;
				return;
			}
			pMark = pMark->pRight;  //继续向右走
		}
		else
		{
			printf("添加失败！！！\n");
			free(pTemp);
			pTemp = NULL;
			return;
		}
	}

}

void CreateSortBiTree(BinaryTree **pRoot,int arr[],int nLength)
{
	int i;
	if(pRoot == NULL || arr == NULL || nLength <=0)return;
	for(i = 0;i<nLength;i++)
	{
		AddNode(pRoot,arr[i]);
	}
}

void InOrderTraversal(BinaryTree *pRoot)
{
	if(pRoot == NULL)return;

	//左
	InOrderTraversal(pRoot->pLeft);
	//根
	printf("%d  ",pRoot->nValue);
	//右
	InOrderTraversal(pRoot->pRight);
}


int main()
{
	BinaryTree *pRoot = NULL;

	int arr[] = {12,10,100,4,29,37,108,1,234};
	CreateSortBiTree(&pRoot,arr,sizeof(arr)/sizeof(arr[0]));
	InOrderTraversal(pRoot);
	return 0;
}
