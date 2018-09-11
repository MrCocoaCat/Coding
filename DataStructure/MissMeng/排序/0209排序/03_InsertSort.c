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
//		//遍历有序数组 找到合适位置
//		while(arr[j] > temp && j>=0) //把temp 插入到排序数组中，如果temp 比当前位小，则依次向前找，同时整体向后移位。
//			//直到找到不小的。找到后,将temp 放入数组中。
//		{
//			arr[j+1] = arr[j];
//			j--;
//		}
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
//	system("pause");
//	return 0;
//}