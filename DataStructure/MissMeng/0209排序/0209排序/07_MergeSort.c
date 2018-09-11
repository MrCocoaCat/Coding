//#include<stdio.h>
//#include<stdlib.h>
//
//void Merge(int arr[],int nLow,int nHigh)
//{
//	int nBegin1;
//	int nEnd1;
//	int nBegin2;
//	int nEnd2;
//	int *pTemp = NULL;
//	int i;
//
//	nBegin1 = nLow;
//	nEnd1 = (nLow+nHigh)/2;
//	nBegin2 = nEnd1+1;
//	nEnd2 = nHigh;
//
//	//申请辅助数组
//	pTemp = (int *)malloc(sizeof(int ) * (nHigh-nLow+1));
//
//	i = 0;
//	while(nBegin1 <= nEnd1 && nBegin2 <= nEnd2)
//	{
//		if(arr[nBegin1] < arr[nBegin2])
//		{
//			pTemp[i] = arr[nBegin1];
//			nBegin1++;
//		}
//		else
//		{
//			pTemp[i] = arr[nBegin2];
//			nBegin2++;
//		}
//		i++;
//	}
//
//	//处理有剩余的数组
//	while(nBegin1 <= nEnd1)
//	{
//		pTemp[i] = arr[nBegin1];
//		nBegin1++;
//		i++;
//	}
//
//	while(nBegin2 <= nEnd2)
//	{
//		pTemp[i] = arr[nBegin2];
//		nBegin2++;
//		i++;
//	}
//
//	//临时数组元素放回原数组
//	for(i = 0;i<nHigh-nLow+1;i++)
//	{
//		arr[nLow+i] = pTemp[i];
//	}
//
//	//释放
//	free(pTemp);
//	pTemp = NULL;
//}
//
//void MergeSort(int arr[],int nLow,int nHigh)
//{
//	int nMid;
//	if(arr == NULL || nLow >= nHigh)return;
//
//	//拆分
//	nMid = (nLow+nHigh)/2;
//	MergeSort(arr,nLow,nMid);
//	MergeSort(arr,nMid+1,nHigh);
//
//	//合并
//	Merge(arr,nLow,nHigh);
//}
//
//
//int main()
//{
//	int arr[] = {10,3,16,7,29,19,8,57,100,130,160};
//	int i;
//
//	MergeSort(arr,0,sizeof(arr)/sizeof(arr[0])-1);
//
//	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
//	{
//		printf("%d  ",arr[i]);
//	}
//	return 0;
//}