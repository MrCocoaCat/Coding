//#include<stdio.h>
//#include<stdlib.h>
//#include<windows.h>
//
//void CountSort(int arr[],int nLength)
//{
//	int i;
//	int nMin,nMax;
//	int *pCount = NULL;
//	int j;
//
//	if(arr == NULL || nLength <=0)return;
//
//	//�����ֵ��Сֵ
//	nMin = arr[0];
//	nMax = arr[0];
//	for(i = 1;i<nLength;i++)
//	{
//		if(arr[i] < nMin)
//		{
//			nMin = arr[i];
//		}
//		if(arr[i] > nMax)
//		{
//			nMax = arr[i];
//		}
//	}
//
//	//���ټ�������
//	pCount = (int *)malloc(sizeof(int) *(nMax-nMin+1));
//	memset(pCount,0,sizeof(int) *(nMax-nMin+1));
//
//	//����ԭ���� ��ʼ����
//	for(i = 0;i<nLength;i++)
//	{
//		pCount[arr[i]-nMin]++;
//	}
//
//	//��ԭ�������ֵ
//	j = 0;
//	for(i = 0;i<nMax-nMin+1;i++)
//	{
//		while(pCount[i] != 0)
//		{
//			arr[j] = i+nMin;
//			j++;
//			pCount[i]--;
//		}
//	}
//
//	//�ͷ�
//	free(pCount);
//	pCount = NULL;
//}
//
//int main()
//{
//	int arr[] = {2,4,3,4,4,4,6,7,6,4,1,2,4};
//	int i;
//
//	CountSort(arr,sizeof(arr)/sizeof(arr[0]));
//
//	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
//	{
//		printf("%d  ",arr[i]);
//	}
//	return 0;
//}