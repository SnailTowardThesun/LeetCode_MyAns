/*
 Given a binary tree,find its minimum depth
 The minimum depth is the number of nodes along the shortest path from root node down to the nearest leaf node.
 */

struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x),right(NULL),left(NULL){}
};

class solution
{
public:
	int minDepth(TreeNode *root)
	{
		if(root == NULL) return 0;
		if(root->left == NULL && root->right == NULL) return 1;
		int leftDepth = minDepth(root->left);
		int rightDpeth = minDepth(root->right);
		if(leftDepth == 0)
			return rightDepth + 1;
		else if (rightDepth == 0)
			return leftDepth + 1;
		else 
			return min(leftDepth, rightDepth) + 1;
	}
};
