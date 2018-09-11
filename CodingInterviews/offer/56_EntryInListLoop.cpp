#include<iostream>
struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :val(x), next(NULL)
	{
		
    }
};

class Solution 
{
public:
    ListNode* MeetingNode(ListNode * pHead) //找到快慢指针相遇的节点，返回其指针
	{
		if(pHead == NULL )
		{
			return NULL;
		}
		ListNode * pSlow = pHead->next;
		if(pSlow == NULL)
		{
			return NULL;
		}
		ListNode * pFast = pSlow->next;
		while(pFast != NULL && pSlow != NULL )
		{
			if( pFast == pSlow)
			{
				return pFast;
			}
			//慢节点走一步
			pSlow = pSlow->next;
			
			//快结点走两步
			pFast = pFast->next;
			if( pFast != NULL)
			{
				pFast = pFast->next;
			}
		}
		return NULL;
	}

	
    ListNode* EntryNodeOfLoop(ListNode* pHead)
    {
		
		ListNode *meetingNode=MeetingNode(pHead);
		if(meetingNode == NULL)
		{
			return NULL;
		}
		ListNode *TempNode = meetingNode;
		int LoopNum = 1; //用于记录环的大小
		while(meetingNode != TempNode->next )//与下一个比较，否则根本无法进入环
		{
			TempNode = TempNode ->next;
			LoopNum++;
		}
		
		ListNode *pNode1 = pHead;
		ListNode *pNode2 = pHead;
		//指针1 先走环那么大小
		for(int i=0;i<LoopNum;i++)
		{
			pNode1 = pNode1->next;
		}
		//指针1 和指针2 同时开始走
		while(pNode1 != pNode2)
		{
			pNode1 = pNode1->next;
			pNode2 = pNode2->next;
		}
		return pNode1;
		
    }
};