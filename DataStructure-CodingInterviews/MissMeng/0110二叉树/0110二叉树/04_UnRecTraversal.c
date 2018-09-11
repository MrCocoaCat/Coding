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
//typedef struct node1
//{
//	BinaryTree *pTree;
//	struct node1 *pNext;
//}MyStack;
//
//typedef struct node2
//{
//	MyStack *pTop;
//	int nCount;
//}Stack;
//
//void s_Init(Stack **pStack)
//{
//	if(pStack == NULL)return;
//
//	//申请栈空间  赋初值
//	*pStack = (Stack*)malloc(sizeof(Stack));
//	(*pStack)->nCount = 0;
//	(*pStack)->pTop = NULL;
//}
//
//void s_Push(Stack *pStack,BinaryTree *pNode)
//{
//	MyStack *pTemp = NULL;
//
//	if(pStack == NULL || pNode == NULL)
//	{
//		printf("栈不存在TAT\n");
//		return;
//	}
//
//	pTemp = (MyStack*)malloc(sizeof(MyStack));
//	pTemp->pTree = pNode;
//
//	//头添加  
//	pTemp->pNext = pStack->pTop;
//	pStack->pTop = pTemp;
//
//	//更新栈内元素个数
//	pStack->nCount++;
//}
//
//BinaryTree * s_Pop(Stack *pStack)
//{
//	MyStack *pDel = NULL;
//	BinaryTree *pNode = NULL;
//	if(pStack == NULL || pStack->pTop == NULL)return NULL;
//
//	//标记被删除节点 和值
//	pDel = pStack->pTop;
//	pNode = pDel->pTree;
//
//	//头删除
//	pStack->pTop = pStack->pTop->pNext;
//	free(pDel);
//	pDel = NULL;
//
//	//更新栈内元素个数
//	pStack->nCount--;
//
//	return pNode;
//}
//
//int s_IsEmpty(Stack *pStack)
//{
//	if(pStack == NULL)return -1;
//	return (pStack->nCount == 0) ? 1:0;
//}
//
//void CreateBinaryTree(BinaryTree **pRoot)
//{
//	if(pRoot == NULL)return;
//
//	//根
//	*pRoot = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->nValue = 1;
//
//	//根的左
//	(*pRoot)->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pLeft->nValue = 2;
//
//	//左的左
//	(*pRoot)->pLeft->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pLeft->pLeft->nValue = 4;
//	(*pRoot)->pLeft->pLeft->pLeft = NULL;
//	(*pRoot)->pLeft->pLeft->pRight = NULL;
//
//	//左的右
//	(*pRoot)->pLeft->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pLeft->pRight->nValue = 5;
//	(*pRoot)->pLeft->pRight->pLeft = NULL;
//	(*pRoot)->pLeft->pRight->pRight = NULL;
//
//	//根的右
//	(*pRoot)->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pRight->nValue = 3;
//	
//	//右的左
//	(*pRoot)->pRight->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pRight->pLeft->nValue = 6;
//	(*pRoot)->pRight->pLeft->pLeft = NULL;
//	(*pRoot)->pRight->pLeft->pRight = NULL;
//
//	//右的右
//	(*pRoot)->pRight->pRight = NULL;
//	
//}
//
//void UnRecPreOrderTraversal(BinaryTree *pRoot)
//{
//	Stack *pStack = NULL;
//	if(pRoot == NULL)return;
//
//	//申请栈
//	s_Init(&pStack);
//
//	while(1)
//	{
//		while(pRoot)
//		{
//			//打印 入栈
//			printf("%d  ",pRoot->nValue);
//			s_Push(pStack,pRoot);
//
//			//处理左
//			pRoot = pRoot->pLeft;
//		}
//
//		//出栈
//		pRoot = s_Pop(pStack);
//
//		//空栈 结束
//		if(pRoot == NULL)
//		{
//			break;
//		}
//
//		//处理右
//		pRoot = pRoot->pRight;
//	}
//}
//
//void UnRecInOrderTraversal(BinaryTree *pRoot)
//{
//	Stack *pStack = NULL;
//	if(pRoot == NULL)return;
//
//	//申请栈
//	s_Init(&pStack);
//
//	while(1)
//	{
//		while(pRoot)
//		{
//			// 入栈
//			s_Push(pStack,pRoot);
//
//			//处理左
//			pRoot = pRoot->pLeft;
//		}
//
//		//出栈
//		pRoot = s_Pop(pStack);
//
//		//空栈 结束
//		if(pRoot == NULL)
//		{
//			break;
//		}
//		//打印
//		printf("%d  ",pRoot->nValue);
//
//		//处理右
//		pRoot = pRoot->pRight;
//	}
//}
//
//void UnRecLastOrderTraversal(BinaryTree *pRoot)
//{
//	Stack *pStack = NULL;
//	BinaryTree *pMark = NULL;
//
//	if(pRoot == NULL)return;
//
//	//申请栈
//	s_Init(&pStack);
//
//	while(1)
//	{
//		while(pRoot)
//		{
//			// 入栈
//			s_Push(pStack,pRoot);
//
//			//处理左
//			pRoot = pRoot->pLeft;
//		}
//
//		//空栈 结束
//		if(pStack->pTop == NULL)break;
//
//		//检测栈顶元素是否有右 右是否被标记过
//		if(pStack->pTop->pTree->pRight == NULL || pStack->pTop->pTree->pRight == pMark)
//		{
//			pMark = s_Pop(pStack);
//			printf("%d  ",pMark->nValue);
//		}
//		//有右 且未被标记
//		else
//		{
//			pRoot = pStack->pTop->pTree->pRight;
//		}
//	}
//}
//
//
//
//
//int main()
//{
//	BinaryTree *pRoot= NULL;
//	CreateBinaryTree(&pRoot);
//	UnRecPreOrderTraversal(pRoot);
//	printf("\n");
//	UnRecInOrderTraversal(pRoot);
//	printf("\n");
//	UnRecLastOrderTraversal(pRoot);
//	return 0;
//}
//
