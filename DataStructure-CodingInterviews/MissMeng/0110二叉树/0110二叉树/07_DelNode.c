//#include<stdio.h>
//#include<stdlib.h>
//
//typedef struct node 
//{
//	int nValue;
//	struct node *pLeft;
//	struct node *pRight;
//}BinaryTree;
//
//void AddNode(BinaryTree **pRoot,int nValue)
//{
//	BinaryTree *pTemp = NULL;
//	BinaryTree *pMark = NULL;
//
//	if(pRoot == NULL)return;
//
//	pTemp = (BinaryTree*)malloc(sizeof(BinaryTree));
//	pTemp->nValue = nValue;
//	pTemp->pLeft = NULL;
//	pTemp->pRight = NULL;
//
//	if(*pRoot == NULL)
//	{
//		*pRoot = pTemp;
//		return;
//	}
//
//	pMark = *pRoot;
//
//	while(1)
//	{
//		if(pMark->nValue > nValue)
//		{
//			if(pMark->pLeft == NULL)
//			{
//				pMark->pLeft = pTemp;
//				return;
//			}
//			pMark = pMark->pLeft;
//		}
//		else if(pMark->nValue < nValue)
//		{
//			if(pMark->pRight == NULL)
//			{
//				pMark->pRight = pTemp;
//				return;
//			}
//			pMark = pMark->pRight;
//		}
//		else
//		{
//			printf("添加失败！！！\n");
//			free(pTemp);
//			pTemp = NULL;
//			return;
//		}
//	}
//
//}
//
//void CreateSortBiTree(BinaryTree **pRoot,int arr[],int nLength)
//{
//	int i;
//	if(pRoot == NULL || arr == NULL || nLength <=0)return;
//	for(i = 0;i<nLength;i++)
//	{
//		AddNode(pRoot,arr[i]);
//	}
//}
//
//void InOrderTraversal(BinaryTree *pRoot)
//{
//	if(pRoot == NULL)return;
//
//	//左
//	InOrderTraversal(pRoot->pLeft);
//	//根
//	printf("%d  ",pRoot->nValue);
//	//右
//	InOrderTraversal(pRoot->pRight);
//}
//
//void FindNode(BinaryTree *pRoot,int nNum,BinaryTree **pDel,BinaryTree **pDelFather)
//{
//	while(pRoot)
//	{
//		if(pRoot->nValue == nNum)
//		{
//			*pDel = pRoot;
//			return;
//		}
//		else if(pRoot->nValue > nNum)
//		{
//			*pDelFather = pRoot;
//			pRoot = pRoot->pLeft;
//		}
//		else
//		{
//			*pDelFather = pRoot;
//			pRoot = pRoot->pRight;
//		}
//	}
//
//	//没找到被删除节点  父亲清空
//	*pDelFather = NULL;
//}
//
//void DelOneChild(BinaryTree *pDel,BinaryTree *pDelFather)
//{
//	if(pDel == pDelFather->pLeft)
//	{
//		pDelFather->pLeft = pDel->pLeft?pDel->pLeft:pDel->pRight;
//		free(pDel);
//		pDel = NULL;
//		return;
//	}
//	if(pDel == pDelFather->pRight)
//	{
//		pDelFather->pRight = pDel->pLeft?pDel->pLeft:pDel->pRight;
//		free(pDel);
//		pDel = NULL;
//		return;
//	}
//}
//
//void DelNode(BinaryTree **pRoot,int nNum)
//{
//	BinaryTree *pDel = NULL;
//	BinaryTree *pDelFather = NULL;
//	BinaryTree *pMark = NULL;
//
//	if(pRoot == NULL || *pRoot == NULL)return;
//
//	//查找
//	FindNode(*pRoot,nNum,&pDel,&pDelFather);
//
//	//检测情况
//	if(pDel == NULL)return;
//
//	//两个孩子
//	if(pDel->pLeft!= NULL && pDel->pRight!= NULL)
//	{
//		pMark = pDel;
//
//		//右子树最左
//		pDelFather = pDel;
//		pDel = pDel->pRight;
//
//		while(pDel->pLeft)
//		{
//			pDelFather = pDel;
//			pDel = pDel->pLeft;
//		}
//
//		pMark->nValue = pDel->nValue;
//	}
//
//	if(pDelFather == NULL)
//	{
//		*pRoot = pDel->pLeft ? pDel->pLeft : pDel->pRight;
//		free(pDel);
//		pDel = NULL;
//		return;
//	}
//
//	//一个孩子或者没有孩子
//	DelOneChild(pDel,pDelFather);
//
//}
//
//
//int main()
//{
//	BinaryTree *pRoot = NULL;
//
//	int arr[] = {12,10,100,4,29,37,108,1,234};
//	CreateSortBiTree(&pRoot,arr,sizeof(arr)/sizeof(arr[0]));
//	InOrderTraversal(pRoot);
//	printf("\n");
//	DelNode(&pRoot,100);
//	InOrderTraversal(pRoot);
//	return 0;
//}
