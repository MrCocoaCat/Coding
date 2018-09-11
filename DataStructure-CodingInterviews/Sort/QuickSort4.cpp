#include<iostream>
#include <time.h>  
using namespace std;
void swap( int &a ,int &b)
{
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}
int helpsort(int arr[],int be,int end)
{
	/****************************
	//优化1： 产生随机数
	srand((unsigned)time(NULL));  
	int Pivot = (rand() % (end-be+1))+ be; //产生随机数
	if(Pivot != end)
	{
		swap(arr[Pivot], arr[end]); //和最后一位做交换
	}
	****************************/
	int  sIndex = be -1;
	for( ;be < end ;be++ )
	{
		if( arr[be] < arr[end])
		{
			sIndex ++;
			if( sIndex != be )
			{
				swap(arr[sIndex], arr[be] );
			}
		}
	}
	sIndex ++;
	if( sIndex != end )
	{
		swap(arr[sIndex], arr[end] );
	}
	return sIndex;
}






int helpsort2(int arr[],int nLow,int nHigh)
{
	/****************************
	//优化1： 产生随机数
	srand((unsigned)time(NULL));  
	int Pivot = (rand() % (end-be+1))+ be; //产生随机数
	if(Pivot != end)
	{
		swap(arr[Pivot], arr[end]); //和最后一位做交换
	}
	****************************/
	int temp;
	temp = arr[nLow];
	while(nLow < nHigh)
	{
		//从后向前找比标准值小的
		while(nLow < nHigh)
		{
			if(arr[nHigh] < temp) //找到的值赋值给别人
			{
				arr[nLow] = arr[nHigh];
				nLow++;
				break;
			}
			else
			{
				nHigh--;
			}
		}

		//从前向后找比标准值大的
		while(nLow < nHigh)
		{
			if(arr[nLow] > temp)
			{
				arr[nHigh] = arr[nLow];
				nHigh--;
				break;
			}
			else
			{
				nLow++;
			}
		}
	}

	//标准值放到对应位置
	arr[nLow] = temp;
	return nLow;
}
void quitsort(int arr[],int be,int end)
{
	if(arr == NULL || be >=  end)
	{
		return ;
	}
	int stand = helpsort(arr,be,end);
	quitsort(arr,be,stand - 1);
	quitsort(arr,stand + 1,end);
}
int main()
{
	int arr[] = {1,3,5,7,9,2,4,6,8};
	quitsort(arr,0,sizeof(arr)/sizeof(int)-1);
	for(int i=0; i < sizeof(arr)/sizeof(int); i++)
	{
		cout<<" "<<arr[i];
	}
	system("pause");
	return 0;
}