#include<iostream>
//区间分割法
void swap(int &a,int &b)
{
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}
int Sort(int arr[],int nLow,int nHigh)
{
	int nSmall; //用来标记小区间
	nSmall = nLow - 1;
	for( ; nLow < nHigh; nLow++)
	{
		if(arr[nLow] < arr[nHigh])
		{
			nSmall ++;
			if(nSmall != nLow)
			{
				swap(arr[nSmall],arr[nLow]);
			}
			
		}
	}
	++nSmall;
	if( nSmall != nHigh)
	{
		swap(arr[nSmall],arr[nHigh]);
	}
	return nSmall;
	
}
void QuickSort(int arr[],int nLow,int nHigh)
{
	if(nLow >= nHigh||arr == NULL)
	{
		return ;
	}
	int standard=Sort(arr,nLow,nHigh);
	QuickSort(arr,nLow,standard-1);
	QuickSort(arr,standard+1,nHigh);
}

int main(int argc,char * argv[])
{
	
	int arr[] = {10,3,16,7,29,19,8,57,12,130,120};
	int i;
	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d  ",arr[i]);
	}
	printf("\n");
	QuickSort(arr,0,sizeof(arr)/sizeof(arr[0])-1);
	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d  ",arr[i]);
	}
return 0;
}

