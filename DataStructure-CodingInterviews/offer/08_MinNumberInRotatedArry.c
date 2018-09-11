#include<stdio.h>
int MinNumInRotatedArr(int arr[],int len)
{
	if(arr==NULL||len<0)
	{
		return -1;
	}
	int index1=0;
	int index2=len-1;
	while(index2-index1>1)
	{
		if(arr[index1]<arr[index2])
		{
			return arr[index1];
		}
		int Mid=(index1+index2)/2;
		if(arr[Mid]==arr[index1]&&arr[index1]==arr[index2])
		{
			int result=arr[0];
			for(int i=index1;i<index2;i++)
			{
				if(arr[i]<result)
				{
					result=arr[i];
				}
			}
			return result;
		}
		if(arr[Mid]>=arr[index1])
		{
			index1=Mid;
		}
		else if(arr[Mid]<=arr[index2])
		{
			index2=Mid;
		}

	}
	return arr[index2];




}
int main(int argc,char * argv[])
{
	int arr[]={1,0,1,1,1};
	int ret=MinNumInRotatedArr(arr,sizeof(arr)/sizeof(arr[0]));
	printf("%d\n",ret);
	return 0;
}
