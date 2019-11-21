#include "leetcode.h"
#include <string>
#include <iostream>
#include "../timer.h"

using namespace std;
namespace al
{
class Atoi : public ILeetCode
{
public:
    int myAtoi(string s)
    {
        al::timer _{__func__};
        int sign = 1;
        int64_t ret = 0;
        bool started = false;
        for(auto c : s)
        {
            if(c == ' ') 
            {
                if(!started)
                {
                    continue;
                }
                else break;
            }
            if(c == '+')
            {
                if(!started)
                {
                    started = true;
                    continue;
                }
                else break;
            }
            if(c == '-') 
            {
                if(!started) 
                {
                    started = true;
                    sign = -1;
                    continue;
                }
                else break;
            }
            if(c < 48 || c > 57)
            {
                if(!started) return 0;
                else break;
            }
            ret = ret * 10 + (c - 48);
            if(ret*sign > INT32_MAX)
            {
                ret = INT32_MAX;
                break;
            } 
            else if(ret*sign < INT32_MIN)
            {
                ret = INT32_MIN;
                break;
            }
            started = true;
        }
        return ret * sign;
    }
    int myAtoi2(string str)
    {
        al::timer _{__func__};
        int result = 0;
        stringstream ss;
        ss << str;
        ss >> result;
        return result;
    }

    void test() override
    {
        string s{"123456"};
        assert(myAtoi(s) == 123456);
        s = "-123456";
        assert(myAtoi(s) == -123456);
        s = "  -123456";
        assert(myAtoi(s) == -123456);
        s = "w  -123456";
        assert(myAtoi(s) == 0);
        s = " -123456 ws";
        assert(myAtoi(s) == -123456);
        s = " -123456-ws";
        assert(myAtoi(s) == -123456);
        s = "12345512313123123";
        assert(myAtoi(s) == INT32_MAX);
        s = "-12345512313123123";
        assert(myAtoi(s) == INT32_MIN);
        assert(myAtoi2(s) == INT32_MIN);


        s = "+1";
        assert(myAtoi(s) == 1);
        s = "+-1";
        assert(myAtoi(s) == 0);
    }
};

}