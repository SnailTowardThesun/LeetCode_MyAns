/*
   Given a linked list, swap every two adjacent nodes and return its head.
   For example.
   Given 1->2->3->4,you should return the list as 2->1->4->3
   Youralgorithm should use only constant space.You may not modify the values int the list,only nodes itself can be changed
 */

/*
   definition for singly-list
 */
#include <iostream>
using namespace std;

struct ListNode
{
	int val;
	struct ListNode *next;
};

struct ListNode *swapPairs(struct ListNode *head)
{
    struct  ListNode *cur = NULL, *next = NULL, *tmp = NULL, *pre = NULL;
    cur = head;
    if(cur != NULL && cur->next != NULL)
        head = cur->next;
    while(cur != NULL)
    {
        if(cur->next == NULL)
        {
            return head;
        }
        next = cur->next;
        if(pre != NULL)
            pre->next = next;
        tmp = next->next;
        next->next = cur;
        cur->next = tmp;
        pre = cur;
        cur = cur->next;

    }
    return head;
}
