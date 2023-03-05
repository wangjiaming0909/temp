#pragma once
#include "leetcode.h"
#include <cassert>

namespace al
{


class AddTwoNumbers : public ILeetCode
{
public:
  void clear() {pre_head = new ListNode(0); cur_node = pre_head;}
  ListNode *pre_head = new ListNode(0);
  ListNode *cur_node = pre_head;
  void add_node(int val) {
    auto node = new ListNode(val);
    pre_head->next = pre_head->next == nullptr ? node : pre_head->next;
    cur_node->next = node;
    cur_node = node;
  }

  ListNode * add_two_numbers(ListNode*l1, ListNode* l2) {
    auto *cur1 = l1;
    auto  *cur2 = l2;

    int plus_1 = 0;
    while (cur1 && cur2) {
      int val = cur1->val + cur2->val + plus_1;
      plus_1 = val >= 10 ? 1 : 0;
      val = val % 10;
      add_node(val);
      cur1 = cur1->next;
      cur2 = cur2->next;
    }

    while (cur1) {
      add_node(cur1->val + plus_1);
      plus_1 = 0;
      cur1 = cur1->next;
    }
    while(cur2) {
      add_node(cur2->val+ plus_1);
      plus_1 = 0;
      cur2 = cur2->next;
    }
    if (plus_1) {
      add_node(1);
    }

    return pre_head->next;
  }

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

    //auto node = addTwoNumbers1(&n1, &nn1);
    auto node = add_two_numbers(&n1, &nn1);
    assert(node != nullptr);
    assert(node->val == 3);
    assert(node->next->val == 0);
    assert(node->next->next->val == 8);
    assert(node->next->next->next == nullptr);

    clear();

    ListNode p{5};
    ListNode p2{5};
    //node = addTwoNumbers1(&p, &p2);
    node = add_two_numbers(&p, &p2);
    assert(node != nullptr);
    assert(node->val == 0);
    assert(node->next->val == 1);
  }


};
}
