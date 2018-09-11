#include<stdio.h>
void swap(int *first,int *last)
{
	//int * temp;
	*first = *last ^ *first;
	*last = *last ^ *first;
	*first = *last ^ *first;
	
}
int* Sort(int *first,int *last,int pivot)
{
	while(1)
	{

		while(*first < pivot)
		{
			first++;
		}
		--last;
		while(pivot < *last)
		{
			--last;
		}
		if( first >= last)
		{
			return first;
		}
		swap(first,last);
		++first;

	}
}
void QuickSort(int *nLow,int *nHigh)
{
	if(nLow == nHigh)
	{
		return ;
	}
	int *standard=Sort(nLow,nHigh,*nLow);
	QuickSort(nLow,standard-1);
	QuickSort(standard+1,nHigh);
}
int main(int argc,char * argv[])
{

	int arr[] = {10,3,16,7,29,19,8,57,12,130,120};
	int i;
	//	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	//	{
	//		printf("%d  ",arr[i]);
	//	}
	//	printf("\n");
	QuickSort(&arr[0],&arr[sizeof(arr)/sizeof(arr[0])-1]);
	for(i = 0;i<sizeof(arr)/sizeof(arr[0]);i++)
	{
		printf("%d  ",arr[i]);
	}
	printf("\n");
	//QuickSort(arr,0,sizeof(arr)/sizeof(arr[0])-1);
	return 0;
}

