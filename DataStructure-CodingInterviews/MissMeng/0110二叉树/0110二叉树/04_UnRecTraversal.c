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
//	//����ջ�ռ�  ����ֵ
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
//		printf("ջ������TAT\n");
//		return;
//	}
//
//	pTemp = (MyStack*)malloc(sizeof(MyStack));
//	pTemp->pTree = pNode;
//
//	//ͷ���  
//	pTemp->pNext = pStack->pTop;
//	pStack->pTop = pTemp;
//
//	//����ջ��Ԫ�ظ���
//	pStack->nCount++;
//}
//
//BinaryTree * s_Pop(Stack *pStack)
//{
//	MyStack *pDel = NULL;
//	BinaryTree *pNode = NULL;
//	if(pStack == NULL || pStack->pTop == NULL)return NULL;
//
//	//��Ǳ�ɾ���ڵ� ��ֵ
//	pDel = pStack->pTop;
//	pNode = pDel->pTree;
//
//	//ͷɾ��
//	pStack->pTop = pStack->pTop->pNext;
//	free(pDel);
//	pDel = NULL;
//
//	//����ջ��Ԫ�ظ���
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
//	//��
//	*pRoot = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->nValue = 1;
//
//	//������
//	(*pRoot)->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pLeft->nValue = 2;
//
//	//�����
//	(*pRoot)->pLeft->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pLeft->pLeft->nValue = 4;
//	(*pRoot)->pLeft->pLeft->pLeft = NULL;
//	(*pRoot)->pLeft->pLeft->pRight = NULL;
//
//	//�����
//	(*pRoot)->pLeft->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pLeft->pRight->nValue = 5;
//	(*pRoot)->pLeft->pRight->pLeft = NULL;
//	(*pRoot)->pLeft->pRight->pRight = NULL;
//
//	//������
//	(*pRoot)->pRight = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pRight->nValue = 3;
//	
//	//�ҵ���
//	(*pRoot)->pRight->pLeft = (BinaryTree*)malloc(sizeof(BinaryTree));
//	(*pRoot)->pRight->pLeft->nValue = 6;
//	(*pRoot)->pRight->pLeft->pLeft = NULL;
//	(*pRoot)->pRight->pLeft->pRight = NULL;
//
//	//�ҵ���
//	(*pRoot)->pRight->pRight = NULL;
//	
//}
//
//void UnRecPreOrderTraversal(BinaryTree *pRoot)
//{
//	Stack *pStack = NULL;
//	if(pRoot == NULL)return;
//
//	//����ջ
//	s_Init(&pStack);
//
//	while(1)
//	{
//		while(pRoot)
//		{
//			//��ӡ ��ջ
//			printf("%d  ",pRoot->nValue);
//			s_Push(pStack,pRoot);
//
//			//������
//			pRoot = pRoot->pLeft;
//		}
//
//		//��ջ
//		pRoot = s_Pop(pStack);
//
//		//��ջ ����
//		if(pRoot == NULL)
//		{
//			break;
//		}
//
//		//������
//		pRoot = pRoot->pRight;
//	}
//}
//
//void UnRecInOrderTraversal(BinaryTree *pRoot)
//{
//	Stack *pStack = NULL;
//	if(pRoot == NULL)return;
//
//	//����ջ
//	s_Init(&pStack);
//
//	while(1)
//	{
//		while(pRoot)
//		{
//			// ��ջ
//			s_Push(pStack,pRoot);
//
//			//������
//			pRoot = pRoot->pLeft;
//		}
//
//		//��ջ
//		pRoot = s_Pop(pStack);
//
//		//��ջ ����
//		if(pRoot == NULL)
//		{
//			break;
//		}
//		//��ӡ
//		printf("%d  ",pRoot->nValue);
//
//		//������
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
//	//����ջ
//	s_Init(&pStack);
//
//	while(1)
//	{
//		while(pRoot)
//		{
//			// ��ջ
//			s_Push(pStack,pRoot);
//
//			//������
//			pRoot = pRoot->pLeft;
//		}
//
//		//��ջ ����
//		if(pStack->pTop == NULL)break;
//
//		//���ջ��Ԫ���Ƿ����� ���Ƿ񱻱�ǹ�
//		if(pStack->pTop->pTree->pRight == NULL || pStack->pTop->pTree->pRight == pMark)
//		{
//			pMark = s_Pop(pStack);
//			printf("%d  ",pMark->nValue);
//		}
//		//���� ��δ�����
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
