//#include<stdio.h>
//
//void ShellSort(int arr[],int nLength)
//{
//	int nGap;
//	int j;
//	int i;
//	int k;
//	int temp;
//	if(arr == NULL || nLength <=0)return;
//
//	//定步长
//	for(nGap = nLength/2;nGap >=1;nGap/=2)
//	{
//		//各组内插入排序
//		for(i = 0;i<nGap;i++)
//		{
//			//插入排序
//			//无序数组
//			for(j = i+nGap;j<nLength;j+=nGap)
//			{
//				k = j-nGap;//有序数组的最后一个
//				temp = arr[j];//无序数组的第一个
//				while(arr[k] > temp&&k>=0)
//				{
//					arr[k+nGap] = arr[k];
//					k-=nGap;
//				}
//
//				arr[k+nGap] = temp;
//			}
//		}
//	}
//
//}
//
//void ShellSort2(int arr[],int nLength)
//{
//	int nGap;
//	int j;
//	int k;
//	int temp;
//	if(arr == NULL || nLength <=0)return;
//
//	//定步长
//	for(nGap = nLength/2;nGap >=1;nGap/=2)
//	{
//		//各组内插入排序
//		//插入排序
//		//无序数组
//		for(j = nGap;j<nLength;j++)
//		{
//			k = j-nGap;//有序数组的最后一个
//			temp = arr[j];//无序数组的第一个
//			while(arr[k] > temp&&k>=0)
//			{
//				arr[k+nGap] = arr[k];
//				k-=nGap;
//			}
//
//			arr[k+nGap] = temp;
//		}
//	}
//
//}
//
//
//int main()
//{
//	int arr[] = {10,3,16,7,29,19,8,57,100,130,160};
//	int i;
//
//	ShellSort2(arr,sizeof(arr)/sizeof(arr[0]));
//
//	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
//	{
//		printf("%d  ",arr[i]);
//	}
//	return 0;
//}