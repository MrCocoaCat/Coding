/*
struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
    TreeNode(int x) :
            val(x), left(NULL), right(NULL) {
    }
};
*/

class Solution {
public:
    bool isSame(TreeNode* p1,TreeNode* p2)
    {
        if(p1==NULL && p2!=NULL)return false;
        if(p2==NULL && p1!=NULL)return false; 
		//当二者同时为NULL时，则走完，这是可以判定为true
        if(p1==NULL && p2==NULL)return true; 
 
        if(p1->val == p2->val)
		{
			return isSame(p1->right,p2->left) && isSame(p1->left,p2->right);
		}
        else
		{	
			return false;
		}
            
    }
    bool isSymmetrical(TreeNode* pRoot)
    {
        if(pRoot==NULL)
		{
			return true;     
		}   
        return isSame(pRoot->left,pRoot->right);
    }
 
};