/*
   Given a linked list,remove the Nth node from the end of list and return list head
   For example
		Given linked list: 1->2->3->4->5 ,and n = 2
		After removing the second node from the end, the linked list becomes 1->2->3->5
 */
#include <iostream>
using namespace std;
struct ListNode
{
    int val;
    ListNode* next;
};
class Solution{
public:
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		if(head == NULL) return head;
		ListNode* pr = head;
        ListNode* pe = head;
		for(int i = 0; i <=n; i++)
		{
			if(!pe) return head->next;
			pe = pe->next;
		}
		while(pe != NULL)
		{
			pe = pe->next;
			pr = pr->next;
		}
		pr->next = pr->next->next;
		return head;
	}
};
