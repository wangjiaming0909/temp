#pragma once
#include "leetcode.h"
#include <iostream>
#include <vector>

using namespace std;

namespace al
{

//删除链表的第n个节点, 只使用一趟遍历, n保证是有效的
class RemoveNthFromEnd : public ILeetCode
{
public:

    ListNode* removeNthFromEnd(ListNode* head, int n)
    {
        ListNode node{0};
        node.next = head;
        if(head == nullptr) return nullptr;
        ListNode* cur1 = &node, *cur2 = &node;
        for (size_t i = 0; i < static_cast<size_t>(n); i++)
        {
            cur2 = cur2->next;
        }

        while(cur2->next != nullptr)
        {
            cur1 = cur1->next;
            cur2 = cur2->next;
        }

        cur1->next = cur1->next->next;
        return node.next;
    }

    void test() override
    {
        ListNode n1{1};
        ListNode n2{2};
        ListNode n3{3};

        n1.next = &n2;
        n2.next = &n3;

        printList(&n1);

        auto node = removeNthFromEnd(&n1, 2);
        printList(node);

        ListNode nn1{2};
        ListNode nn2{8};
        ListNode nn3{4};
        n3.next = &nn1;
        nn1.next = &nn2;
        nn2.next = &nn3;
        printList(&n1);

        node = removeNthFromEnd(&n1, 1);
        printList(node);
        node = removeNthFromEnd(&n1, 1);
        printList(node);
        node = removeNthFromEnd(&n1, 3);
        printList(node);
        node = removeNthFromEnd(node, 2);
        printList(node);
        node = removeNthFromEnd(node, 1);
        printList(node);
    }
};

}