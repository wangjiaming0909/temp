#ifndef _LEETCODE_H_
#define _LEETCODE_H_
#include <iostream>
using namespace std;

namespace al{

class ILeetCode{
public:
    virtual void test() = 0;
};

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
};

void printList(ListNode* head)
{
    while(head != nullptr)
    {
        cout << head->val << " -> ";
        head = head->next;
    }
    cout << endl;
}

} //namespace al
#endif // _LEETCODE_H_