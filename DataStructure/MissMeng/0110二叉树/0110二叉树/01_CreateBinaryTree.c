#include<stdio.h>
#include<stdlib.h>

typedef struct node 
{
	int nValue;
	struct node *pLeft;
	struct node *pRight;
}BinaryTree;

void CreateBinaryTree(BinaryTree **pRoot)
{
	if(pRoot == NULL)return;

	//根
	*pRoot = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->nValue = 1;

	//根的左
	(*pRoot)->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->pLeft->nValue = 2;

	//左的左
	(*pRoot)->pLeft->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->pLeft->pLeft->nValue = 4;
	(*pRoot)->pLeft->pLeft->pLeft = NULL;
	(*pRoot)->pLeft->pLeft->pRight = NULL;

	//左的右
	(*pRoot)->pLeft->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->pLeft->pRight->nValue = 5;
	(*pRoot)->pLeft->pRight->pLeft = NULL;
	(*pRoot)->pLeft->pRight->pRight = NULL;

	//根的右
	(*pRoot)->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->pRight->nValue = 3;
	
	//右的左
	(*pRoot)->pRight->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->pRight->pLeft->nValue = 6;
	(*pRoot)->pRight->pLeft->pLeft = NULL;
	(*pRoot)->pRight->pLeft->pRight = NULL;

	//右的右
	(*pRoot)->pRight->pRight = NULL;
	
}

void RecCreateBiTree(BinaryTree **pRoot)
{
	int nNum;
	if(pRoot == NULL)return;
	scanf("%d",&nNum);

	if(nNum == 0)return;

	//添加节点
	*pRoot = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->nValue = nNum;
	(*pRoot)->pLeft = NULL;
	(*pRoot)->pRight = NULL;

	//处理当前节点的左右
	RecCreateBiTree(&((*pRoot)->pLeft));
	RecCreateBiTree(&((*pRoot)->pRight));
}

BinaryTree * ArrToBiTree(int arr[],int nLength)
{
	BinaryTree *pTree = NULL;
	int i;
	if(arr == NULL || nLength <=0)return NULL;

	//根据数组长度创建结构体数组
	pTree = (BinaryTree*)malloc(sizeof(BinaryTree) * nLength);

	//数组元素拷贝  结构数组赋初值
	for(i = 0;i<nLength;i++)
	{
		pTree[i].nValue = arr[i];
		pTree[i].pLeft = NULL;
		pTree[i].pRight = NULL;
	}

	//根据左右关系关联
	for(i = 0;i < nLength/2; i++)
	{
		if(2*i+1 < nLength)
		{
			pTree[i].pLeft = &pTree[2*i+1];
		}
		if(2*i +2 < nLength)
		{
			pTree[i].pRight = &pTree[2*i+2];
		}
	}
	return pTree;
}



void PreOrderTraversal(BinaryTree *pRoot)
{
	if(pRoot == NULL)return;

	//根
	printf("%d  ",pRoot->nValue);
	//左
	PreOrderTraversal(pRoot->pLeft);
	//右
	PreOrderTraversal(pRoot->pRight);
}

int main()
{
	BinaryTree *pRoot = NULL;
	int arr[] = {1,2,3,4,5,6,7};
	//CreateBinaryTree(&pRoot);
	//RecCreateBiTree(&pRoot);
	pRoot = ArrToBiTree(arr,sizeof(arr)/sizeof(arr[0]));
	PreOrderTraversal(pRoot);
	return 0;
}