//#include<stdio.h>
//#include<stdlib.h>
//
//typedef struct node 
//{
//	int nValue;
//	struct node *pLeft;
//	struct node *pRight;
//	struct node  *pFather;
//}BinaryTree;
//
//void CreateBiTree(BinaryTree **root)
//{
//	if(root == NULL)return;
//	(*root) = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*root)->nValue = 1;
//	(*root)->pFather = NULL;
//
//	//������
//	(*root)->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*root)->pLeft->nValue = 2;
//	(*root)->pLeft->pFather = *root;
//
//	//������
//	(*root)->pRight = NULL;
//
//	//�����
//	(*root)->pLeft->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*root)->pLeft->pLeft->nValue = 3;
//	(*root)->pLeft->pLeft->pFather = (*root)->pLeft;
//
//	//��������
//	(*root)->pLeft->pLeft->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*root)->pLeft->pLeft->pLeft->nValue = 5;
//	(*root)->pLeft->pLeft->pLeft->pFather = (*root)->pLeft->pLeft;
//	(*root)->pLeft->pLeft->pLeft->pLeft = NULL;
//	(*root)->pLeft->pLeft->pLeft->pRight = NULL;
//
//	//��������
//	(*root)->pLeft->pLeft->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*root)->pLeft->pLeft->pRight ->nValue = 6;
//	(*root)->pLeft->pLeft->pRight ->pFather = (*root)->pLeft->pLeft;
//	(*root)->pLeft->pLeft->pRight ->pLeft = NULL;
//	(*root)->pLeft->pLeft->pRight ->pRight = NULL;
//
//	//�����
//	(*root)->pLeft->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*root)->pLeft->pRight->nValue = 4;
//	(*root)->pLeft->pRight->pFather = (*root)->pLeft;
//	(*root)->pLeft->pRight->pLeft = NULL;
//	(*root)->pLeft->pRight->pRight = NULL;
//}
//
//void RightRotate(BinaryTree **pTree)
//{
//	BinaryTree *pNode = NULL ;//֧��
//	BinaryTree *pMark = NULL;
//	if(pTree == NULL || *pTree == NULL)return;
//
//	pNode = *pTree;
//	pMark = pNode->pLeft; //���� ���֧�����
//
//	//�������ӹ�ϵ
//	pNode->pLeft = pMark->pRight;
//	pMark->pRight = pNode;
//
//	//֧�㸸�״���
//	if(pNode->pFather != NULL)
//	{
//		if(pNode == pNode->pFather->pLeft)
//		{
//			pNode->pFather->pLeft = pMark;
//		}
//		else
//		{
//			pNode->pFather->pRight = pMark;
//		}
//	}
//
//	//�������׹�ϵ
//	if(pNode->pLeft != NULL)
//	{
//		pNode->pLeft->pFather = pNode;
//	}
//
//	pMark->pFather = pNode->pFather;
//	if(pMark->pFather == NULL)
//	{
//		*pTree = pMark;
//	}
//
//	pNode->pFather = pMark;
//
//}
//
//void LeftRotate(BinaryTree **pTree)
//{
//	BinaryTree *pNode = NULL ;//֧��
//	BinaryTree *pMark = NULL;
//	if(pTree == NULL || *pTree == NULL)return;
//
//	pNode = *pTree;
//	pMark = pNode->pRight; //���� ���֧���Ҳ�
//
//	//�������ӹ�ϵ
//	pNode->pRight = pMark->pLeft;
//	pMark->pLeft = pNode;
//
//	//֧�㸸�״���
//	if(pNode->pFather != NULL)
//	{
//		if(pNode == pNode->pFather->pLeft)
//		{
//			pNode->pFather->pLeft = pMark;
//		}
//		else
//		{
//			pNode->pFather->pRight = pMark;
//		}
//	}
//
//	//�������׹�ϵ
//	if(pNode->pRight != NULL)
//	{
//		pNode->pRight->pFather = pNode;
//	}
//
//	pMark->pFather = pNode->pFather;
//	if(pMark->pFather == NULL)
//	{
//		*pTree = pMark;
//	}
//
//	pNode->pFather = pMark;
//
//}
//
//
//void PreOrderTraversal(BinaryTree *pRoot)
//{
//	if(pRoot == NULL)return;
//
//	//��
//	printf("%d  ",pRoot->nValue);
//	//��
//	PreOrderTraversal(pRoot->pLeft);
//	//��
//	PreOrderTraversal(pRoot->pRight);
//}
//
//int main()
//{
//	BinaryTree *pRoot = NULL;
//	CreateBiTree(&pRoot);
//	PreOrderTraversal(pRoot);
//	printf("\n");
//	RightRotate(&pRoot);
//	PreOrderTraversal(pRoot);
//	printf("\n");
//	LeftRotate(&pRoot);
//	PreOrderTraversal(pRoot);
//	return 0;
//}
