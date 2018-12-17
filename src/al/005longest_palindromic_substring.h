#ifndef _AL_LEETCODE_005
#define _AL_LEETCODE_005

#include "leetcode.h"
#include <unordered_map>
#include "../timer.h"

using namespace std;
namespace al{

class Longest_palindromic_strstring : public ILeetCode{
public:
    string longestPalindrome(string s) {
        al::timer _{__func__};
        return s;
    }
    virtual void test() override{
        string s{"ad"};
        auto ret = longestPalindrome(s);
}
};
}//al
#endif // _AL_LEETCODE_005