//#include<stdio.h>
//
//void InsertSort(int arr[],int nLength)
//{
//	int i; 
//	int j; 
//	int temp;
//	if(arr == NULL || nLength <=0)return;
//
//	//无序数组
//	for(i = 1;i<nLength;i++)
//	{
//		j = i-1;  //有序数组的最后一个
//		temp = arr[i];  //无序数组的第一个
//
//		//遍历有序数组 找到合适位置
//		while(arr[j] > temp && j>=0)
//		{
//			arr[j+1] = arr[j];
//			j--;
//		}
//
//		//放入到对应位置上
//		arr[j+1] = temp;
//	}
//
//}
//
//int main()
//{
//	int arr[] = {10,3,16,7,29,19,8,57,100,130,160};
//	int i;
//
//	InsertSort(arr,sizeof(arr)/sizeof(arr[0]));
//
//	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
//	{
//		printf("%d  ",arr[i]);
//	}
//	return 0;
//}