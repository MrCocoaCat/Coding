#include<iostream>
#include"CreateNode.h"

//非递归
Node * ReList(Node * pHead)
{
	if(pHead == NULL)
	{
		return NULL;
	}
	Node * p1 = NULL;
	Node * p2 = pHead;
	Node * p3 = p2->pNext;
	while(p3 != NULL)
	{
		p2->pNext = p1;

		p1 = p2;
		p2 = p3;
		p3 = p3->pNext;
	}
	p2->pNext = p1;  //�˳�ʱ����δ���ӵĽڵ�
	return p2;
}


//递归
Node* RecursionList(Node* pNode,Node*& head)
{
	if(pNode == NULL || pNode->pNext == NULL)
    {
          head->pNext = NULL;    //�ѷ�ת������һ���ڵ��next����ΪNULL
          head = pNode;
          return pNode;
     }
     Node* tmpNode = RecursionList(pNode->pNext,head);//����ԭ������pNode����һ���ڵ�,ÿ�εݹ�����ƶ�
     tmpNode->pNext = pNode;
     return pNode; //�ݹ��temNode ��ֵ��Ҳ����ÿ��tmp �����¸�
}

int main()
{
    Node * pHead = NULL;
    CreateList(pHead,0,5);
    PrintList(pHead);

    pHead=ReList(pHead);
    PrintList(pHead);

    RecursionList( pHead,pHead);
    PrintList(pHead);


    //MergeTwoList();

}