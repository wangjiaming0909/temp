#include <iostream>
#include <string>
#include <stack>
#include <algorithm>
#include <vector>
using namespace std;

void print()
{
    cout << "123" << endl;
}
bool isdotdot(const string &s)
{
    return s == string("/..");
}

bool isdot(const string &s)
{
    return s == string("/.");
}

bool isline(const string &s)
{
    return s == string("/");
}

//搜狐笔试题1
//关于linux下文件目录简化 /./    /../    //
void main_linux()
{
    stack<string> stack_string;
    string s;
    cin >> s;
    auto it_ = s.begin();
    if (*it_ == '/')
        stack_string.push(string("/"));
    else
    {
        cout << "error" << endl;
        return;
    }
    while (true)
    {
        auto it1 = it_;
        auto it2 = find(it1 + 1, s.end(), '/');
        if (it2 == s.end())
        { //查找到末尾了
            // cout << "over" << endl;
            string last(it1, it2);
            if (isdot(last))
            {
                it_ = it2;
                break;
            }
            else if (isdotdot(last))
            {
                if (stack_string.top() == string("/"))
                {
                    cout << "already in the root dir" << endl;
                    return;
                }
                stack_string.pop();
                if (stack_string.empty())
                    stack_string.push(string("/"));
                it_ = it2;
                break;
            }
            else if (isline(last))
            {
                it_ = it2;
                break;
            }
            else
            {
                it_ = it2;
                if (stack_string.top() == string("/"))
                    stack_string.pop();
                stack_string.push(last);
            }
            break;
        }
        string ss(it1, it2); //构造string时，从it1开始，到it2的前一个
        if (isdot(ss))
        {
            it_ = it2;
            continue;
        }
        else if (isdotdot(ss))
        {
            if (stack_string.top() == string("/"))
            {
                stack_string.pop();
                cout << "already in the root dir" << endl;
                return;
            }
            if (!stack_string.empty())
            {
                stack_string.pop();
            }
            if (stack_string.empty())
                stack_string.push("/");
            it_ = it2;
            continue;
        }
        else if (isline(ss))
        {
            it_ = it2;
            continue;
        }
        else
        {
            it_ = it2;
            if (stack_string.top() == string("/"))
                stack_string.pop();
            stack_string.push(ss);
        }
    }
    vector<string> v;
    while (!stack_string.empty())
    {
        v.insert(v.begin(), stack_string.top());
        stack_string.pop();
    }
    for (auto &it : v)
    {
        cout << it;
    }
    cout << endl;
}