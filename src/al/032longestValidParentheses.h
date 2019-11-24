#pragma once
#include "leetcode.h"
#include <stack>


namespace al {

struct StackNode{
    StackNode(char c, size_t pos) : c(c), pos(pos){}
    char c;
    size_t pos;
};

class LongestValidParentheses : public ILeetCode
{
public:
    int longestValidParentheses(string s) {
        if(s.size() == 0) return 0;
        vector<char> v{0};
        v.resize(s.size());
        stack<StackNode> st{};
        for(size_t i = 0; i < s.size(); i++)
        {
            char c = s[i];
            if(c == ')' && !st.empty() && st.top().c == '(')
            {
                v[st.top().pos] = 1;
                v[i] = 1;
                st.pop();
            }
            else st.push(StackNode(c, i));
        }
        int max = 0;
        int tmp = 0;
        for(size_t i = 0; i <v.size(); i++)
        {
            if(v[i] == 1)
            {
                tmp++;
            }
            else
            {
                max = std::max(max, tmp);
                tmp = 0;
            }
        }
        return std::max(max, tmp);
    }

    //动态规划
    int longestValidParentheses2(string s) {
        vector<int> v{};
        v.resize(s.size());
        int max = 0;
        for(int j = 1; j < s.size(); j++)
        {
            if(s[j] == ')' && s[j-1] == '(')
            {
                v[j] = j > 1 ? v[j-2]+2 : 2;
            }
            else if(s[j] == ')' && j - v[j-1] > 0 && s[j - v[j-1]-1] == '(')
            {
                v[j] = v[j-1]+2 + ((j - v[j-1] > 2) ? v[j-v[j-1]-2] : 0);
            }
            max = std::max(max, v[j]);
        }
        return max;
    }

    void test() override
    {
        cout << longestValidParentheses("(()") << endl;
        cout << longestValidParentheses(")()())") << endl;
        cout << longestValidParentheses("") << endl;
        cout << longestValidParentheses("))(()))()") << endl;
        cout << longestValidParentheses("()(())") << endl;

        cout << longestValidParentheses2("(()") << endl;
        cout << longestValidParentheses2(")()())") << endl;
        cout << longestValidParentheses2("") << endl;
        cout << longestValidParentheses2("))(()))()") << endl;
        cout << longestValidParentheses2("()(())") << endl;
    }
};


}
