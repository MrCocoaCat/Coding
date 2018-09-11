//#include<stdio.h>
//#include<stdlib.h>
//#include<string.h>
//
//int *GetNext(char *match)
//{
//	int *pNext = NULL;
//	int i;
//	int j;
//	pNext = (int *)malloc(sizeof(int)*strlen(match));
//
//	pNext[0] = 0;
//	i = 1;
//	j = i-1;
//	while(i < strlen(match))
//	{
//		//和前一个next值对应的位置相同  
//		if(match[i] == match[pNext[j]])
//		{
//			pNext[i] = pNext[j] + 1;
//			i++;
//			j = i-1;
//		}
//		//不满足前一个的情况 且 前一个next值为0
//		else if(pNext[j] == 0)
//		{
//			pNext[i] = 0;
//			i++;
//			j = i-1;
//		}
//
//		//以上均不满足 向前跳转
//		else
//		{
//			j = pNext[j] - 1;
//		}
//	}
//	return pNext;
//}
//
//int KMP(char *str,char *match)
//{
//	int *pNext = NULL;
//	int i,j;
//	if(str == NULL || match == NULL)return -1;
//
//	//获得Next数组
//	pNext = GetNext(match);
//
//	//查找
//	i = 0;
//	j = 0;
//
//	while(i < strlen(str)&& j<strlen(match))
//	{
//		//相等 顺次向后移动
//		if(str[i] == match[j])
//		{
//			i++;
//			j++;
//		}
//		else
//		{
//			//不相等 且 匹配串已经在开始位置
//			if(j == 0)
//			{
//				i++;
//			}
//
//			//向前跳转
//			else
//			{
//				j = pNext[j-1];
//			}
//		}
//	}
//
//	//匹配成功
//	if(j == strlen(match))
//	{
//		return i-j;
//	}
//	//匹配失败
//	return -1;
//}
//
//int main()
//{
//	char *str = "ashdihsuadhaewuabcabcdabcabcfsjfoisfsoieue";
//	char *match = "abcabcardhesroieyrdabcabcf";
//	int i = KMP(str,match);
//	printf("%d\n",i);
//	return 0;
//}