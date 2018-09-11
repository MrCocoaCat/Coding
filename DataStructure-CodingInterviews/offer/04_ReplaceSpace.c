#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void replaceSpace(char *str,int length) 
{
	if(str==NULL)
	{
		return ;
	}
	int oldLen=0; //记录字符串的实际长度
	int NumSpace=0;
	int i=0;
	while(str[i]!='\0')
	{

		oldLen++; 
		if(str[i]==' ')
		{
			NumSpace++;
		}
		i++;//移动字符串
	}

	int newLen = oldLen+2*NumSpace;
	if(newLen>length)
	{
		return;
	}
	int indexNew=newLen;
	int indexOld=oldLen;
	while(indexOld>=0&&indexNew>indexOld)
	{

		if(str[indexOld]==' ')
		{
			str[indexNew--]='0';
			str[indexNew--]='2';
			str[indexNew--]='%';
		}
		else
		{
			str[indexNew--]=str[indexOld];
		}

		indexOld--;
	}

}
int main(int argc,char * argv[])
{
	char * str=(char *)malloc(50*sizeof(char));
//	char* str2="we are happy";
	char * str2=(char *)argv[1];
	strcpy(str,str2);
	printf("%s\n",str);
	replaceSpace(str,50);
	printf("%s\n",str);



}
