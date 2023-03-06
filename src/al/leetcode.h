#ifndef _LEETCODE_H_
#define _LEETCODE_H_
#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
using namespace std;

namespace al{

class ILeetCode{
public:
    virtual void test() = 0;
    virtual void test_with_param(vector<string> params) {}
    static inline vector<string> get_params(int argc, char** argv);
    inline bool param_check(int expected_size, const vector<string>& params);
};

inline vector<string> ILeetCode::get_params(int argc, char **argv){
  vector<string> ret;
  for (int i = 1; i < argc; ++i) {
    ret.push_back(argv[i]);
  }
  return ret;
}

inline bool ILeetCode::param_check(int expected_size, const vector<string> & params){
  if (params.size() < expected_size) {
    printf("expected param size: %d actual size: %ld\n", expected_size, params.size());
    return false;
  }
  return true;
}

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(nullptr) {}
	bool operator>(const ListNode& node) const
	{
		return val > node.val;
	}
	bool operator<(const ListNode& node) const
	{
		return val < node.val;
	}
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

template <typename T>
void printVector(const vector<T>& v)
{
    for(auto& i : v)
    {
        cout << i << " ";
    }
//    cout << endl;
}

template <typename T>
void printStack(stack<T>& s)
{
    while(!s.empty())
    {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;
}

} //namespace al
#endif // _LEETCODE_H_
