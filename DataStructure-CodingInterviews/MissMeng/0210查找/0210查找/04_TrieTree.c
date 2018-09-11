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
//		//当前字母对应位置没有节点 添加
//		if(pTrie->pCharacter[str[i]-97] == NULL)
//		{
//			pTemp = (TrieTree*)malloc(sizeof(TrieTree));
//			memset(pTemp,0,sizeof(TrieTree));
//
//			pTrie->pCharacter[str[i]-97] = pTemp;
//		}
//
//		//有  向下一层前进 处理下一个字母
//		pTrie = pTrie->pCharacter[str[i] - 97];
//		i++;
//	}
//
//	//末尾标志
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
//	//创建根
//	pTrie = (TrieTree *)malloc(sizeof(TrieTree));
//	memset(pTrie,0,sizeof(TrieTree));
//
//	//向树添加单词
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
//			printf("查找失败！！！\n");
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
//	printf("单词不存在TAT\n");
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