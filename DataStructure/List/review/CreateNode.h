//
// Created by liyubo on 28/01/18.
//

#ifndef REVIEW_CREATENODE_H
#define REVIEW_CREATENODE_H

#endif //REVIEW_CREATENODE_H
struct Node
{
    int val;
    Node *pNext;
};
void PrintList(Node * pHead);
void AddListEnd(Node * &pHead,int val);
void CreateList(Node * &pHead,int firval,int num);