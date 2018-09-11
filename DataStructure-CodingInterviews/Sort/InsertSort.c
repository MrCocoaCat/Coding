#include<stdio.h>
void InsertSort(int arr[],int len)
{
	int SortedEnd;
	int UnsortBe;
	for(UnsortBe = 1; UnsortBe < len ;UnsortBe++)
	{
		 SortedEnd = UnsortBe -1;
		 int temp = arr[UnsortBe];
		while(arr[SortedEnd] >temp &&  SortedEnd >=0)
		{
			arr[SortedEnd + 1] = arr[SortedEnd];
			SortedEnd -- ;
		}	 
		arr[SortedEnd +1] = temp;



	}

	
}

int main(int argc,char * argv[])
{
	int i;
	int arr[]={11,4,7,9,6,14,23,2,8};
	int mun=sizeof(arr)/sizeof(arr[0]);
//	BubbleSort(arr,mun);
	InsertSort(arr,mun);
	for(i=0;i<mun;i++)
	{
		printf("%d    ",arr[i]);
	}
	printf("\n");
	return 0;

}


