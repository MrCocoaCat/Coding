//#include<stdio.h>
//
//void SelectSort(int arr[],int nLength)
//{
//	int i;
//	int j;
//	int nMinIndex;
//
//	if(arr == NULL || nLength <=0)return;
//
//	for(i = 0;i<nLength;i++)
//	{
//		nMinIndex = i;
//
//		//找到最小值
//		for(j = i+1;j<nLength;j++)
//		{
//			if(arr[j] < arr[nMinIndex])
//			{
//				nMinIndex = j;
//			}
//		}
//
//		//交换
//		if(nMinIndex != i)
//		{
//			arr[nMinIndex] = arr[i] ^ arr[nMinIndex];
//			arr[i] = arr[i] ^ arr[nMinIndex];
//			arr[nMinIndex] = arr[i] ^ arr[nMinIndex];
//		}
//	}
//}
//
//int main()
//{
//	int arr[] = {10,3,16,7,29,19,8,57,100,130,160};
//	int i;
//
//	SelectSort(arr,sizeof(arr)/sizeof(arr[0]));
//
//	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
//	{
//		printf("%d  ",arr[i]);
//	}
//	return 0;
//}