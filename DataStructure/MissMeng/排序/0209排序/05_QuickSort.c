//#include<stdio.h>
//
////挖坑填补法
//int  Sort(int arr[],int nLow,int nHigh)
//{
//	int temp;
//	temp = arr[nLow];
//
//	while(nLow < nHigh)
//	{
//		//从后向前找比标准值小的
//		while(nLow < nHigh)
//		{
//			if(arr[nHigh] < temp)
//			{
//				arr[nLow] = arr[nHigh];
//				nLow++;
//				break;
//			}
//			else
//			{
//				nHigh--;
//			}
//		}
//
//		//从前向后找比标准值大的
//		while(nLow < nHigh)
//		{
//			if(arr[nLow] > temp)
//			{
//				arr[nHigh] = arr[nLow];
//				nHigh--;
//				break;
//			}
//			else
//			{
//				nLow++;
//			}
//		}
//	}
//
//	//标准值放到对应位置
//	arr[nLow] = temp;
//	return nLow;
//}
//
//区间分割法
int Sort2(int arr[],int nLow,int nHigh)
{
	int nSmall;
	nSmall = nLow-1;
	for(nLow;nLow < nHigh;nLow++)
	{
		//小区间扩张
		if(arr[nLow] < arr[nHigh])
		{
			if(++nSmall != nLow)
			{
				arr[nSmall] = arr[nSmall] ^ arr[nLow];
				arr[nLow] = arr[nSmall] ^ arr[nLow];
				arr[nSmall] = arr[nSmall] ^ arr[nLow];
			}
		}
	}
	//标准值放置
	if(++nSmall != nHigh)
	{
		arr[nSmall] = arr[nSmall] ^ arr[nHigh];
		arr[nHigh] = arr[nSmall] ^ arr[nHigh];
		arr[nSmall] = arr[nSmall] ^ arr[nHigh];
	}
	return nSmall;
}


//
//void QuickSort(int arr[],int nLow,int nHigh)
//{
//	int nStandard;
//	if(arr == NULL || nLow >=nHigh)return;
//
//	//找到标准值位置
//	nStandard = Sort2(arr,nLow,nHigh);
//
//	//通过标准值将数组分成两部分，各部分分别进行以上操作
//	QuickSort(arr,nLow,nStandard-1);
//	QuickSort(arr,nStandard+1,nHigh);
//}
//
//
//int main()
//{
//		int arr[] = {10,3,16,7,29,19,8,57,100,130,160};
//	int i;
//
//	QuickSort(arr,0,sizeof(arr)/sizeof(arr[0])-1);
//
//	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
//	{
//		printf("%d  ",arr[i]);
//	}
//	return 0;
//}