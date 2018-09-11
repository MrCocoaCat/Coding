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
        void Print(TreeNode* pRoot) 
        {
			if(pRoot == NULL)
			{
				return 
			}
			queue.push(pRoot);
			int LevelNum = 0;
			int PrintFlag = 0;
			while( !queue.empty() )
			{
				TreeNode* pTemp = queue.top;
				cout << pTemp->val;
				
				if( TreeNode->left != NULL)
				{
					queue.push(TreeNode->left);
					LevelNum++;
				}
				if( TreeNode->right != NULL)
				{
					queue.push(TreeNode->right);
					LevelNum++;
				}
				queue.pop();
				PrintFlag --;
				if(PrintFlag == 0)
				{
					PrintFlag = LevelNum;
					LevelNum = 0;
					cout<<endl;
				}
				
				
			}
     }
    
};