#include<stdio.h>
#include<stdlib.h>
struct NODE
{
	int value;
	struct NODE *pNext;
};
void ViewList(struct NODE * pHead)
{

	while(pHead!=NULL)
	{
		printf("%d  ",pHead->value);
		pHead=pHead->pNext;
	}
	printf("\n");
	return ;
}
//递归反向打印链表
void RViewList(struct NODE * pHead)
{
	if(pHead!=NULL)
	{
		if(pHead->pNext!=NULL)
		{
			RViewList(pHead->pNext); //递归
		}
		printf("%d  ",pHead->value);
	}
	return ;
}

void listAdd(struct NODE ** pHead,int value)
{
	struct NODE *temp;
	temp=(struct NODE *)malloc(sizeof(struct NODE));
	temp->value=value;
	temp->pNext=NULL;
	if(*pHead==NULL)
	{
		*pHead=temp;
	}
	else
	{
		struct NODE *pTail=*pHead;
		while(pTail->pNext!=NULL)
		{
			pTail=pTail->pNext;
		}
		pTail->pNext=temp;
	}
	return ;
}
 // throw new RuntimeException("分母不能为0");  


int main(int argc,char *argv[])
{

	struct NODE * pHead=NULL;
	int i=0;
	for(i=0;i<5;i++)
	{
		listAdd(&pHead,i);

	}
	ViewList(pHead);
	RViewList(pHead);
	printf("\n");
	ReverseList(pHead);
	return 0;
}
