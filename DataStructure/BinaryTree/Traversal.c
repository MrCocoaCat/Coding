#include"lib.h"
void PreOrderTraversal(Node * pRoot)
{
	if(pRoot==NULL)
	{
		return ;
	}
	printf("%d ",pRoot->value);
	PreOrderTraversal(pRoot->pLeft);
	PreOrderTraversal(pRoot->pRight);
}
void InOrderTraversal(Node * pRoot)
{
	if(pRoot==NULL)
	{
		return ;
	}
	InOrderTraversal(pRoot->pLeft);
	printf("%d ",pRoot->value);
	InOrderTraversal(pRoot->pRight);
}
void PostOrderTraversal(Node * pRoot)
{
	if(pRoot==NULL)
	{
		return ;
	}
	PostOrderTraversal(pRoot->pLeft);
	PostOrderTraversal(pRoot->pRight);
	printf("%d ",pRoot->value);
}


//************************************************************
TreeNode KthNode(TreeNode root)
{
        if(root==null||k==0)
            return null;
        Stack<TreeNode> stack = new Stack<TreeNode>();
        int count = 0;
        TreeNode node = root;
        do{
            if(node!=null)
			{
                stack.push(node);
                node = node.left;
            }
			else
			{
                node = stack.pop();
                node = node.right;
            }
        }while(node!=null || !stack.isEmpty());
        return null;
}








