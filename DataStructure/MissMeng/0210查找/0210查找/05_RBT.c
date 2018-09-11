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
//	RBT *pNode = NULL ;//֧��
//	RBT *pMark = NULL;
//	if(pTree == NULL || *pTree == NULL)return;
//
//	pNode = *pTree;
//	pMark = pNode->pLeft; //���� ���֧�����
//
//	//�������ӹ�ϵ
//	pNode->pLeft = pMark->pRight;
//	pMark->pRight = pNode;
//
//	//֧�㸸�״���
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
//	//�������׹�ϵ
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
//	RBT *pNode = NULL ;//֧��
//	RBT *pMark = NULL;
//	if(pTree == NULL || *pTree == NULL)return;
//
//	pNode = *pTree;
//	pMark = pNode->pRight; //���� ���֧���Ҳ�
//
//	//�������ӹ�ϵ
//	pNode->pRight = pMark->pLeft;
//	pMark->pLeft = pNode;
//
//	//֧�㸸�״���
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
//	//�������׹�ϵ
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
//			printf("�������󣡣���\n");
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
//	//����
//	pNode = FindNode(pRBT,nNum);
//
//	pTemp = (RBT*)malloc(sizeof(RBT));
//	pTemp->nColor = RED;
//	pTemp->nValue = nNum;
//	pTemp->pLeft = NULL;
//	pTemp->pRight = NULL;
//	pTemp->pFather = NULL;
//
//	//����������λ�õ����
//	//����
//	if(pNode == NULL)
//	{
//		pRBT = pTemp;
//		pRBT->nColor = BLACK;
//		return;
//	}
//	
//	//��ǰ�ڵ��������
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
//	//�����Ǻڵ�
//	if(pNode->nColor == BLACK)
//	{
//		return;
//	}
//
//	
//	//�����Ǻ��
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
//			//�����Ǻ��
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
//			//�����Ǻڵ�
//			if(pUncle  == NULL || pUncle->nColor == BLACK)
//			{
//				//������үү����
//				if(pNode == pGrandFather->pLeft)
//				{
//					//��ǰ�ڵ��Ǹ��׵���
//					if(pTemp == pNode->pRight)
//					{
//						pTemp = pNode;
//						LeftRotate(&pTemp);
//
//						//���¸���
//						pNode = pTemp->pFather;
//						continue;
//					}
//					
//					//��ǰ�ڵ��Ǹ��׵���
//					if(pTemp == pNode->pLeft)
//					{
//						pNode->nColor = BLACK;
//						pGrandFather->nColor = RED;
//						RightRotate(&pGrandFather);
//						break;
//					}
//				}
//
//				//������үү����
//				if(pNode == pGrandFather->pRight)
//				{
//					// ��ǰ�ڵ��Ǹ��׵���
//					if(pTemp == pNode->pLeft)
//					{
//						pTemp = pNode;
//						RightRotate(&pTemp);
//						pNode = pTemp->pFather;
//						continue;
//					}
//
//					//��ǰ�ڵ��Ǹ��׵���
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
//	//���ұ�ɾ��λ��
//	pNode = FindValue(pRBT,nNum);
//
//	if(pNode == NULL)return;
//
//	//��������
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
//	//1.���ڵ� 
//	if(pNode->pFather == NULL)
//	{
//		//û����
//		if(pNode->pLeft == NULL && pNode->pRight == NULL)
//		{
//			pRBT = NULL;
//			free(pNode);
//			pNode = NULL;
//			return;
//		}
//
//		//��һ������
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
//	//�Ǹ�
//	if(pNode->pFather != NULL)
//	{
//		//1.��ڵ�
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
//		//2.��һ������
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
//		//3.�ڽڵ� û�к���
//
//		pBrother = GetBrother(pNode);
//		pFather = pNode->pFather;
//
//		//��ɾ��
//		if(pNode == pNode->pFather->pLeft)
//		{
//			pNode->pFather->pLeft = NULL;
//		}
//		else
//		{
//			pNode->pFather->pRight = NULL;
//		}
//
//		//���ԭʼ��ɾ��λ��
//		pMark = pNode;
//
//		while(1)
//		{
//			//�ֵ��Ǻ��
//			if(pBrother != NULL && pBrother->nColor == RED)
//			{
//				//��ǰ�ڵ��Ǹ��׵���
//				if(pBrother == pFather->pRight)
//				{
//					pFather->nColor = RED;
//					pBrother->nColor = BLACK;
//					LeftRotate(&pFather);
//
//					//�����ֵ�
//					pBrother = pFather->pRight;
//					continue;
//				}
//
//				//��ǰ�ڵ��Ǹ��׵���
//				if(pBrother == pFather->pLeft)
//				{
//					pFather->nColor = RED;
//					pBrother->nColor = BLACK;
//					RightRotate(&pFather);
//
//					//�����ֵ�
//					pBrother = pFather->pLeft;
//					continue;
//				}
//			}
//
//			//�ֵ��Ǻڵ�
//			if(pBrother->nColor == BLACK)
//			{
//				//�ֵܵ��������Ӷ��Ǻڵ�
//				if((pBrother->pLeft == NULL &&pBrother->pRight == NULL ) ||
//					(pBrother->pLeft != NULL && pBrother->pLeft->nColor == BLACK && 
//					pBrother->pRight != NULL && pBrother->pRight->nColor == BLACK) )
//				{
//					//�����Ǻ��
//					if(pFather->nColor == RED)
//					{
//						pFather->nColor = BLACK;
//						pBrother->nColor = RED;
//						break;
//					}
//
//					//�����Ǻڵ�
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
//				//�����Ǻ��  �Һ����Ǻڵ�
//				if(pBrother->pLeft != NULL && pBrother->pLeft->nColor == RED &&
//					(pBrother->pRight == NULL || pBrother->pRight->nColor == BLACK))
//				{
//					//��ǰ�ڵ��Ǹ��׵���
//					if(pBrother == pFather->pRight)
//					{
//						pBrother->nColor = RED;
//						pBrother->pLeft->nColor = BLACK;
//
//						RightRotate(&pBrother);
//
//						//�����ֵ�
//						pBrother = pFather->pRight;
//						continue;
//					}
//
//					//��ǰ�ڵ��Ǹ��׵���
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
//				//�ֵܵ����Ǻ��
//				if(pBrother->pRight != NULL && pBrother->pRight->nColor == RED)
//				{
//					//��ǰ�ڵ��Ǹ��׵���
//					if(pBrother == pFather->pRight)
//					{
//						pBrother->nColor = pFather->nColor;
//						pFather->nColor = BLACK;
//						pBrother->pRight->nColor= BLACK;
//						LeftRotate(&pFather);
//						break;
//					}
//
//					//��ǰ�ڵ��Ǹ��׵���
//					if(pBrother == pFather->pLeft)
//					{
//						pBrother->nColor = RED;
//						pBrother->pRight->nColor = BLACK;
//
//						LeftRotate(&pBrother);
//
//						//�����ֵ�
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
