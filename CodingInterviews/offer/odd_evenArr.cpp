#include<iostream>
using namespace std;
void printArr(int arr[],int len)
{
	for(int i=0;i<len;i++)
	{
		cout<<arr[i]<<" ";
	}
	cout<<endl;
}
void swap(int &a,int &b)
{
	if(a==b)
	{
		return ;
	}
	a=a^b;
	b=a^b;
	a=a^b;
}
int main()
{
int arr[] = {1,2,3,4,5,6,7};
int len = sizeof(arr)/sizeof(int);
printArr(arr,len);
int odd=0;
int even=len-1;
while(odd < even)
{
	while(odd < even && arr[odd]%2 == 1)
	{	
		odd++;
	}
	while(odd < even && arr[even]%2 == 0)
	{	
		even--;
	}
	swap(arr[odd],arr[even]);
}

printArr(arr,len);
return 0;
}
