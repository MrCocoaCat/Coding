#include<stdio.h>
#include<stdlib.h>
int Numberof1(int nValue)
{
	int nNumber=0;
	while(nValue!=0)
	{
		nValue=nValue&(nValue-1);
		nNumber++;
	}

	return nNumber;

}
int main(int agrc,char * argv[])
{
	int nValue=atoi(argv[1]);
	printf("%d\n",Numberof1(nValue));


}
