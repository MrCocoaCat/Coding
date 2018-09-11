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
//		//��ǰһ��nextֵ��Ӧ��λ����ͬ  
//		if(match[i] == match[pNext[j]])
//		{
//			pNext[i] = pNext[j] + 1;
//			i++;
//			j = i-1;
//		}
//		//������ǰһ������� �� ǰһ��nextֵΪ0
//		else if(pNext[j] == 0)
//		{
//			pNext[i] = 0;
//			i++;
//			j = i-1;
//		}
//
//		//���Ͼ������� ��ǰ��ת
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
//	//���Next����
//	pNext = GetNext(match);
//
//	//����
//	i = 0;
//	j = 0;
//
//	while(i < strlen(str)&& j<strlen(match))
//	{
//		//��� ˳������ƶ�
//		if(str[i] == match[j])
//		{
//			i++;
//			j++;
//		}
//		else
//		{
//			//����� �� ƥ�䴮�Ѿ��ڿ�ʼλ��
//			if(j == 0)
//			{
//				i++;
//			}
//
//			//��ǰ��ת
//			else
//			{
//				j = pNext[j-1];
//			}
//		}
//	}
//
//	//ƥ��ɹ�
//	if(j == strlen(match))
//	{
//		return i-j;
//	}
//	//ƥ��ʧ��
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