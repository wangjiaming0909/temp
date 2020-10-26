#pragma once
#include "leetcode.h"
#include <cassert>

namespace al
{


class AddTwoNumbers : public ILeetCode
{
public:
    ListNode* addTwoNumbers1(ListNode* l1, ListNode* l2)
    {
      bool forward = false;
      ListNode *p = nullptr;
      ListNode *target = nullptr;
      while(l1 != nullptr || l2 != nullptr) {
        auto val= (l1 ? l1->val : 0) +  (l2 ? l2->val : 0) + (forward ? 1 : 0);
        forward = val >= 10 ? true : false;
        val = val % 10;
        if (!target) {
          p = new ListNode{val};
          target = p;
        } else {
          p->next = new ListNode{val};
        }
        p = p->next;
        l1 = l1 ? l1->next : l1;
        l2 = l2 ? l2->next : l2;
      }

      if(forward) {
        p->next = new ListNode{1};
      }
      return target;
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
