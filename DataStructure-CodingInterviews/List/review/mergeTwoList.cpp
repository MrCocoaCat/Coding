#include<iostream>
#include"CreateNode.h"

void CreatTwoList( Node * &pHead1,Node * &pHead2)
{
	for(int i = 0;i<10;i++)
	{
		if(i%2)
		{
			AddListEnd(pHead1,i);
		}
		else
		{
			AddListEnd(pHead2,i);
		}
	}
}

void MergeTwoList()
{
	Node * pHead1 = NULL;
	Node * pHead2 = NULL;
	CreatTwoList( pHead1,pHead2);
	PrintList(pHead1);
	PrintList(pHead2);

}
int main()
{
    Node * pHead1 = NULL;
    Node * pHead2 = NULL;
    CreatTwoList(pHead1,pHead2);
    PrintList(pHead1);
    PrintList(pHead2);



}

