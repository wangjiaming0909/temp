#pragma once
#include "leetcode.h"
#include <cassert>

namespace al
{

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

class AddTwoNumbers : public ILeetCode
{
public:
    ListNode* addTwoNumbers1(ListNode* l1, ListNode* l2)
    {
        auto p1 = l1;
        auto p2 = l2;
        bool forward = false;
        ListNode *target = new ListNode{0};
        auto p = target;
        while(p1 != nullptr || p2 != nullptr)
        {
            auto p1v = p1 ? p1->val : 0;
            auto p2v = p2 ? p2->val : 0;
            auto val = p1v + p2v + (forward ? 1 : 0);
            forward = val >= 10 ? true : false;
            val = val % 10;
            p->next = new ListNode{val};
            p = p->next;
            p1 = p1 ? p1->next : p1;
            p2 = p2 ? p2->next : p2;
        }

        if(forward)
        {
            p->next = new ListNode{1};
        }
        auto ret = target->next;
        delete target;
        target = nullptr;
        return ret;
    }
    void test() override 
    {
        ListNode n1{1};
        ListNode n2{2};
        ListNode n3{3};

        n1.next = &n2;
        n2.next = &n3;


        ListNode nn1{2};
        ListNode nn2{8};
        ListNode nn3{4};
        nn1.next = &nn2;
        nn2.next = &nn3;

        auto node = addTwoNumbers1(&n1, &nn1);
        assert(node != nullptr);
        assert(node->val == 3);
        assert(node->next->val == 0);
        assert(node->next->next->val == 8);
        assert(node->next->next->next == nullptr);

        ListNode p{5};
        ListNode p2{5};
        node = addTwoNumbers1(&p, &p2);
        assert(node != nullptr);
        assert(node->val == 0);
        assert(node->next->val == 1);
    }


};
}