//#include<stdio.h>
//
//#define LEFT 2*nRootID+1
//#define RIGHT 2*nRootID +2
//
//void Adjust(int arr[],int nLength,int nRootID)
//{
//	while(1)
//	{
//		//��������
//		if(RIGHT < nLength)
//		{
//			//�Ƚ��������Ӵ�С
//			if(arr[LEFT] > arr[RIGHT])
//			{
//				//����븸�׽��бȽ�
//				if(arr[LEFT] > arr[nRootID])
//				{
//					//����
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
//				//����븸�׽��бȽ�
//				if(arr[RIGHT] > arr[nRootID])
//				{
//					//����
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
//		//һ������
//		else if(LEFT < nLength)
//		{
//			//����븸�׽��бȽ�
//			if(arr[LEFT] > arr[nRootID])
//			{
//				//����
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
//		//û�к��� 
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
//		//��������
//		if(RIGHT < nLength)
//		{
//			if(arr[RIGHT] > arr[LEFT])
//			{
//				MAX = RIGHT;
//			}
//		}
//
//		//��ǰ���ֵ�͸��ױȽ�
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
//	//����ʼ��
//	for(i = nLength/2-1;i>=0;i--)
//	{
//		//�Ӹ������׽ڵ㿪ʼ����
//		Adjust2(arr,nLength,i);
//	}
//
//	//����
//	for(i = nLength-1;i>0;i--)
//	{
//		//����
//		arr[0] = arr[0] ^ arr[i];
//		arr[i] = arr[0] ^ arr[i];
//		arr[0] = arr[0] ^ arr[i];
//
//		//���µ����Ѷ�
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