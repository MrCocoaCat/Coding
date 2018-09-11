#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	int nValue;
	struct node *pNext;
}MyStack;

typedef struct node2
{
	MyStack *pTop;
	int nCount;
}Stack;

void s_Init(Stack **pStack)
{
	if(pStack == NULL)return;

	//申请栈空间  赋初值
	*pStack = (Stack*)malloc(sizeof(Stack));
	(*pStack)->nCount = 0;
	(*pStack)->pTop = NULL;
}

void s_Push(Stack *pStack,int nValue)
{
	MyStack *pTemp = NULL;

	if(pStack == NULL )
	{
		printf("栈不存在TAT\n");
		return;
	}

	pTemp = (MyStack*)malloc(sizeof(MyStack));
	pTemp->nValue = nValue;

	//头添加  
	pTemp->pNext = pStack->pTop;
	pStack->pTop = pTemp;

	//更新栈内元素个数
	pStack->nCount++;
}

int s_Pop(Stack *pStack)
{
	MyStack *pDel = NULL;
	int nNum;
	if(pStack == NULL || pStack->pTop == NULL)return -1;

	//标记被删除节点 和值
	pDel = pStack->pTop;
	nNum = pDel->nValue;

	//头删除
	pStack->pTop = pStack->pTop->pNext;
	free(pDel);
	pDel = NULL;

	//更新栈内元素个数
	pStack->nCount--;

	return nNum;
}

void s_Clear(Stack *pStack)
{
	if(pStack == NULL || pStack->pTop == NULL)return;
	while(pStack->nCount != 0)
	{
		s_Pop(pStack);
	}
}

void s_Destroy(Stack **pStack)
{
	if(pStack == NULL)return;
	s_Clear(*pStack);

	free(*pStack);
	*pStack = NULL;
}

MyStack *s_GetTop(Stack *pStack)
{
	if(pStack == NULL)return NULL;
	return pStack->pTop;
}

int s_GetCount(Stack *pStack)
{
	if(pStack == NULL)return -1;
	return pStack->nCount;
}

int s_IsEmpty(Stack *pStack)
{
	if(pStack == NULL)return -1;
	return (pStack->nCount == 0) ? 1:0;
}

int main()
{
	Stack *pStack = NULL;
	s_Init(&pStack);

	s_Push(pStack,1);
	s_Push(pStack,2);
	s_Push(pStack,3);
	s_Push(pStack,4);

	printf("%d\n",s_Pop(pStack));
	printf("%d\n",s_Pop(pStack));
	printf("%d\n",s_Pop(pStack));

	s_Destroy(&pStack);
	s_Push(pStack,100);

	return 0;
}