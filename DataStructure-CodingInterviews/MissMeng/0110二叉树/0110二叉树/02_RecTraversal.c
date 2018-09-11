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

	//��
	*pRoot = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->nValue = 1;

	//������
	(*pRoot)->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->pLeft->nValue = 2;

	//�����
	(*pRoot)->pLeft->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->pLeft->pLeft->nValue = 4;
	(*pRoot)->pLeft->pLeft->pLeft = NULL;
	(*pRoot)->pLeft->pLeft->pRight = NULL;

	//�����
	(*pRoot)->pLeft->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->pLeft->pRight->nValue = 5;
	(*pRoot)->pLeft->pRight->pLeft = NULL;
	(*pRoot)->pLeft->pRight->pRight = NULL;

	//������
	(*pRoot)->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->pRight->nValue = 3;
	
	//�ҵ���
	(*pRoot)->pRight->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->pRight->pLeft->nValue = 6;
	(*pRoot)->pRight->pLeft->pLeft = NULL;
	(*pRoot)->pRight->pLeft->pRight = NULL;

	//�ҵ���
	(*pRoot)->pRight->pRight = NULL;
	
}

void PreOrderTraversal(BinaryTree *pRoot)
{
	if(pRoot == NULL)return;

	//��
	printf("%d  ",pRoot->nValue);
	//��
	PreOrderTraversal(pRoot->pLeft);
	//��
	PreOrderTraversal(pRoot->pRight);
}

void InOrderTraversal(BinaryTree *pRoot)
{
	if(pRoot == NULL)return;

	//��
	InOrderTraversal(pRoot->pLeft);
	//��
	printf("%d  ",pRoot->nValue);
	//��
	InOrderTraversal(pRoot->pRight);
}

void LastOrderTraversal(BinaryTree *pRoot)
{
	if(pRoot == NULL)return;

	//��
	LastOrderTraversal(pRoot->pLeft);
	//��
	LastOrderTraversal(pRoot->pRight);
	//��
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