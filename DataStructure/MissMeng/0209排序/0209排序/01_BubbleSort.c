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
//		//��������δ�������Ԫ��������ֵ���ں���
//		for(j = 0;j<nLength-1-i ;j++)
//		{
//			//��������Ԫ�ؽ��д�С�Ƚ� ǰ���С�򽻻�
//			if(arr[j] > arr[j+1])
//			{
//				//�����м����ʵ������������ͬ�������ݵĻ���
//				arr[j] = arr[j] ^ arr[j+1];
//				arr[j+1] = arr[j] ^ arr[j+1];
//				arr[j] = arr[j] ^ arr[j+1];
//
//				//��ǵ�ǰ��󽻻�λ��
//				nFlag = j+1;		
//			}
//		}
//
//		if(nFlag == 0)
//		{
//			break;
//		}
//
//		//��������ִ�д���
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