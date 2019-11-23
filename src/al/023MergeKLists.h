#include "leetcode.h"
#include <vector>
#include <queue>

namespace al
{

struct ListNodePointer
{
	ListNodePointer(ListNode* n) : node{n}{}
	bool operator<(const ListNodePointer& p) const 
	{
		if(node == nullptr || p.node == nullptr) return false;
		return node->val < p.node->val;
	}
	bool operator>(const ListNodePointer& p) const 
	{
		if(node == nullptr || p.node == nullptr) return false;
		return node->val > p.node->val;
	}
	ListNode* node = nullptr;
};
class MergeKLists : public ILeetCode
{
public:
	ListNode* mergeKLists(vector<ListNode*>& lists)
	{
		std::priority_queue<ListNodePointer, std::vector<ListNodePointer>, std::greater<ListNodePointer>> q{};
		ListNode head = {0};
		ListNode* cur = &head;
		for(auto node : lists)
		{
			if(node) q.push(ListNodePointer{node});
		}
		while(!q.empty())
		{
			cur->next = q.top().node;
			q.pop();
			cur = cur->next;
			if(cur->next)
			{
				q.push(ListNodePointer{cur->next});
			}
			cur->next = nullptr;
		}
		return head.next;
	}

	ListNode* merge2List(ListNode* l1, ListNode* l2)
	{
		ListNode head{0};
		ListNode* cur = &head;
		while(l1 != nullptr && l2 != nullptr)
		{
			if(l1->val <= l2->val)
			{
				cur->next = l1;
				l1 = l1->next;
				cur = cur->next;
				cur->next = nullptr;
			}
			else if(l1->val > l2->val)
			{
				cur->next = l2;
				l2 = l2->next;
				cur = cur->next;
				cur->next = nullptr;
			}
		}

		while(l1)
		{
			cur->next = l1;
			l1 = l1->next;
			cur = cur->next;
			cur->next = nullptr;
		}

		while(l2)
		{
			cur->next = l2;
			l2 = l2->next;
			cur = cur->next;
			cur->next = nullptr;
		}
		return head.next;
	}

	vector<ListNode*> mergeKList2_(vector<ListNode*>& l)
	{
		if(l.size() <=1) return l;
		vector<ListNode*> v{};

		for(size_t i = 0; i < l.size(); i++)
		{
			if(i % 2 == 0)
			{
				auto right = i+1 < l.size() ? l[i+1] : nullptr;
				auto l2 = merge2List(l[i], right);
				v.push_back(l2);
			}
		}
		return mergeKList2_(v);
	}

	//使用分治思想
	ListNode* mergeKList2(vector<ListNode*>& lists)
	{
		if(lists.size() == 0) return nullptr;
		if(lists.size() == 1)  return lists[0];
		return mergeKList2_(lists)[0];
	}

	void test() override
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


        ListNode nn1{2};
        ListNode nn2{4};
        ListNode nn3{12};
        ListNode nn4{17};
        ListNode nn5{29};
        nn1.next = &nn2;
        nn2.next = &nn3;
        nn3.next = &nn4;
        nn4.next = &nn5;

		printList(&nn1);

        ListNode nnn1{2};
        ListNode nnn2{4};
        ListNode nnn3{37};
        ListNode nnn4{42};
        ListNode nnn5{79};
        nnn1.next = &nnn2;
        nnn2.next = &nnn3;
        nnn3.next = &nnn4;
        nnn4.next = &nnn5;
		printList(&nnn1);

		vector<ListNode*> v{};
		v.push_back(&n1);
		v.push_back(&nn1);
		v.push_back(&nnn1);

		auto ret = mergeKLists(v);
		printList(ret);

		vector<ListNode*> v2{};
		v2.push_back(nullptr);
		ret = mergeKList2(v2);
		printList(ret);


	//	cout << "merge two listes..." << endl;
	//	auto ret = merge2List(&n1, &nn1);
	//	printList(ret);
	//
	//
		cout << "-----------------------------" << endl;
		test2();
	}

	void test2()
	{

		ListNode n1{1};
		ListNode n2{4};
		ListNode n3{5};
		n1.next = &n2;
		n2.next = &n3;

		ListNode q1{1};
		ListNode q2{3};
		ListNode q3{4};

		q1.next = &q2;
		q1.next = &q3;

		ListNode a1{2};
		ListNode a2{6};
		a1.next = &a2;

		vector<ListNode*> v{};
		v.push_back(&n1);
		v.push_back(&q1);
		v.push_back(&a1);

		auto ret = mergeKList2(v);
		printList(ret);
	}
};
}
