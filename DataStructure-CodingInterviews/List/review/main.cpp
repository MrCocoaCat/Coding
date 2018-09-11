#include<iostream>
#include"CreateNode.h"
//using namespace std;
static int num = 0;
int main()
{
	Node * pHead = NULL;
	for(int i= 0;i<5;i++)
	{
		AddListEnd(pHead,num);
		num+=3;
	}
	//PrintList(pHead);
	//pHead=ReList(pHead);
	//PrintList(pHead);
	//�ݹ�����
	//RecursionList( pHead,pHead);
	PrintList(pHead);

	//MergeTwoList();

}