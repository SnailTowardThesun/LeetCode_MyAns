/*
   You are given two linked lists representing two non-negative numbers.The digits are stored in reverse order ande each of their nodes contain a single digit.Add the two numbers and return it as a linked list
Input: (2 -> 4 -> 3) + (5-> 6 -> 4)
output: 7 -> 0 ->8
 */

/*
 Definition for singly-linked list.
 */
#include <iostream>
using namespace std;

 struct ListNode
 {
	int val;
	ListNode *next;
	ListNode(int x):val(x),next(NULL){}
 };

class Solution
{
public:
	ListNode* addTwoNumbers(ListNode* l1,ListNode* l2)
	{
		if(l1 == NULL || l2 == NULL) return l1==NULL ? l1 : l2;

		ListNode* result = new ListNode(0);
		ListNode* pResult = result;
		ListNode* p1 = l1;
		ListNode* p2 = l2;
		int isBiggerThenTen = 0;
		while(p1 != NULL && p2 != NULL)
		{
			int tmp = 0;
			tmp = p1->val + p2->val + isBiggerThenTen;
			ListNode* tmpNode = new ListNode((tmp)%10);
			pResult->next = tmpNode;
			pResult = pResult->next;
			tmp >= 10 ? isBiggerThenTen = 1 : isBiggerThenTen = 0;
			p1 = p1->next;
			p2 = p2->next;
		}
		while(p1 != NULL || p2 != NULL || isBiggerThenTen != 0)
		{
			int tmp = 0;
			ListNode* tmpNode = NULL;
			if(p1 != NULL || p2 != NULL)
			{
				if(p1 == NULL)
				{
					tmp = p2->val + isBiggerThenTen;
					tmpNode = new ListNode(tmp%10);
					tmp >= 10 ? isBiggerThenTen = 1 : isBiggerThenTen = 0;
					p2 = p2->next;
				}
				else
				{
					tmp = p1->val + isBiggerThenTen;
					tmpNode = new ListNode(tmp%10);
					tmp >= 10 ? isBiggerThenTen = 1 : isBiggerThenTen = 0;
					p1 = p1->next;
				}
			}
			else
			{
				tmpNode = new ListNode(isBiggerThenTen);
				isBiggerThenTen = 0;
			}
			pResult->next = tmpNode;
			pResult = pResult->next;
		}
		return pResult->next;
	}
};
