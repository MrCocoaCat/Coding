#include<iostream>
using namespace std;
static int Test ;
void printArr(int arr[],int len)
{
	for(int i = 0;i < len ;i++)
	{
		cout<<arr[i]<<" ";

	}
	cout<<endl;
}
void swap(int &a,int &b)
{
	a = a^b;
	b = a^b;
	a = a^b;
}
void bubbleSort0(int arr[],int len )
{
	for(int i = 0;i<len;i++)
	{
		
		for(int j = 0;j<len -1;j++)
		{
			Test++;
			if (arr[j] > arr[j+1] )
			{
				swap(arr[j],arr[j+1]);
			}
		}
	}
}
//每次大循环会将最大的排序，每次小循环依次减小
void bubbleSort1(int arr[],int len )
{
	for(int i = 0;i<len;i++)
	{
		
		for(int j = 0;j<len -i-1;j++)
		{
			Test++;
			if (arr[j] > arr[j+1] )
			{
				swap(arr[j],arr[j+1]);
			}
		}
	}
}
void bubbleSort2(int arr[],int len )
{
	int flag = 0;
	for(int i = 0;i<len;i++) //大循环控制次数，每次循环把大数放到最合适位置，冒泡大数
	{
		int flag = 0;	
		for(int j = 0;j<len-i -1;j++)
		{
			Test++;
			if (arr[j] > arr[j+1] )
			{
				swap(arr[j],arr[j+1]);
				flag = 1;
			}
		
		}
		if( 0 == flag)  //如果一次遍历没有发生交换，那么该数组就是排序的数组，退出循环
		{
			return ;
		}
	}

}
void bubbleSort3(int arr[],int len )
{
	int flag = 0;
	for(int i = 0;i<len;i++) //每次循环将最大的数冒泡到最后
	{
		int flag = 0;
		Test++;
		for(int j = 0;j<len -1-i;j++)
		{
			if (arr[j] > arr[j+1] )
			{
				swap(arr[j],arr[j+1]);
				flag = j + 1;
			}  
		
		}
		if( 0 == flag)  //如果一次遍历没有发生交换，那么该数组就是排序的数组，退出循环
		{
			return ;
		}

		i = len - flag -1;  //控制总循环的次数，可以认为每次大循环确定一个大数，如果大数已经排好序，可以依次减少排序
	}

}
int main()
{
	int arr[] = {11,3,5,7,2,10,4,6,8,9};
	printArr(arr,sizeof(arr)/sizeof(int));
	//bubbleSort1(arr,sizeof(arr)/sizeof(int));
	bubbleSort3(arr,sizeof(arr)/sizeof(int));
	printArr(arr,sizeof(arr)/sizeof(int));
	cout<<Test<<endl;
	system("pause");
	return 0;
}