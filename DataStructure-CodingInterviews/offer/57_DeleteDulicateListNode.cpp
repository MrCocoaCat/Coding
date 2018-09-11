#include<iostream>
using namespace std;
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {
    }
};

class Solution {
public:
    ListNode* deleteDuplication(ListNode* pHead)
    {
		if( pHead == NULL)
		{
			return NULL;
		}
		//添加一个新头，并插入到链表中
		ListNode* NewHead = new  ListNode(-1);
		NewHead ->next = pHead;
		
		ListNode* pre = NewHead;
		ListNode* pNode = pHead;
		ListNode* pNext = NULL;
		while(pNode != NULL && pNode->next !=NULL)//节点的下一个也不为NULL 的时候往下移
		{
			pNext = pNode->next;//为当前节点的额下个节点赋值
			if( pNext->val == pNode->val)
			{
				while(  pNext!= NULL  && pNext->val == pNode->val)//如果当前节点的值 和下一个节点的值相等
				{
					pNext = pNext->next; //当前节点保持不变，下一个节点依次移动
				}
				pre->next = pNext; //c重复的节点都删掉了，一个都不留
				pNode = pNext;
			}
			else
			{
				//如果当前节点和下一个节点值不等，则向后移动一位
				pre = pNode;
				pNode = pNode->next;
			}
		}
		return NewHead->next;
		
    }
};  
int main()
{
	ListNode* pHead = new  ListNode(1);
	ListNode* ptail = NULL;
	ListNode* NewHead = new  ListNode(1);
	pHead->next = NewHead;
	ptail = NewHead;
	NewHead = new  ListNode(2);
	ptail->next = NewHead;
    ptail = NewHead;
	NewHead = new  ListNode(2);
	ptail->next = NewHead;
    ptail = NewHead;
	NewHead = new  ListNode(3);
	ptail->next = NewHead;
    ptail = NewHead;
	Solution so;
	ListNode* pretHead =so.deleteDuplication(pHead);



}