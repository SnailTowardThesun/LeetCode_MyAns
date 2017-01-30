/*
 Given a linked list, determine if it has a cycle in it.
 Follow up:
 Can you solve it without using extra space?
 */
#include <iostream>
using namespace std;

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
        ListNode* fast = head;
        ListNode* slow = head;

        if(head == NULL)
            return false;

        if(head->next == NULL)
            return false;

        while(fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;

            if(slow == fast)
                return true;
        }

        return false;
	}
};
