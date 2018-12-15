#ifndef _AL_LONGESTSUBSTRING_H_
#define _AL_LONGESTSUBSTRING_H_

#include <string>
#include <unordered_map>
#include <cassert>
#include <iostream>
#include <boost/timer.hpp>
#include <iomanip>
#include "../timer.h"
using namespace std;

namespace LONGESTSUBSTRING{

/*
a a s d s w a 
|                   a0              1   
| |                 a1              1
  | |               a1 s2           2
  |   |             a1 s2 d3        3
  |     |           a1 s4 d3        3
      |  |          a1 s4 d3 w5     4
      |    |        a6 s4 d3 w5     4

*/

size_t longestSubString(const string s) {
    al::timer _{__func__};
    size_t start = 0, end = 0;   
    size_t ret = 0;
    unordered_map<char, size_t> char_map{};

    for(; end < s.size(); end++){
        if(char_map.count(s[end]) == 0){//did't contain
            char_map[s[end]] = end;
            ret = std::max(ret, end - start + 1);
        }else{//if contains then modify the start, but start won't go back
            // 1, the contained element is in the front of start, start won't modified,
            //      so we do not need to remove the old elements when we move start
            // 2, the contained element is at the back of start, start will go to back + 1
            //std::max is used to ensure that start will not go back
            start = std::max(char_map.at(s[end]) + 1, start);
            char_map[s[end]] = end;
            ret = std::max(ret, end - start + 1);
        }
    }
    return ret;
}

size_t longestSubString2(const string s) {//do some refactor
    al::timer _{__func__};
    size_t start = 0, end = 0;   
    size_t ret = 0;
    unordered_map<char, size_t> char_map{};

    for(; end < s.size(); end++){
        if(char_map.count(s[end]) != 0){//did't contain
            start = std::max(char_map.at(s[end]) + 1, start);
        }
        char_map[s[end]] = end;
        ret = std::max(ret, end - start + 1);
    }
    return ret;
}



void test(){
    string s1{"tmmzuxasasdqweadqweasdqwdasdqweasdqwedsadwqeasdgrthgjhghkjlyuoiyurgdfsdfdfqwerafsdgqwefsdpogopdjgowjkfopewgrpeasdqpwfqpqiowersdasdqwegfdfuiqtvzxcnmihfiowircjpoqjwfwekwkggslfqowejhfashdqljgnqweqafasdqwerqwrigt"};
    string s2{"w"};

    int ret1 = 0;
    for(int i = 0; i < 10; i++){
        ret1 = longestSubString2(s1);
        ret1 = longestSubString(s1);
    }
    cout << "ret1: " << ret1 << endl;
    int ret2 = longestSubString2(s2);
    cout << "ret2: " << ret2 << endl;
    assert(ret2 == 1);
}

}

#endif // _AL_LONGESTSUBSTRING_H_