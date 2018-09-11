//#include<stdio.h>
//
//void BubbleSort(int arr[],int nLength)
//{
//	int i;
//	int j;
//	int nFlag = 0;
//
//	if(arr == NULL || nLength <=0)return;
//
//	for(i = 0;i<nLength;i++)
//	{
//		nFlag = 0;
//		//将数组内未处理过的元素里的最大值放在后面
//		for(j = 0;j<nLength-1-i ;j++)
//		{
//			//相邻两个元素进行大小比较 前大后小则交换
//			if(arr[j] > arr[j+1])
//			{
//				//不用中间变量实现两个类型相同变量内容的互换
//				arr[j] = arr[j] ^ arr[j+1];
//				arr[j+1] = arr[j] ^ arr[j+1];
//				arr[j] = arr[j] ^ arr[j+1];
//
//				//标记当前最大交换位置
//				nFlag = j+1;		
//			}
//		}
//
//		if(nFlag == 0)
//		{
//			break;
//		}
//
//		//减少整体执行次数
//		i = nLength - nFlag -1;
//	}
//}
//
//int main()
//{
//	int arr[] = {10,3,16,7,29,19,8,57,100,130,160};
//	int i;
//
//	BubbleSort(arr,sizeof(arr)/sizeof(arr[0]));
//
//	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
//	{
//		printf("%d  ",arr[i]);
//	}
//	return 0;
//}