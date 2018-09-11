#include"lib.h"
Node * ArrToBiTree(int arr[],int len)
{
	if(arr==NULL||len<0)
	{
		return NULL;
	}
	int i=0;
	// malloc arr of Node
	Node * pTree=(Node *)malloc(sizeof(Node)*len);
	//init Node arr
	for(i=0;i<len;i++)
	{
		pTree[i].value=arr[i];
		pTree[i].pLeft=NULL;
		pTree[i].pRight=NULL;
	}
	for(i=0;i<len/2;i++)
	{
		if(2*i+1<len)
		{
			pTree[i].pLeft=&pTree[2*i+1];
		}
		if(2*i+2<len)
		{
			pTree[i].pRight=&pTree[2*i+2];
		}
	}
return pTree;
}

