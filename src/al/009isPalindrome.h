#include "leetcode.h"
#include <vector>

using namespace std;
namespace al
{
class IsPalindrome : public ILeetCode
{
public:
    bool isPalindrome(int x)
    {
        vector<int> v{};
        if(x < 0) return false;
        if(x == 0) return true;
        int a = 0;
        while(x > 0)
        {
            a = x % 10;
            x /= 10;
            v.push_back(a);
        }
        size_t i = 0;
        size_t j = v.size();
        while(i <= j)
        {
            if(v[i] != v[j-1]) return false;
            i++;
            j--;
        }
        return true;
    }

    void test()override
    {
        int a = 123321;
        assert(isPalindrome(a));
        a = 12321;
        assert(isPalindrome(a));
    }
};
}