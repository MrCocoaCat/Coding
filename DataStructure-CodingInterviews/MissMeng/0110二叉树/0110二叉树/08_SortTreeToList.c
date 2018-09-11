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
//void SBTToList(BinaryTree *pRoot,BinaryTree **pHead,BinaryTree **pTail)
//{
//	if(pRoot == NULL)return;
//
//	//左
//	SBTToList(pRoot->pLeft,pHead,pTail);
//
//	//链表节点添加
//	if(*pHead == NULL)
//	{
//		*pHead = pRoot;
//	}
//	else
//	{
//		(*pTail)->pRight = pRoot;
//		pRoot->pLeft = *pTail;
//	}
//	*pTail = pRoot;
//
//	//右
//	SBTToList(pRoot->pRight,pHead,pTail);
//}
//
//
//int main()
//{
//	BinaryTree *pRoot = NULL;
//	BinaryTree *pHead = NULL;
//	BinaryTree *pTail = NULL;
//
//	int arr[] = {12,10,100,4,29,37,108,1,234};
//	CreateSortBiTree(&pRoot,arr,sizeof(arr)/sizeof(arr[0]));
//	SBTToList(pRoot,&pHead,&pTail);
//
//	while(pHead)
//	{
//		printf("%d  ",pHead->nValue);
//		pHead = pHead->pRight;
//	}
//	return 0;
//}
