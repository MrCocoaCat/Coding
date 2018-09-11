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

void LastOrderTraversal(BinaryTree *pRoot)
{
	if(pRoot == NULL)return;

	//左
	LastOrderTraversal(pRoot->pLeft);
	//右
	LastOrderTraversal(pRoot->pRight);
	//根
	printf("%d  ",pRoot->nValue);
}




int main()
{
	BinaryTree *pRoot = NULL;
	CreateBinaryTree(&pRoot);
	PreOrderTraversal(pRoot);
	printf("\n");
	InOrderTraversal(pRoot);
	printf("\n");
	LastOrderTraversal(pRoot);
	return 0;
}