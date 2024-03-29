#ifndef _AL_LEETCODE_005
#define _AL_LEETCODE_005

#include "leetcode.h"
#include <unordered_map>
#include "../timer.h"
#include <string>

#include <vector>

using namespace std;
namespace al{

class Longest_palindromic_strstring : public ILeetCode{
public:
    string longestPalindrome(const string& s) {//O(n*n)
        al::timer _{__func__};
        if(s.size() == 0) return "";
        int start = 0, end = 0;
        for(size_t i = 0; i < s.size(); i++){//O(n)
            size_t len1 = expandAroundCenter(s, i, i);//i is the center
            size_t len2 = expandAroundCenter(s, i, i+1);// (i and i+1) is the center
            size_t len = std::max(len1, len2);            
            if(static_cast<int>(len) > end - start){//if the new len is longer than the recorded longest one
                start = i - (len - 1) / 2;//update start
                end = i + len / 2;//update end
            }
        }
        return string(s.begin() + start, s.begin() + end + 1);
    }

    string longestPalindrome_Manacher(const string& s){//O(n)
        al::timer _{__func__};
        string manacherStr = "$#";
        for(auto& ch : s){
            manacherStr.push_back(ch);
            manacherStr.push_back('#');
        }
        vector<int> v(manacherStr.size(), 0);
        int mx = 0, id = 0, resLen = 0, resCenter = 0;
        for(int i = 0; i < static_cast<int>(manacherStr.size()); i++){

            v[i] = mx > i ? std::min(v[2 * id - i], mx - i) : 1;
            while(manacherStr[i + v[i]] == manacherStr[i - v[i]]) 
                ++v[i];
            if(mx < i + v[i]){
                mx = i + v[i];
                id = i;
            }
            if(resLen < v[i]){
                resLen = v[i];
                resCenter = i;
            }
        }
        return s.substr((resCenter - resLen) / 2, resLen - 1);
    }

    string longestPalindrome2(const string& s) {
      vector<vector<int>> dp;
      dp.resize(s.size());
      for (int i = 0; i < s.size(); ++i){
        dp[i].resize(s.size(), 0);
      }
      int max = 1, max_i = 0, max_j = 0;

      for (int j = 1; j < s.size(); ++j) {
        for (int i = j - 1; i >= 0; --i) {
          if (s[i] == s[j]) {
            if (j < i + 3) dp[i][j] = j-i+1;
            else dp[i][j] = dp[i+1][j-1] == 0 ? 0 : dp[i+1][j-1] + 2;

            if (max < dp[i][j]) {
              max = dp[i][j]; max_i = i; max_j = j;
            }
          } else {
            dp[i][j] = 0;
          }
        }
      }

      return s.substr(max_i, max);
    }


    void test(const string &s) {
        auto ret = longestPalindrome(s);
        cout << ret << endl;
        //ret = longestPalindrome_Manacher(s);
        //cout << ret << endl;
        ret = longestPalindrome2(s);
        cout << ret << endl;
    }

    virtual void test() override{
        string s{"tmmzuxasasdqweadqweasdqwdasdqweasdqwedsadwqeasdgrthgjhghkjlyuoiyurgdfsdfdfqwerafsdgqwefsdpogopdjgowjkfopewgrpeasdqpwfqpqiowersdasdqwegfdfuiqtvzxcnmihfiowircjpoqjwfwekwkggslfqowejhfashdqljgnqweqaasdjkwwqdandasdasdfghjklplkjhgfdsalkjwdansxcdjfqpwjdasndcnhasdwjhqndacansclsnvlwkdjfqpejtpqwtpjgskjffasdqwerqwrigt"};
        test(s);
        s = "asdsa";
        test(s);
        s = "aaaa";
        test(s);
        s = "asddsa";
        test(s);
        s = "babad";
        test(s);
        s = "aacabdkacaa";
        test(s);
        s = "cbb";
        test(s);
        s = "a";
        test(s);
    }

private:
    size_t expandAroundCenter(const string& s, size_t left, size_t right){//O(n)
        int L = left;
        size_t R = right;
        while(L >= 0 && R < s.size() && s[L] == s[R]){
            L--;
            R++;
        }
        return R-L-1;
    }
};
}//al
#endif // _AL_LEETCODE_005
