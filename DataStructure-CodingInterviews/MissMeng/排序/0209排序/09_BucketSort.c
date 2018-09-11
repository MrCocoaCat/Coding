//#include<stdio.h>
//#include<stdlib.h>
//#include<windows.h>
//
//typedef struct node
//{
//	int nValue;
//	struct node *pNext;
//}MyBucket;
//
//void BucketSort(int arr[],int nLength)
//{
//	int i;
//	int nMax,nMin;
//	int nNum;
//	int nBase;
//	int nMinIndex;
//	int nMaxIndex;
//	int nIndex;
//	MyBucket **pBucket = NULL;
//	MyBucket *pTemp = NULL;
//	MyBucket *pMark = NULL;
//
//	if(arr == NULL || nLength <=0)return;
//
//	//找最大值最小值
//	nMax = arr[0];
//	nMin = arr[0];
//	for(i = 1;i<nLength;i++)
//	{
//		if(arr[i] > nMax)
//		{
//			nMax = arr[i];
//		}
//		if(arr[i] < nMin)
//		{
//			nMin = arr[i];
//		}
//	}
//
//	//数据分析
//	nNum = nMax;
//	i = 0;
//
//	 //数据位数
//	while(nNum)
//	{
//		i++;
//		nNum/=10;
//	}
//		
//	//求被除数
//	nBase = 1;
//	while(i >1)
//	{
//		nBase*=10;
//		i--;
//	}
//
//	nMaxIndex = nMax/nBase;
//	nMinIndex = nMin/nBase;
//
//	//创建桶
//	pBucket = (MyBucket**)malloc(sizeof(MyBucket*)*(nMaxIndex-nMinIndex+1));
//	memset(pBucket,0,sizeof(MyBucket*)*(nMaxIndex-nMinIndex+1));
//
//	//元素入桶
//	for(i = 0;i<nLength;i++)
//	{
//		nIndex = arr[i]/nBase - nMinIndex;
//		pTemp = (MyBucket*)malloc(sizeof(MyBucket));
//		pTemp->nValue = arr[i];
//		pTemp->pNext = NULL;
//
//		//插入
//		if(pBucket[nIndex] == NULL || pBucket[nIndex]->nValue > pTemp->nValue)
//		{
//			pTemp->pNext = pBucket[nIndex];
//			pBucket[nIndex] = pTemp;
//		}
//		else
//		{
//			pMark = pBucket[nIndex];
//			while(pMark->pNext != NULL && pMark->pNext->nValue < pTemp->nValue)
//			{
//				pMark = pMark->pNext;
//			}
//
//			pTemp->pNext = pMark->pNext;
//			pMark->pNext = pTemp;
//		}
//	}
//
//	//放回原数组
//	nIndex = 0;
//	for(i = 0;i<nMaxIndex-nMinIndex+1;i++)
//	{
//		pMark = pBucket[i];
//		while(pMark)
//		{
//			arr[nIndex] = pMark->nValue;
//			nIndex++;
//			pMark = pMark->pNext;
//		}
//	}
//
//	//释放
//	for(i = 0;i<nMaxIndex-nMinIndex+1;i++)
//	{
//		pMark = pBucket[i];
//		while(pMark)
//		{
//			pTemp = pMark;
//			pMark = pMark->pNext;
//			free(pTemp);
//			pTemp = NULL;
//		}
//	}
//
//	free(pBucket);
//	pBucket = NULL;
//}
//
//int main()
//{
//	int arr[] = {104,223,186,287,329,119,408,527,100,130,160};
//	int i;
//
//	BucketSort(arr,sizeof(arr)/sizeof(arr[0]));
//
//	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
//	{
//		printf("%d  ",arr[i]);
//	}
//	return 0;
//}