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

void RecCreateBiTree(BinaryTree **pRoot)
{
	int nNum;
	if(pRoot == NULL)return;
	scanf("%d",&nNum);

	if(nNum == 0)return;

	//��ӽڵ�
	*pRoot = (BinaryTree*)malloc(sizeof(BinaryTree));
	(*pRoot)->nValue = nNum;
	(*pRoot)->pLeft = NULL;
	(*pRoot)->pRight = NULL;

	//����ǰ�ڵ������
	RecCreateBiTree(&((*pRoot)->pLeft));
	RecCreateBiTree(&((*pRoot)->pRight));
}

BinaryTree * ArrToBiTree(int arr[],int nLength)
{
	BinaryTree *pTree = NULL;
	int i;
	if(arr == NULL || nLength <=0)return NULL;

	//�������鳤�ȴ����ṹ������
	pTree = (BinaryTree*)malloc(sizeof(BinaryTree) * nLength);

	//����Ԫ�ؿ���  �ṹ���鸳��ֵ
	for(i = 0;i<nLength;i++)
	{
		pTree[i].nValue = arr[i];
		pTree[i].pLeft = NULL;
		pTree[i].pRight = NULL;
	}

	//�������ҹ�ϵ����
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

	//��
	printf("%d  ",pRoot->nValue);
	//��
	PreOrderTraversal(pRoot->pLeft);
	//��
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