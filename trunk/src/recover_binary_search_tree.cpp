/*
 Two elements of a binary search tree(BST) are swapped by mistake.
 Recover the tree without changing its structure.
Note:
A solution using O(n) space is pretty straight forward. Could you devise a constant space solution?
 */
#include <iostream>
using namespace std;
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode(int x): val(x),left(NULL),right(NULL){}
};

class solution
{
public:
    void findTwoNodes(TreeNode *root, TreeNode *&n1, TreeNode *&n2, TreeNode *&prev)
    {
        if(root==NULL) return;

        findTwoNodes(root->left,n1,n2,prev);
        if(prev!=NULL && prev->val > root->val)
        {
            n2=root;
            if(n1==NULL)
            {
                n1=prev;
            }
        }
        prev=root;
        findTwoNodes(root->right,n1,n2,prev);
    }
    void recoverTree(TreeNode* root)
	{
        TreeNode *n1=NULL;
        TreeNode *n2=NULL;
        TreeNode *prev=NULL;
        findTwoNodes(root,n1,n2,prev);

        if(n1!=NULL && n2!=NULL)
        {
            int tmp=n2->val;
            n2->val=n1->val;
            n1->val=tmp;
        }
    }

};
