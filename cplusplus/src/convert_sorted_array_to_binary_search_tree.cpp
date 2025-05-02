/*
 Given an array where elements are sorted in ascending order, convert it to a height balanced BST.
 */
#include <iostream>
#include <vector>
using namespace std;

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
	TreeNode* sortedArrayToBST(vector<int> &num)
	{
		TreeNode* root = NULL;
		GetResult(num,0,num.size()-1,root);
		return root;
	}
	void GetResult(vector<int> &num,int left,int right,TreeNode* &root)
	{
		if(left > right) return;
		int mid = (left + right) /2;
		root = new TreeNode(num[mid]);
		GetResult(num,left,mid-1,root->left);
		GetResult(num,mid+1,right,root->right);
	}
};
