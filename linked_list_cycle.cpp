/*
 Given a linked list, determine if it has a cycle in it.
 Follow up:
 Can you solve it without using extra space?
 */

struct ListNode
{
	int val;
	ListNode *next;
	ListNode(int x):val(x),next(NULL){}
};

class solution
{
public:
	bool hasCycle(ListNode* head)
	{
		ListNode *fast = NULL;
		ListNode *slow = NULL;
		if(head == NULL || head->next == NULL) return false;
		while(false != NULL && false->next != NULL)
		{
			slow = slow->next;
			fast = fast->next->next;
			if(slow == fast) return true;
		}
		return false;
	}
};
