#include "leetcode.h"
#include <vector>
#include <string>
#include <queue>
#include <stack>

namespace al
{

class GenerateParenthesis : public ILeetCode
{
public:

    vector<string>& addParaenthesis(vector<string>& v, bool isLeft, int left, int right, string s)
    {
        if(isLeft)
        {
            left--;
            s.push_back('(');
        }
        else
        {
            right--;
            s.push_back(')');
        } 

        if(left == 0 && right == 0)
        {
            v.push_back(s);
        }
        if(left > 0)
        {
            addParaenthesis(v, true, left, right, s);
        }
        if(right > 0 && right > left)
        {
            addParaenthesis(v, false, left, right, s);
        }
        return v;
    }
    vector<string> generateParenthesis(int n)
    {
        int left = n, right = n;
        vector<string> ret{};
        string s{};
        addParaenthesis(ret, true, left, right, s);
        return ret;
    }

    void print(vector<string>& v)
    {
        for(auto& s : v)
        {
            cout << s << endl;
        }
    }
    void test() override
    {

        auto v = generateParenthesis(3);
        print(v);
        v = generateParenthesis(4);
        print(v);
    }
};
}
