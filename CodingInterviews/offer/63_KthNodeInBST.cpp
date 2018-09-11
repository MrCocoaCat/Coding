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
    TreeNode* KthNode(TreeNode* pRoot, int k)
    {
		if(pRoot == NULL || k <= 0)
		{
			return NULL;
		}
        vector<TreeNode*> ve;
		InOrderTraversal(pRoot,ve);
		if(ve.size() < k)
		{
			return NULL;
		}
		return ve[k-1];
		
    };
	
    void InOrderTraversal(TreeNode* pRoot,vector<TreeNode*> &ve)
	{
		if( pRoot ==NULL)
		{
			return ;
		}
		 InOrderTraversal(pRoot->left,ve);
		 ve.push_back(pRoot);
		 InOrderTraversal(pRoot->right,ve);
	};
    
};







TreeNode KthNode(TreeNode pRoot, int k)
 {
       //int total = getNumOfNode(pRoot);
        if (pRoot == null || k <= 0 )
		{
			 return null;
		}
                   
        int i = 1;
        Stack<TreeNode> stack = new Stack<TreeNode>();
        TreeNode p = pRoot;
        while (p != null || !stack.isEmpty())
        {
           while (p != null)
           {
              stack.push(p);
              p = p.left;
           }
           p = stack.pop();

           if (i++ ==k)
			{
				return p;
			}               
            p = p.right;
        }
        return null;
}






