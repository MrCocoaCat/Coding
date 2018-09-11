//
// Created by liyubo on 28/01/18.
//

#include"CreateNode.h"
#include<iostream>
void PrintList(Node * pHead)
{
    while(pHead != NULL)
    {
        std::cout<<pHead->val<<"  ";
        pHead=pHead->pNext;
    }
    std::cout<<std::endl;
}
void AddListEnd(Node * &pHead,int val)
{

    if(pHead == NULL)
    {
        pHead = new Node;
        pHead->val = val;
        pHead->pNext = NULL;
    }
    else
    {
        Node * pTemp = new Node;
        pTemp->val = val;
        pTemp->pNext = NULL;
        Node * pHeadTemp =pHead;
        while(pHeadTemp->pNext != NULL)
        {
            pHeadTemp=pHeadTemp->pNext;
        }
        pHeadTemp->pNext=pTemp;
    }
}

void CreateList(Node * &pHead,int firval,int num)
{

    for(int i= 0;i<num;i++)
    {
        AddListEnd(pHead,firval);
        firval+=3;
    }
}
