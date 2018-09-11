//g++ -std=c++11 
#include<iostream>
using namespace std;
struct ListNode 
{
	int val;
	struct ListNode *next;
	ListNode(int x) :
		val(x), next(NULL) 
	{
	}
};
void ListAdd( ListNode **pHead,int nValue)
{
	ListNode* temp=new ListNode(nValue);
	//	temp->val=nValue;
	//	temp->next=NULL;
	if(*pHead==NULL)
	{
		*pHead=temp;
	}
	else
	{	
		ListNode * pTail  = *pHead;
		while(pTail->next!=NULL)
		{
			pTail=pTail->next;
		}
		pTail->next=temp;
	}
}
void ViewList(ListNode* pHead)
{	
	if(pHead==NULL)
	{
		return ;
	}
	while(pHead!=NULL)
	{
		cout<<pHead->val<<endl;
		pHead=pHead->next;
	}
	return ;
}
class Solution 
{
	public:
		ListNode* FindKthToTail(ListNode* pListHead, unsigned int k) 
		{
			ListNode* index1=pListHead;
			ListNode* index2=pListHead;
			for(int i=1;i<k;i++)
			{
				index1=index1->next;
				if(index1->next==NULL)
				{
					return NULL;
				}
			}
			while(index1->next!=NULL)
			{
				index1=index1->next;
				index2=index2->next;
			}
			return index2;
		}
};
int main()
{
	ListNode *pHead=NULL;
	for(int i=0;i<4;i++)
	{
		ListAdd(&pHead,i);
	}
	ViewList(pHead);
	Solution so;
	ListNode * temp;
	temp=so.FindKthToTail(pHead,2);
	cout<<"last 2 is:"<<temp->val<<endl;
	return 0;
}


