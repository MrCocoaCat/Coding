//#include<stdio.h>
//
//#define LEFT 2*nRootID+1
//#define RIGHT 2*nRootID +2
//
//void Adjust(int arr[],int nLength,int nRootID)
//{
//	while(1)
//	{
//		//两个孩子
//		if(RIGHT < nLength)
//		{
//			//比较两个孩子大小
//			if(arr[LEFT] > arr[RIGHT])
//			{
//				//大的与父亲进行比较
//				if(arr[LEFT] > arr[nRootID])
//				{
//					//交换
//					arr[LEFT ]  = arr[LEFT ] ^ arr[nRootID];
//					arr[nRootID ]  = arr[LEFT ] ^ arr[nRootID];
//					arr[LEFT ]  = arr[LEFT ] ^ arr[nRootID];
//
//					nRootID = LEFT;
//					continue;
//				}
//				else
//				{
//					break;
//				}
//			}
//			else
//			{
//				//大的与父亲进行比较
//				if(arr[RIGHT] > arr[nRootID])
//				{
//					//交换
//					arr[RIGHT ]  = arr[RIGHT ] ^ arr[nRootID];
//					arr[nRootID ]  = arr[RIGHT ] ^ arr[nRootID];
//					arr[RIGHT ]  = arr[RIGHT ] ^ arr[nRootID];
//
//					nRootID = RIGHT;
//					continue;
//				}
//				else
//				{
//					break;
//				}
//			}
//		}
//		//一个孩子
//		else if(LEFT < nLength)
//		{
//			//大的与父亲进行比较
//			if(arr[LEFT] > arr[nRootID])
//			{
//				//交换
//				arr[LEFT ]  = arr[LEFT ] ^ arr[nRootID];
//				arr[nRootID ]  = arr[LEFT ] ^ arr[nRootID];
//				arr[LEFT ]  = arr[LEFT ] ^ arr[nRootID];
//
//				nRootID = LEFT;
//				continue;
//			}
//			else
//			{
//				break;
//			}
//		}
//		//没有孩子 
//		else
//		{
//			break;
//		}
//	}
//}
//
//void Adjust2(int arr[],int nLength,int nRootID)
//{
//	int MAX;
//	for(MAX = LEFT;MAX < nLength; MAX = LEFT )
//	{
//		//两个孩子
//		if(RIGHT < nLength)
//		{
//			if(arr[RIGHT] > arr[LEFT])
//			{
//				MAX = RIGHT;
//			}
//		}
//
//		//当前最大值和父亲比较
//		if(arr[MAX] > arr[nRootID])
//		{
//			arr[MAX] = arr[MAX] ^ arr[nRootID];
//			arr[nRootID] = arr[MAX] ^ arr[nRootID];
//			arr[MAX] = arr[MAX] ^ arr[nRootID];
//
//			nRootID = MAX;
//		}
//		else
//		{
//			break;
//		}
//	}
//}
//
//void HeapSort(int arr[],int nLength)
//{
//	int i;
//	if(arr == NULL || nLength <=0)return;
//
//	//建初始堆
//	for(i = nLength/2-1;i>=0;i--)
//	{
//		//从各个父亲节点开始调整
//		Adjust2(arr,nLength,i);
//	}
//
//	//排序
//	for(i = nLength-1;i>0;i--)
//	{
//		//交换
//		arr[0] = arr[0] ^ arr[i];
//		arr[i] = arr[0] ^ arr[i];
//		arr[0] = arr[0] ^ arr[i];
//
//		//重新调整堆顶
//		Adjust2(arr,i,0);
//	}
//
//}
//
//int main()
//{
//	int arr[] = {10,3,16,7,29,19,8,57,100,130,160};
//	int i;
//
//	HeapSort(arr,sizeof(arr)/sizeof(arr[0]));
//
//	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
//	{
//		printf("%d  ",arr[i]);
//	}
//	return 0;
//}