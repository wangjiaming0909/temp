#include "leetcode.h"
#include "../timer.h"


namespace al
{

class SwapPairs : public ILeetCode
{
public:

	ListNode* swapPairs(ListNode* head)
	{
		ListNode h{0};
		h.next = head;
		ListNode* cur = &h;

		ListNode* n = nullptr;
		ListNode* nn = nullptr;

		while(cur)
		{
			n = cur->next;
			if(!n) break;
			nn = n->next;
			if(!nn) break;

			cur->next = nn;
			n->next = nn->next;
			nn->next = n;
			cur = n;
		}
		return h.next;
	}

	ListNode* swapPairs2(ListNode* head)
	{
		if(!head || ! head->next) return head;

		auto next = head->next;
		head->next = swapPairs2(next->next);
		next->next = head;
		return next;
	}

	void test() override
	{
		{
			al::timer _{"1"};
			test2(1);
		}
		{
			al::timer _{"2"};
			test2(2);
		}
	}

	void test2(int i)
	{
        ListNode n1{1};
        ListNode n2{2};
        ListNode n3{3};
        ListNode n4{4};
        ListNode n5{5};

        n1.next = &n2;
        n2.next = &n3;
		n3.next = &n4;
		n4.next = &n5;

		printList(&n1);

		ListNode* ret = nullptr;
		switch(i)
		{
			case 1:
				ret = swapPairs(&n1);
				break;
			case 2:
				ret = swapPairs2(&n1);
				break;
			default:
				break;
		}
		printList(ret);

	}

};

}
