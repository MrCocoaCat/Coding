//#include<stdio.h>
//
////�ڿ����
//int  Sort(int arr[],int nLow,int nHigh)
//{
//	int temp;
//	temp = arr[nLow];
//
//	while(nLow < nHigh)
//	{
//		//�Ӻ���ǰ�ұȱ�׼ֵС��
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
//		//��ǰ����ұȱ�׼ֵ���
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
//	//��׼ֵ�ŵ���Ӧλ��
//	arr[nLow] = temp;
//	return nLow;
//}
//
//����ָ
int Sort2(int arr[],int nLow,int nHigh)
{
	int nSmall;
	nSmall = nLow-1;
	for(nLow;nLow < nHigh;nLow++)
	{
		//С��������
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
	//��׼ֵ����
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
//	//�ҵ���׼ֵλ��
//	nStandard = Sort2(arr,nLow,nHigh);
//
//	//ͨ����׼ֵ������ֳ������֣������ֱַ�������ϲ���
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