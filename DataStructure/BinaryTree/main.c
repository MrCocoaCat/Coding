#include"lib.h"
void fun(Node * temp);
Node * ArrToBiTree(int arr[],int len);
int main(int argc,char * argv[])
{
	int arr[10]={1,2,3,4,5,6,7,8,9,0};
	Node *pRoot;
	pRoot=ArrToBiTree(arr,sizeof(arr)/sizeof(arr[0]));
	PreOrderTraversal(pRoot);
	printf("\n");
	InOrderTraversal(pRoot);
	printf("\n");
	PostOrderTraversal(pRoot);
	printf("\n");

	return 0;
}
