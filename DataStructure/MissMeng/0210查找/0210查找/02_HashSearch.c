//#include<stdio.h>
//#include<stdlib.h>
//#include<windows.h>
//
//typedef struct node
//{
//	int nValue;
//	int nIndex;
//	struct node *pNext;
//}Hash;
//
//
//Hash **CreateHashTable(int arr[],int nLength)
//{
//	Hash **pHash = NULL;
//	int i;
//	Hash *pTemp = NULL;
//	int nIndex;
//
//	pHash = (Hash**)malloc(sizeof(Hash*)*nLength);
//	memset(pHash,0,sizeof(Hash*)*nLength);
//
//	//数据元素放入哈希表
//	for(i = 0;i<nLength;i++)
//	{
//		nIndex = arr[i]%nLength;
//		pTemp = (Hash*)malloc(sizeof(Hash));
//		pTemp->nIndex = i;
//		pTemp->nValue = arr[i];
//
//		pTemp->pNext = pHash[nIndex];
//		pHash[nIndex] = pTemp;
//	}
//	return pHash;
//}
//
//int  HashSearch(int arr[],int nLength,int nNum)
//{
//	Hash **pHash = NULL;
//	int nIndex;
//	Hash *pMark = NULL;
//	int n =-1;
//	int i;
//	Hash *pDel = NULL;
//
//	if(arr == NULL || nLength <=0)return;
//
//	//创建哈希表
//	pHash = CreateHashTable(arr,nLength);
//
//	//查找
//	nIndex = nNum%nLength;
//
//	pMark = pHash[nIndex];
//	while(pMark)
//	{
//		if(pMark->nValue == nNum)
//		{
//			n =  pMark->nIndex;
//			break;
//		}
//		pMark = pMark->pNext;
//	}
//
//	//释放
//	//小链表释放
//	for(i = 0;i<nLength;i++)
//	{
//		pMark = pHash[i];
//		while(pMark)
//		{
//			pDel = pMark;
//			pMark = pMark->pNext;
//			free(pDel);
//			pDel = NULL;
//		}
//	}
//
//	free(pHash);
//	pHash = NULL;
//
//	return n;
//}
//
//int main()
//{
//	int arr[] = {1,3,4,5,6,12,25,36,47,59};
//	int nIndex = HashSearch(arr,sizeof(arr)/sizeof(arr[0]),47);
//	printf("%d\n",nIndex);
//	return 0;
//}