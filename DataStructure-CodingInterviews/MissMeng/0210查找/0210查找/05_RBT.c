//#include<stdio.h>
//#include<stdlib.h>
//
//typedef struct node
//{
//	int nValue;
//	int nColor;
//	struct node *pLeft;
//	struct node *pRight;
//	struct node *pFather;
//}RBT;
//
//enum COLOR{RED,BLACK};
//
//RBT *pRBT = NULL;
//
//void RightRotate(RBT **pTree)
//{
//	RBT *pNode = NULL ;//支点
//	RBT *pMark = NULL;
//	if(pTree == NULL || *pTree == NULL)return;
//
//	pNode = *pTree;
//	pMark = pNode->pLeft; //右旋 标记支点左侧
//
//	//三个孩子关系
//	pNode->pLeft = pMark->pRight;
//	pMark->pRight = pNode;
//
//	//支点父亲存在
//	if(pNode->pFather != NULL)
//	{
//		if(pNode == pNode->pFather->pLeft)
//		{
//			pNode->pFather->pLeft = pMark;
//		}
//		else
//		{
//			pNode->pFather->pRight = pMark;
//		}
//	}
//	else
//	{
//		pRBT = pMark;
//	}
//
//	//三个父亲关系
//	if(pNode->pLeft != NULL)
//	{
//		pNode->pLeft->pFather = pNode;
//	}
//
//	pMark->pFather = pNode->pFather;
//	if(pMark->pFather == NULL)
//	{
//		*pTree = pMark;
//	}
//
//	pNode->pFather = pMark;
//
//}
//
//void LeftRotate(RBT **pTree)
//{
//	RBT *pNode = NULL ;//支点
//	RBT *pMark = NULL;
//	if(pTree == NULL || *pTree == NULL)return;
//
//	pNode = *pTree;
//	pMark = pNode->pRight; //左旋 标记支点右侧
//
//	//三个孩子关系
//	pNode->pRight = pMark->pLeft;
//	pMark->pLeft = pNode;
//
//	//支点父亲存在
//	if(pNode->pFather != NULL)
//	{
//		if(pNode == pNode->pFather->pLeft)
//		{
//			pNode->pFather->pLeft = pMark;
//		}
//		else
//		{
//			pNode->pFather->pRight = pMark;
//		}
//	}
//	else
//	{
//		pRBT = pMark;
//	}
//
//	//三个父亲关系
//	if(pNode->pRight != NULL)
//	{
//		pNode->pRight->pFather = pNode;
//	}
//
//	pMark->pFather = pNode->pFather;
//	if(pMark->pFather == NULL)
//	{
//		*pTree = pMark;
//	}
//
//	pNode->pFather = pMark;
//
//}
//
//RBT *FindNode(RBT *pRBT,int nNum)
//{
//	if(pRBT == NULL)return NULL;
//
//	while(pRBT != NULL)
//	{
//		if(nNum > pRBT->nValue)
//		{
//			if(pRBT->pRight == NULL)
//			{
//				return pRBT;
//			}
//			pRBT = pRBT->pRight;
//		}
//		else if(nNum < pRBT->nValue)
//		{
//			if(pRBT->pLeft == NULL)
//			{
//				return pRBT;
//			}
//			pRBT = pRBT->pLeft;
//		}
//		else
//		{
//			abort();
//			printf("数据有误！！！\n");
//			return NULL;
//		}
//	}
//	return NULL;
//}
//
//RBT *GetUncle(RBT *pNode)
//{
//	if(pNode == pNode->pFather->pLeft)
//	{
//		return pNode->pFather->pRight;
//	}
//	else
//	{
//		return pNode->pFather->pLeft;
//	}
//}
//
//void InsertNode(int nNum)
//{
//	RBT *pNode = NULL;
//	RBT *pTemp = NULL;
//	RBT *pUncle = NULL;
//	RBT *pGrandFather = NULL;
//
//	//查找
//	pNode = FindNode(pRBT,nNum);
//
//	pTemp = (RBT*)malloc(sizeof(RBT));
//	pTemp->nColor = RED;
//	pTemp->nValue = nNum;
//	pTemp->pLeft = NULL;
//	pTemp->pRight = NULL;
//	pTemp->pFather = NULL;
//
//	//分析被插入位置的情况
//	//空树
//	if(pNode == NULL)
//	{
//		pRBT = pTemp;
//		pRBT->nColor = BLACK;
//		return;
//	}
//	
//	//当前节点放入树中
//	if(nNum < pNode->nValue)
//	{
//		pNode->pLeft = pTemp;
//	}
//	else
//	{
//		pNode->pRight = pTemp;
//	}
//	pTemp->pFather = pNode;
//
//
//	//父亲是黑的
//	if(pNode->nColor == BLACK)
//	{
//		return;
//	}
//
//	
//	//父亲是红的
//	if(pNode->nColor == RED)
//	{
//		while(1)
//		{
//			pGrandFather = pNode->pFather;
//			if(pGrandFather == NULL)
//			{
//				pRBT->nColor = BLACK;
//				break;
//			}
//			pUncle = GetUncle(pNode);
//
//			//叔叔是红的
//			if(pUncle != NULL && pUncle->nColor == RED)
//			{
//				pUncle->nColor = BLACK;
//				pNode->nColor = BLACK;
//				pGrandFather->nColor = RED;
//				pTemp = pGrandFather;
//				pNode = pTemp->pFather;
//
//				if(pNode == NULL)
//				{
//					pRBT->nColor = BLACK;
//					break;
//				}
//				continue;
//			}
//
//			//叔叔是黑的
//			if(pUncle  == NULL || pUncle->nColor == BLACK)
//			{
//				//父亲是爷爷的左
//				if(pNode == pGrandFather->pLeft)
//				{
//					//当前节点是父亲的右
//					if(pTemp == pNode->pRight)
//					{
//						pTemp = pNode;
//						LeftRotate(&pTemp);
//
//						//更新父亲
//						pNode = pTemp->pFather;
//						continue;
//					}
//					
//					//当前节点是父亲的左
//					if(pTemp == pNode->pLeft)
//					{
//						pNode->nColor = BLACK;
//						pGrandFather->nColor = RED;
//						RightRotate(&pGrandFather);
//						break;
//					}
//				}
//
//				//父亲是爷爷的右
//				if(pNode == pGrandFather->pRight)
//				{
//					// 当前节点是父亲的左
//					if(pTemp == pNode->pLeft)
//					{
//						pTemp = pNode;
//						RightRotate(&pTemp);
//						pNode = pTemp->pFather;
//						continue;
//					}
//
//					//当前节点是父亲的右
//					if(pTemp == pNode->pRight)
//					{
//						pNode->nColor = BLACK;
//						pGrandFather->nColor = RED;
//						LeftRotate(&pGrandFather);
//						break;
//					}
//				}
//			}
//		}
//	}
//}
//
//RBT *FindValue(RBT *pRBT,int nNum)
//{
//	while(pRBT)
//	{
//		if(pRBT->nValue == nNum)
//		{
//			return pRBT;
//		}
//		else if(pRBT->nValue > nNum)
//		{
//			pRBT = pRBT->pLeft;
//		}
//		else
//		{
//			pRBT = pRBT->pRight;
//		}
//	}
//	return NULL;
//}
//
//RBT *GetBrother(RBT *pNode)
//{
//	if(pNode == pNode->pFather->pLeft)
//	{
//		return pNode->pFather->pRight;
//	}
//	else
//	{
//		return pNode->pFather->pLeft;
//	}
//}
//
//void DelNode(int nNum)
//{
//	RBT *pNode = NULL;
//	RBT *pMark = NULL;
//	RBT *pBrother = NULL;
//	RBT *pFather = NULL;
//
//	//查找被删除位置
//	pNode = FindValue(pRBT,nNum);
//
//	if(pNode == NULL)return;
//
//	//两个孩子
//	if(pNode->pLeft != NULL && pNode->pRight != NULL)
//	{
//		pMark = pNode;
//		pNode = pNode->pRight;
//
//		while(pNode->pLeft)
//		{
//			pNode  = pNode->pLeft;
//		}
//		pMark->nValue = pNode->nValue;
//	}
//
//	//1.根节点 
//	if(pNode->pFather == NULL)
//	{
//		//没孩子
//		if(pNode->pLeft == NULL && pNode->pRight == NULL)
//		{
//			pRBT = NULL;
//			free(pNode);
//			pNode = NULL;
//			return;
//		}
//
//		//有一个孩子
//		if(pNode->pLeft != NULL || pNode->pRight != NULL)
//		{
//			pRBT = pNode->pLeft ? pNode->pLeft : pNode->pRight;
//			pRBT->nColor = BLACK;
//			pRBT->pFather = NULL;
//			free(pNode);
//			pNode = NULL;
//			return;
//		}
//	}
//
//	//非根
//	if(pNode->pFather != NULL)
//	{
//		//1.红节点
//		if(pNode->nColor == RED)
//		{
//			if(pNode == pNode->pFather->pLeft)
//			{
//				pNode->pFather->pLeft = NULL;
//			}
//			else
//			{
//				pNode->pFather->pRight = NULL;
//			}
//			free(pNode);
//			pNode = NULL;
//			return;
//		}
//
//		//2.有一个孩子
//		if(pNode->pLeft != NULL || pNode->pRight != NULL)
//		{
//			if(pNode == pNode->pFather->pLeft)
//			{
//				pNode->pFather->pLeft = pNode->pLeft ? pNode->pLeft : pNode->pRight;
//				pNode->pFather->pLeft->nColor = BLACK;
//				pNode->pFather->pLeft->pFather = pNode->pFather;
//			}
//			else
//			{
//				pNode->pFather->pRight = pNode->pLeft ? pNode->pLeft : pNode->pRight;
//				pNode->pFather->pRight->nColor = BLACK;
//				pNode->pFather->pRight->pFather = pNode->pFather;
//			}
//			free(pNode);
//			pNode = NULL;
//			return;
//		}
//
//		//3.黑节点 没有孩子
//
//		pBrother = GetBrother(pNode);
//		pFather = pNode->pFather;
//
//		//假删除
//		if(pNode == pNode->pFather->pLeft)
//		{
//			pNode->pFather->pLeft = NULL;
//		}
//		else
//		{
//			pNode->pFather->pRight = NULL;
//		}
//
//		//标记原始被删除位置
//		pMark = pNode;
//
//		while(1)
//		{
//			//兄弟是红的
//			if(pBrother != NULL && pBrother->nColor == RED)
//			{
//				//当前节点是父亲的左
//				if(pBrother == pFather->pRight)
//				{
//					pFather->nColor = RED;
//					pBrother->nColor = BLACK;
//					LeftRotate(&pFather);
//
//					//更新兄弟
//					pBrother = pFather->pRight;
//					continue;
//				}
//
//				//当前节点是父亲的右
//				if(pBrother == pFather->pLeft)
//				{
//					pFather->nColor = RED;
//					pBrother->nColor = BLACK;
//					RightRotate(&pFather);
//
//					//更新兄弟
//					pBrother = pFather->pLeft;
//					continue;
//				}
//			}
//
//			//兄弟是黑的
//			if(pBrother->nColor == BLACK)
//			{
//				//兄弟的两个孩子都是黑的
//				if((pBrother->pLeft == NULL &&pBrother->pRight == NULL ) ||
//					(pBrother->pLeft != NULL && pBrother->pLeft->nColor == BLACK && 
//					pBrother->pRight != NULL && pBrother->pRight->nColor == BLACK) )
//				{
//					//父亲是红的
//					if(pFather->nColor == RED)
//					{
//						pFather->nColor = BLACK;
//						pBrother->nColor = RED;
//						break;
//					}
//
//					//父亲是黑的
//					if(pFather->nColor == BLACK)
//					{
//						pBrother->nColor = RED;
//
//						pNode = pFather;
//						pFather = pNode->pFather;
//						if(pFather == NULL)
//						{
//							break;
//						}
//						pBrother = GetBrother(pNode);
//						continue;
//					}
//				}
//
//				//左孩子是红的  右孩子是黑的
//				if(pBrother->pLeft != NULL && pBrother->pLeft->nColor == RED &&
//					(pBrother->pRight == NULL || pBrother->pRight->nColor == BLACK))
//				{
//					//当前节点是父亲的左
//					if(pBrother == pFather->pRight)
//					{
//						pBrother->nColor = RED;
//						pBrother->pLeft->nColor = BLACK;
//
//						RightRotate(&pBrother);
//
//						//更新兄弟
//						pBrother = pFather->pRight;
//						continue;
//					}
//
//					//当前节点是父亲的右
//					if(pBrother == pFather->pLeft)
//					{
//						pBrother->nColor = pFather->nColor;
//						pFather->nColor = BLACK;
//						pBrother->pLeft->nColor= BLACK;
//						RightRotate(&pFather);
//						break;
//					}
//				}
//
//				//兄弟的右是红的
//				if(pBrother->pRight != NULL && pBrother->pRight->nColor == RED)
//				{
//					//当前节点是父亲的左
//					if(pBrother == pFather->pRight)
//					{
//						pBrother->nColor = pFather->nColor;
//						pFather->nColor = BLACK;
//						pBrother->pRight->nColor= BLACK;
//						LeftRotate(&pFather);
//						break;
//					}
//
//					//当前节点是父亲的右
//					if(pBrother == pFather->pLeft)
//					{
//						pBrother->nColor = RED;
//						pBrother->pRight->nColor = BLACK;
//
//						LeftRotate(&pBrother);
//
//						//更新兄弟
//						pBrother = pFather->pLeft;
//						continue;
//					}
//				}
//			}
//		}
//	}
//	pRBT->nColor = BLACK;
//
//	free(pMark);
//	pMark = NULL;
//}
//
//void CreateRBT(int arr[],int nLength)
//{
//	int i;
//	if(arr == NULL || nLength <=0)return;
//	for(i = 0;i<nLength;i++)
//	{
//		InsertNode(arr[i]);
//	}
//}
//
//void Traversal(RBT *pRBT)
//{
//	if(pRBT == NULL)return;
//	Traversal(pRBT->pLeft);
//
//	printf("%d\t",pRBT->nValue);
//	printf("%d\n",pRBT->nColor);
//
//	Traversal(pRBT->pRight);
//}
//
//int main()
//{
//	int arr[] = {11,2,14,1,7,15,5,8};
//	CreateRBT(arr,8);
//	//Traversal(pRBT);
//	//InsertNode(4);
//	Traversal(pRBT);
//	DelNode(1);
//	printf("-------------------------------------------------\n");
//	Traversal(pRBT);
//
//	return 0;
//}
