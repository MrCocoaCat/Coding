#include<stdio.h>
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
				swap(&arr[j],&arr[j+1]);
				flag=j+1;
			}
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
