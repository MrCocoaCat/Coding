//#include<stdio.h>
//
//void InsertSort(int arr[],int nLength)
//{
//	int i; 
//	int j; 
//	int temp;
//	if(arr == NULL || nLength <=0)return;
//
//	//��������
//	for(i = 1;i<nLength;i++)
//	{
//		j = i-1;  //������������һ��
//		temp = arr[i];  //��������ĵ�һ��
//		//������������ �ҵ�����λ��
//		while(arr[j] > temp && j>=0) //��temp ���뵽���������У����temp �ȵ�ǰλС����������ǰ�ң�ͬʱ���������λ��
//			//ֱ���ҵ���С�ġ��ҵ���,��temp ���������С�
//		{
//			arr[j+1] = arr[j];
//			j--;
//		}
//		//���뵽��Ӧλ����
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