/*
 Give two binary trees,write a function to check if they are equal or not
 Two binary trees are considered euqal if they arestructurally identiccal and the nodes hanve the same value.
 */
struct TreeNode
{
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x):val(x),left(NULL),right(NULL){}
};

class solution
{
public:
	bool isSameTree(TreeNode* p, TreeNode* q)
	{
		if(p == NULL || q == NULL)
			return p == q ? true:false;
		return p->val == q->val 
			? isSameTree(p->left,q->left) && isSameTree(p->right,q->right)
			: false;
	}
};
