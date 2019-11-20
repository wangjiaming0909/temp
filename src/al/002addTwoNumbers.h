#pragma once
#include "leetcode.h"

namespace al
{

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class AddTwoNumbers : public ILeetCode
{
public:
    ListNode* addTwoNumbers1(ListNode* l1, ListNode l2)
    {
        
    }
    void test() override 
    {
        ListNode n1{1};
    }


};
}