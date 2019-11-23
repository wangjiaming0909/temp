#include "leetcode.h"


namespace al
{

class ReverseKGroup : public ILeetCode
{

public:

	//a->b ---->  a<-b	
	ListNode* reverseKNodes(ListNode* head, ListNode* lastNode)
	{
		if(!head) return lastNode;
		auto next = head->next;
		if(!next) 
		{
			head->next = lastNode;
			return head;
		}

		auto temp = next->next;
		next->next = head;
		head->next = lastNode;

		return reverseKNodes(temp, next);
	}

	ListNode* lastNodeOfK(ListNode* head, int k)
	{
		while(head && k > 0)
		{
			k--;
			if(k > 0) head = head->next;
		}
		return head;
	}

	ListNode* reverseGroups(ListNode* head, int k, ListNode* lastNode)
	{
		auto last = lastNodeOfK(head, k);
		if(!last) return head;
		auto next = last->next;

		last->next = nullptr;
		auto newFirstNode = reverseKNodes(head, next);
		lastNode->next = newFirstNode;

		auto n = reverseGroups(next, k, head);
		head->next = n;
		return newFirstNode;
	}

	ListNode* reverseKGroup(ListNode* head, int k)
	{
		ListNode h{0};
		h.next = head;
		reverseGroups(head, k, &h);
		return h.next;
	}

	void test() override
	{
        ListNode n1{1};
        ListNode n2{2};
        ListNode n3{3};
        ListNode n4{4};
        ListNode n5{5};

        n1.next = &n2;
        //n2.next = &n3;
		//n3.next = &n4;
		//n4.next = &n5;

		printList(&n1);
	
		auto ret = reverseKGroup(&n1, 3);
		printList(ret);
	
	}
};



}
