//#include<stdio.h>
//#include<stdlib.h>
//#include<windows.h>
//
//typedef struct node
//{
//	int nFalg;
//	char *str;
//	struct node *pCharacter[26];
//}TrieTree;
//
//void AddWord(char *str,TrieTree *pTrie,char *match)
//{
//	int i;
//	TrieTree *pTemp = NULL;
//	char *str2 = str;
//	i = 0;
//	while(i < strlen(str))
//	{
//		//��ǰ��ĸ��Ӧλ��û�нڵ� ���
//		if(pTrie->pCharacter[str[i]-97] == NULL)
//		{
//			pTemp = (TrieTree*)malloc(sizeof(TrieTree));
//			memset(pTemp,0,sizeof(TrieTree));
//
//			pTrie->pCharacter[str[i]-97] = pTemp;
//		}
//
//		//��  ����һ��ǰ�� ������һ����ĸ
//		pTrie = pTrie->pCharacter[str[i] - 97];
//		i++;
//	}
//
//	//ĩβ��־
//	pTrie->nFalg = 1;
//	pTrie->str = str2;
//}
//
//TrieTree *CreateTrie(char *str[],int nLength,char *match[] )
//{
//	TrieTree *pTrie = NULL;
//	int i;
//
//	if(str == NULL || nLength <= 0|| match == NULL)return NULL;
//
//	//������
//	pTrie = (TrieTree *)malloc(sizeof(TrieTree));
//	memset(pTrie,0,sizeof(TrieTree));
//
//	//������ӵ���
//	for(i = 0;i<nLength;i++)
//	{
//		AddWord(str[i],pTrie,match[i]);
//	}
//
//	return pTrie;
//}
//
//void Traversal(TrieTree *pTrie)
//{
//	int i;
//	if(pTrie == NULL)return;
//
//	if(pTrie->nFalg == 1)
//	{
//		printf("%s\n",pTrie->str);
//	}
//	for(i = 0;i<26;i++)
//	{
//		Traversal(pTrie->pCharacter[i]);
//	}
//
//}
//
//void Search(TrieTree *pTrie,char *str)
//{
//	int i;
//	if(pTrie == NULL || str == NULL)return;
//
//	i= 0;
//	while(i < strlen(str))
//	{
//		if(pTrie->pCharacter[str[i] - 97] == NULL)
//		{
//			printf("����ʧ�ܣ�����\n");
//			return;
//		}
//		pTrie = pTrie->pCharacter[str[i]-97];
//		i++;
//	}
//
//	if(pTrie->nFalg == 1)
//	{
//		printf("%s\n",pTrie->str);
//		return;
//	}
//	printf("���ʲ�����TAT\n");
//}
//
//
//int main()
//{
//	char *str[] = {"color","car","lenovo","apple","google","cat","ap"};
//	char *match[] = {"yanse","che","lianxiang","pingguo","guge","mao","fashi"};
//	TrieTree *pTrie = CreateTrie(str,7,match);
//	//Traversal(pTrie);
//	Search(pTrie,"app");
//	return 0;
//}