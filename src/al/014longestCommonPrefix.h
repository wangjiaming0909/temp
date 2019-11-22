#include "leetcode.h"
#include <iostream>
#include <vector>
#include <string>

using namespace std;


namespace al
{
class LongestCommonPrefix : public ILeetCode
{
public:

    string longestCommonPrefix(vector<string>& strs)
    {
        string ret{};
        char c = '\0';
        size_t index = 0;
        while(1)
        {
            for(auto& str : strs)
            {
                if(str.size() <= index) return ret;
                if(c == '\0') c = str[index];
                else
                {
                    if(c != str[index]) return ret;
                }
            }
            ret.push_back(c);
            c = '\0';
            index++;
        }
        return ret;
    }

    void test() override
    {
        vector<string> v = {"flower", "flow", "flight"};
        cout << longestCommonPrefix(v) << endl;;
        v = {"a", "asd"};
        cout << longestCommonPrefix(v) << endl;;
        v = {"a"};
        cout << longestCommonPrefix(v) << endl;;
        v = {"dog", "asd"};
        cout << longestCommonPrefix(v) << endl;;
        v = {""};
        cout << longestCommonPrefix(v) << endl;;
    }
};

}
