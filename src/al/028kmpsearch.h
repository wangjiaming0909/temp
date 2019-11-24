#include "leetcode.h"
#include <memory>
#include <vector>

namespace al
{

class KmpSearch : public ILeetCode
{
public:

    shared_ptr<vector<int>> buildSearchTable(const string& needle)
    {
        if(needle.size() == 0) return shared_ptr<vector<int>>();
        vector<int> *searchTable = new vector<int>();
        searchTable->resize(needle.size());
        searchTable->operator[](0) = -1;
        int t = -1;
        int j = 0;

        while(j < static_cast<int>(needle.size() - 1))
        {
            if(t < 0 || needle[j] == needle[t])
            {
                searchTable->operator[](++j) = ++t;
            }
            else
            {
                t = searchTable->operator[](t);
            }
        }
        return std::shared_ptr<vector<int>>(searchTable);
    }

    int kmpSearch(string& haystack, string& needle)
    {
        auto searchTable = buildSearchTable(needle);
        printVector<int>(*searchTable);
        int j = 0;
        int t = 0;

        while (j < haystack.size() && t < static_cast<int>(needle.size()))
        {
            cout << haystack << endl;
            string space(int(j - t) , ' ');
            cout << space << needle << endl;
            string spacej(int(j), ' ');
            cout << spacej << '|' << endl;
            if(t < 0 || needle[t] == haystack[j])
            {
                t++;
                j++;
            }else
            {
                cout << "forward: ";
                        auto temp = t;
                t = searchTable->operator[](t);
                cout <<  temp - t << endl;
            }
            cout << endl;
        }
        if (t < needle.size())
            return -1;
        return j - t;
    }

    void test() override
    {
        string needle{"abcdaabcab"};
        auto vptr = buildSearchTable(needle);
        cout << needle << endl;
        printVector<int>(*vptr);

        string t = "ababababcdaabcab";
        cout << "kmpsearch: " << endl;
        cout << kmpSearch(t, needle) << endl;

        t = "asdasdasdasdasdasd";
        needle =  "sdasdasd";
        cout << "kmpsearch: " << endl;
        cout << kmpSearch(t, needle) << endl;

        needle = "ll";
        vptr = buildSearchTable(needle);
        cout << needle << endl;
        printVector<int>(*vptr);
        t = "hello";
        cout << "kmpsearch: " << kmpSearch(t, needle) << endl;
    }
};
}
