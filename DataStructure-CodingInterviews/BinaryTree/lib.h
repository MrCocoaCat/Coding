#include<stdio.h>
#include<stdlib.h>
typedef struct NODE
{
int value;
struct NODE *pLeft;
struct NODE *pRight;
}Node; 

void PreOrderTraversal(Node * pRoot);
void InOrderTraversal(Node * pRoot);
void PostOrderTraversal(Node * pRoot);
