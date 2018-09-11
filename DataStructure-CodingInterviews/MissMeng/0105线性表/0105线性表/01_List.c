//#include<stdio.h>
//#include<stdlib.h>
//
//
//typedef struct node
//{
//	int nValue;
//	struct node *pNext;
//}MyList;
//
//MyList *CreateList( )
//{
//	MyList *pHead = NULL;
//	MyList *pTail = NULL;
//	MyList *pTemp = NULL;
//	int nValue;
//
//	scanf("%d",&nValue);
//
//	while(nValue != 0)
//	{
//		pTemp = (MyList*)malloc(sizeof(MyList));
//		pTemp->nValue = nValue;
//		pTemp->pNext = NULL;
//
//		if(pHead == NULL)
//		{
//			pHead = pTemp;
//		}
//		else
//		{
//			pTail->pNext = pTemp;
//		}
//		pTail = pTemp;
//		scanf("%d",&nValue);
//	}
//	return pHead;
//}
//
//void Print(MyList *pHead)
//{
//	if(pHead == NULL)return;
//	while(pHead)
//	{
//		printf("%d  ",pHead->nValue);
//		pHead = pHead->pNext;
//	}
//}
//
////链表的倒序输出
//void ReversePrint(MyList *pHead)
//{
//	if(pHead == NULL)return;
//
//	ReversePrint(pHead->pNext);
//	printf("%d  ",pHead->nValue);
//}
//
////链表倒置
//MyList *ReverseList(MyList *pHead)
//{
//	MyList *p1 = NULL;
//	MyList *p2 = NULL;
//	MyList *p3 = NULL; //标记被断开位置
//
//	if(pHead == NULL)return NULL;
//
//	p1 = NULL;
//	p2 = pHead;
//	p3 = pHead->pNext;
//
//	while(p3 != NULL)
//	{
//		p2->pNext = p1;
//		
//		p1 = p2;
//		p2 = p3;
//		p3 = p3->pNext;
//	}
//
//	p2->pNext = p1;
//	return p2;
//}
//
//int main()
//{
//	MyList *pHead = NULL;
//
//	pHead = CreateList();
//	Print(pHead);
//	printf("\n");
//	//ReversePrint(pHead);
//	pHead = ReverseList(pHead);
//	Print(pHead);
//	return 0;
//}