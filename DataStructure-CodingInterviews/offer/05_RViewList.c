
void RViewList(struct NODE * pHead)
{
	if(pHead!=NULL)
	{
		if(pHead->pNext!=NULL)
		{
			RViewList(pHead->pNext);
		}
		printf("%d  ",pHead->value);
	}
	return ;
}

