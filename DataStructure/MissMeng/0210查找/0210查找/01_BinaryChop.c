//#include<stdio.h>
//
//int BinaryChop(int arr[],int nLength,int nNum)
//{
//	int nLow;
//	int nHigh;
//	int nMid;
//	if(arr == NULL || nLength <=0)return -1;
//
//	nLow = 0;
//	nHigh = nLength-1;
//
//	while(nLow <= nHigh)
//	{
//		//�ҵ��м�λ��
//		nMid = (nLow+nHigh)/2;
//
//		//��С�Ƚ�
//		if(arr[nMid] == nNum)
//		{
//			return nMid;
//		}
//
//		//���м�ֵС  ȥ�����������
//		else if(arr[nMid] > nNum )
//		{
//			nHigh = nMid-1;
//		}
//
//		//���м�ֵ��  ȥ���������
//		else
//		{
//			nLow = nMid+1;
//		}
//	}
//
//	//����ʧ��
//	return -1;
//}
//
//int main()
//{
//	int arr[] = {1,3,4,5,6,12,25,36,47,59};
//	int nIndex = BinaryChop(arr,sizeof(arr)/sizeof(arr[0]),470);
//	printf("%d\n",nIndex);
//	return 0;
//}