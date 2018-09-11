#include<stdio.h>
int main()
{
	int arr[2][3]={11,12,21,22,31,31};
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<3;++j)
		{
			printf("%d ",arr[i][j]);
		}
	}
	return 0;
}
