//#include<stdio.h>
//
//int BinaryChop(int arr[],int nLength,int nNum)
//{
//	int nLow;
//	int nHigh;
//	int nMid;
//	if(arr == NULL || nLength <=0)return -1;
//
//	nLow = 0;
//	nHigh = nLength-1;
//
//	while(nLow <= nHigh)
//	{
//		//找到中间位置
//		nMid = (nLow+nHigh)/2;
//
//		//大小比较
//		if(arr[nMid] == nNum)
//		{
//			return nMid;
//		}
//
//		//比中间值小  去左侧的区间查找
//		else if(arr[nMid] > nNum )
//		{
//			nHigh = nMid-1;
//		}
//
//		//比中间值大  去右区间查找
//		else
//		{
//			nLow = nMid+1;
//		}
//	}
//
//	//查找失败
//	return -1;
//}
//
//int main()
//{
//	int arr[] = {1,3,4,5,6,12,25,36,47,59};
//	int nIndex = BinaryChop(arr,sizeof(arr)/sizeof(arr[0]),470);
//	printf("%d\n",nIndex);
//	return 0;
//}