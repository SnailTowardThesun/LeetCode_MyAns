/*
Merge k sorted linked lists and return it as one sorted list. Analyze and describe its complexity.
*/

/**
* Definition for singly-linked list.
* struct ListNode {
*     int val;
*     ListNode *next;
*     ListNode(int x) : val(x), next(NULL) {}
* };
*/
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}

};
class Solution {
public:
	ListNode * mergeKLists(vector<ListNode*>& lists) {
		int count = lists.size();
		if (count == 0) {
			return nullptr;
		}

		ListNode node(0), *res = &node;
		auto cmp = [](const ListNode *a, const ListNode *b) { return a->val > b->val; };
		std::priority_queue<ListNode*, vector<ListNode*>, decltype(cmp)> que(cmp);

		for (int i = 0; i < count; i++) {
			if (lists[i]) {
				que.push(lists[i]);
			}
		}

		while (!que.empty())
		{
			ListNode * p = que.top();
			que.pop();
			res->next = p;
			res = p;

			if (p->next) {
				que.push(p->next);
			}
		}
		return node.next;
	}
};