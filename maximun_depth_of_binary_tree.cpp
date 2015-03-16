/*
 Given a binary tree,find its maximum depth
 The maximum depth is the number of nodes along th longest path from the root node down to the farthest leaf node.
 */

struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x) : val(x),left(NULL),right(NULL){}
};

class solution
{
public:
	int maxDepth(TreeNode* root)
	{
		if(root == NULL) return 0;
		return max(maxDepth(root->left), maxDepth(root->right)) + 1;
	}
};
