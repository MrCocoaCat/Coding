#include<stdio.h>
#include<stdlib.h>
int BinaryChop(int arr[],int len,int FindNum)
{
	if(arr==NULL||len<0)
	{
		return -1;
	}
	int nLow=0;
	int nHigh=len-1;
	int nMid;
	while(nLow<=nHigh)
	{
		nMid=(nHigh+nLow)/2;
		if(arr[nMid]==FindNum)
		{
			return nMid;
		}
		else if(arr[nMid]<FindNum)
		{
			nLow=nMid+1;
		}
		else
		{
			nHigh=nMid-1;
		}

	}
	return -1;
}

int main(int argc,char * argv[])
{
	int arr[]={1,2,3,4,5,6,7,8,9};
	int FindNum=atoi(argv[1]);
	int temp;
	temp=BinaryChop(arr,sizeof(arr)/sizeof(arr[0]),FindNum);
	if(temp==-1)
	{
		printf("Error\n");
	}
	else
	{
		printf("Index :%d\n",temp);
	}
	return 0;
}
