#ifndef _AL_LEETCODE_004
#define _AL_LEETCODE_004

#include <vector>
#include "../timer.h"
#include "leetcode.h"
#include <queue>
#include "../ds/maxheap.h"
using namespace std;

namespace al{

class Median_of_two_sorted_vector : public ILeetCode{
public:
    double median_of_two_sorted_vector(const vector<int>& nums1, const vector<int>& nums2){
        al::timer _{__func__};
        if(nums1.size() == 0){
            return median_of_two_sorted_vector(nums2, nums2);
        }else if(nums2.size() == 0){
            return median_of_two_sorted_vector(nums1, nums1);
        }
        int v1_start = 0, v1_end = nums1.size() - 1;
        int v2_start = 0, v2_end = nums2.size() - 1;
        while(true){
            if(v1_start <= v1_end && v2_start <= v2_end){
                if(v1_start == v1_end && v2_start == v2_end) break;
                if(nums1[v1_start] <= nums2[v2_start])
                    v1_start++;
                else v2_start++;
                if(nums2[v2_end] >= nums1[v1_end]) v2_end--;
                else v1_end--;
            }else{
                if(v2_start < v2_end - 1){
                    vector<int> v{nums2.begin() + v2_start, nums2.begin() + v2_end + 1};
                    return median_of_two_sorted_vector(v, v);
                }else if(v1_start < v1_end - 1){
                    vector<int> v{nums1.begin() + v1_start, nums1.begin() + v1_end};
                    return median_of_two_sorted_vector(v, v);
                }else{
                    break;
                }
            }
        }
        if(v1_start == v1_end && v2_end != v2_start){
            return nums1[v1_start];
        }else if(v2_start == v2_end && v1_end != v1_start){
            return nums2[v2_start];
        }else if(v1_start == v1_end && v2_end == v2_start){
            return (nums1[v1_start] + nums2[v2_start])/2.0;
        }else{
            if(v1_start > v1_end) 
                return (nums2[v2_start] + nums2[v2_end])/2.0;
            else 
                return (nums1[v1_start] + nums1[v1_end])/2;
        }
    }

    double median_of_two_sorted_vector2(const vector<int>& nums1, const vector<int>& nums2){
        al::timer _{__func__};
        bool even = 0;
        int size1 = nums1.size();
        int size2 = nums2.size();
        ds::maxheap<int> tree{size1+size2+1};
        
        int medianSize = (size1+size2)/2 +1;
        if((size1 + size2) %2==0 ){
            even = true;
        }
        
        int itemsInserted = 0;
        
        //to find the (size1+size2)/2 + 1 elements from the two vectors
        //use the maxheap, push (size1+size2)/2 elements into it
        for(int i=0; i<size1+size2; i++){
            int num = (i<size1) ? nums1[i] : nums2[i-size1];
            if(itemsInserted >= medianSize){
                if(tree.top()>num){
                    tree.pop();
                    tree.push(num);
                }
            } else{
                tree.push(num);
                itemsInserted++;
            }
        }
        
        if(even){
            double n1 = tree.top();
            tree.pop();
            double n2 = tree.top();
            return (n1+n2)/2;
            
        }
        else return tree.top();
    }

    double median_of_two_sorted_vector3(const vector<int>& nums1, const vector<int>& nums2){
        al::timer _{__func__};
        bool even = 0;
        int size1 = nums1.size();
        int size2 = nums2.size();
        // ds::maxheap<int> tree{size1+size2+1};
        std::priority_queue<int> tree{};
        
        int medianSize = (size1+size2)/2 +1;
        if((size1 + size2) %2==0 ){
            even = true;
        }
        
        int itemsInserted = 0;
        
        for(int i=0; i<size1+size2; i++){
            int num = (i<size1) ? nums1[i] : nums2[i-size1];
            if(itemsInserted >= medianSize){
                if(tree.top()>num){
                    tree.pop();
                    tree.push(num);
                }
            } else{
                tree.push(num);
                itemsInserted++;
            }
        }
        
        if(even){
            double n1 = tree.top();
            tree.pop();
            double n2 = tree.top();
            return (n1+n2)/2;
            
        }
        else return tree.top();
    }

    double calculateMid(const vector<int>& v, vector<int>::iterator begin, vector<int>::iterator end, int* pos)
    {
        if(v.size() == 0) return 0;
        if(end <= begin) return 0;
        *pos = (end - begin - 1) / 2;
        if((end - begin) % 2 == 0)
        {
            return (*(begin + *pos) + *(begin + *pos + 1)) / 2.0;
        }
        return *(begin + *pos);
    }

    double median_of_two_sorted_vector4(vector<int>& nums1, vector<int>& nums2)
    {
        al::timer _{__func__};
        auto start1 = nums1.begin();
        auto end1 = nums1.end();
        auto start2 = nums2.begin();
        auto end2 = nums2.end();
        auto size1 = nums1.size();
        auto size2 = nums2.size();

        int pos1 = 0;
        int pos2 = 0;
        double mid1 = 0;
        double mid2 = 0;
        int numToDelete = 0;

        while(end1 - start1 > 0 && end2 - start2 > 0)
        {
            if(end1 - start1 == 1 && end2 - start2 == 1) return (*start1 + *start2) / 2.0;
            mid1 = calculateMid(nums1, start1, end1, &pos1);
            mid2 = calculateMid(nums2, start2, end2, &pos2);

            if(mid1 == mid2) return mid1;
            if(mid1 < mid2)
            {
                numToDelete = std::min(pos1, pos2) + 1;
                start1 += numToDelete;
                end2 -= numToDelete;
            }
            else 
            {
                numToDelete = std::min(pos1, pos2) + 1;
                start2 += numToDelete;
                end1 -= numToDelete;
            }
        }

        if(end1 - start1 > 0)
        {
            return calculateMid(nums1, start1, end1, &pos1);
        }
        return calculateMid(nums2, start2, end2, &pos2);
    }
    
    virtual void test() override{
        vector<int> v1{1,1,1,1,1,1,1,1,1,1,4,4,5,6,7,8,9,10,11,223,1212};
        vector<int> v2{1,3,4,4,4,4,4,4,4,4,4,4,5,6,7,8,9,10,11,223,1123,1123,1123,1123,1123,2231,2233,3333,4444,5555,6666,7777,8888};
        // v1 = {1,1,1};
        // v2 = {1,1,1};
        int size1 = 1002;
        int size2 = 2009;
        v1.resize(size1);
        for(int i = 0; i < size1; i++){
            v1[i] = i;
        }
        v1 = {1};
        v2.resize(size2);
        for(int i = 0; i < size2; i++){
            v2[i] = i*2 + 190;
        }
        // v1 = {1,2,3,4};
        // v2 = {5,6,7,8,9};
        double ret = 0;
        ret = median_of_two_sorted_vector(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector2(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector3(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector4(v1, v2);
        cout << ret << endl;
    }
};

}//namespace al

#endif // _AL_LEETCODE_004
