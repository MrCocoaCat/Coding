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
//	//左子树
//	(*root)->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*root)->pLeft->nValue = 2;
//	(*root)->pLeft->pFather = *root;
//
//	//右子树
//	(*root)->pRight = NULL;
//
//	//左的左
//	(*root)->pLeft->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*root)->pLeft->pLeft->nValue = 3;
//	(*root)->pLeft->pLeft->pFather = (*root)->pLeft;
//
//	//左的左的左
//	(*root)->pLeft->pLeft->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*root)->pLeft->pLeft->pLeft->nValue = 5;
//	(*root)->pLeft->pLeft->pLeft->pFather = (*root)->pLeft->pLeft;
//	(*root)->pLeft->pLeft->pLeft->pLeft = NULL;
//	(*root)->pLeft->pLeft->pLeft->pRight = NULL;
//
//	//左的左的右
//	(*root)->pLeft->pLeft->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*root)->pLeft->pLeft->pRight ->nValue = 6;
//	(*root)->pLeft->pLeft->pRight ->pFather = (*root)->pLeft->pLeft;
//	(*root)->pLeft->pLeft->pRight ->pLeft = NULL;
//	(*root)->pLeft->pLeft->pRight ->pRight = NULL;
//
//	//左的右
//	(*root)->pLeft->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*root)->pLeft->pRight->nValue = 4;
//	(*root)->pLeft->pRight->pFather = (*root)->pLeft;
//	(*root)->pLeft->pRight->pLeft = NULL;
//	(*root)->pLeft->pRight->pRight = NULL;
//}
//
//void RightRotate(BinaryTree **pTree)
//{
//	BinaryTree *pNode = NULL ;//支点
//	BinaryTree *pMark = NULL;
//	if(pTree == NULL || *pTree == NULL)return;
//
//	pNode = *pTree;
//	pMark = pNode->pLeft; //右旋 标记支点左侧
//
//	//三个孩子关系
//	pNode->pLeft = pMark->pRight;
//	pMark->pRight = pNode;
//
//	//支点父亲存在
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
//	//三个父亲关系
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
//	BinaryTree *pNode = NULL ;//支点
//	BinaryTree *pMark = NULL;
//	if(pTree == NULL || *pTree == NULL)return;
//
//	pNode = *pTree;
//	pMark = pNode->pRight; //左旋 标记支点右侧
//
//	//三个孩子关系
//	pNode->pRight = pMark->pLeft;
//	pMark->pLeft = pNode;
//
//	//支点父亲存在
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
//	//三个父亲关系
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
//	//根
//	printf("%d  ",pRoot->nValue);
//	//左
//	PreOrderTraversal(pRoot->pLeft);
//	//右
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
