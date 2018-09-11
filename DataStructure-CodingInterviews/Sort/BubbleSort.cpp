#include<iostream>

void swap(int &a,int &b)
{
a = a ^ b;
b = a ^ b;
a = a ^ b;
}
void BubbleSort(int arr[],int len)
{
	int i,j;
	int flag=0;
	for(i=0;i<len;i++)
	{
		flag=0;
		//compare from this to end 
		for(j=0;j<len-i-1;j++)
		{
			if(arr[j]>arr[j+1])
			{
				swap(arr[j],arr[j+1]);
			}
			flag=j+1;
		}
		//no swap ,it`s in order
		if(flag==0)
		{
			break;
		}
		else	
		{
			//munite the cycle;
			i=len-flag-1;
		}
	}
}
int main()
{
	int arr[] = {1,3,5,7,9,2,4,6,8};
	BubbleSort(arr,sizeof(arr)/sizeof(int)-1);
	for(int i=0; i < sizeof(arr)/sizeof(int); i++)
	{
		std::cout<<" "<<arr[i];
	}
	return 0;
}