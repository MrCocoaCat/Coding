
#include<iostream>  
#include<malloc.h>  
  
typedef struct ListNode{  
    int value;  
    ListNode* next;  
}ListNode;  
  

/************************翻转****************************/
void Inversion(ListNode* Head)  
{  
    ListNode *current,*tmp;  
    current=Head->next;  

    if(current!=NULL)//反转后第一个节点的后继要为NULL  
    {  
        tmp=current;  
        current=current->next;    
        tmp->next=NULL;  
    }  
      
    while(current!=NULL)  
    {  
        tmp=current;  
        current=current->next;  
        tmp->next=Head->next;  
        Head->next=tmp;  
    }  

}  

/************************递归实现****************************/
void Inversion_Recursion(ListNode* p,ListNode* &Head)  
{  
    if(NULL == p)  
    {  
        return;  
    }  
    if(p->next==NULL)   //这是指向最后一个节点，让这个节点为头节点的下一个
    {  
        Head=p;  
        return;//找到最后一个节点  
    }  


    Inversion_Recursion(p->next,Head);   //这是个移位的过程，移位到最后一个节点，return

	// 下一个节点 为p->next 下一个节点，下一个节点的指向即为本省，实现翻转

    p->next->next = p;//反转节点  
    p->next=NULL;//第一个节点反转后其后继应该为NULL  


}  

/************************不开辟中间变量实现****************************/
ListNode *ReverseList(ListNode * pHead)
{
	ListNode *p1 = NULL;
	ListNode *p2 = NULL;
	ListNode *p3 = NULL; //标记被断开位置

	if(pHead == NULL)return NULL;

	p1 = NULL;
	p2 = pHead;
	p3 = pHead->next;

	while(p3 != NULL)
	{
		//对中间节点重新更改指向
		p2->next = p1;

		//排列顺序救赎p1 p2 p3,这是个整体向后移动的过程
		p1 = p2;
		p2 = p3;
		p3 = p3->next;
	}
	//退出循环是，p2 就是最后一个节点，也就是头结点
	p2->next = p1;
	return p2;
}


int main()  
{   
    ListNode* Head=(ListNode*)malloc(sizeof(ListNode));   //头节点无值，就是一个节点标记

    if(Head==NULL)  
        std::cout<<"malloc failed"<<std::endl;  
    ListNode* tmp=Head;  
	Head->value = 0;
    for(int i=1;i<=3;i++)  
    {  
        //tmp->next = (ListNode*)malloc(sizeof(ListNode));  
		tmp->next = new ListNode;  
        tmp->next->value = i;  
        tmp->next->next = NULL;  
        tmp = tmp->next;  //移位
    }  
   Inversion_Recursion(Head,Head  );  
	//Head =  ReverseList(Head);
    //Inversion(Head);  


	//打印链表
	tmp = Head;  
    while(1)
	{  
        std::cout<< tmp->value <<std::endl;  
        if(tmp->next==NULL)  
            break;  
        tmp = tmp->next;  
    }  
	system("pause");
}