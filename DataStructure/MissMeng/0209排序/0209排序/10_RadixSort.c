//#include<stdio.h>
//#include<stdlib.h>
//#include<windows.h>
//
//typedef struct node
//{
//	int nValue;
//	struct node *pNext;
//}MyRadix;
//
//void Sort(int arr[],int nLength,int i)
//{
//	int nBase;
//	MyRadix **pRadix = NULL;
//	int nIndex;
//	MyRadix *pMark = NULL;
//	MyRadix *pTemp = NULL;
//
//	//�󱻳���
//	nBase = 1;
//	while(i >1)
//	{
//		nBase*=10;
//		i--;
//	}
//
//	//��Ͱ
//	pRadix = (MyRadix**)malloc(sizeof(MyRadix*)*10);
//	memset(pRadix,0,sizeof(MyRadix*)*10);
//
//	for(i = 0;i<nLength;i++)
//	{
//		nIndex = arr[i]/nBase%10;
//		pTemp = (MyRadix*)malloc(sizeof(MyRadix));
//		pTemp->nValue = arr[i];
//		pTemp->pNext = NULL;
//
//		if(pRadix[nIndex] == NULL)
//		{
//			pRadix[nIndex] = pTemp;
//		}
//		else
//		{
//			pMark = pRadix[nIndex];
//			while(pMark->pNext != NULL)
//			{
//				pMark = pMark->pNext;
//			}
//			pMark->pNext = pTemp;
//		}
//	}
//
//	//���ݷŻ�ԭ����
//	nIndex = 0;
//	for(i = 0;i<10;i++)
//	{
//		pMark = pRadix[i];
//		while(pMark)
//		{
//			arr[nIndex] = pMark->nValue;
//			nIndex++;
//			pMark = pMark->pNext;
//		}
//	}
//
//	//�ͷ�
//	for(i = 0;i<10;i++)
//	{
//		pMark = pRadix[i];
//		while(pMark)
//		{
//			pTemp = pMark;
//			pMark = pMark->pNext;
//			free(pTemp);
//			pTemp = NULL;
//		}
//	}
//
//	free(pRadix);
//	pRadix = NULL;
//}
//
//void RadixSort(int arr[],int nLength)
//{
//	int nMax;
//	int i;
//	int nLoopTimes;
//	if(arr == NULL || nLength <=0)return;
//
//	//�����ֵ
//	nMax = arr[0];
//	for(i = 1;i<nLength;i++)
//	{
//		if(arr[i] > nMax)
//		{
//			nMax = arr[i];
//		}
//	}
//
//	//������ֵλ��
//	nLoopTimes = 0;
//	while(nMax)
//	{
//		nLoopTimes++;
//		nMax/=10;
//	}
//
//	//����λ��Ͱ
//	for(i =1;i<=nLoopTimes;i++)
//	{
//		Sort(arr,nLength,i);
//	}
//}
//
//int main()
//{
//	int arr[] = {4,23,186,87,329,19,8,27,10,130,16};
//	int i;
//
//	RadixSort(arr,sizeof(arr)/sizeof(arr[0]));
//
//	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
//	{
//		printf("%d  ",arr[i]);
//	}
//	system("pause");
//	return 0;
//}