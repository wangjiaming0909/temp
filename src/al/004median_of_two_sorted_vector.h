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
          // if(end1 - start1 == 1 && end2 - start2 == 1) return (*start1 + *start2) / 2.0;
          // mid1 = calculateMid(nums1, start1, end1, &pos1);
          // mid2 = calculateMid(nums2, start2, end2, &pos2);

          // if(mid1 == mid2) return mid1;
          // numToDelete = std::min(pos1, pos2) + 1;
          // for(int i = 0; i < numToDelete; i++)
          // {
                if(end1 - start1 == 1 && end2 - start2 == 1) return (*start1 + *start2) / 2.0;
                if(*start1 > *start2)start2++;else start1++;
                if(*(end1-1) < *(end2-1)) end2--; else end1--;
//            }
        }

        if(end1 - start1 > 0)
        {
            return calculateMid(nums1, start1, end1, &pos1);
        }
        return calculateMid(nums2, start2, end2, &pos2);
    }

    double median_of_two_sorted_vector5(const vector<int>& nums1, const vector<int>& nums2){
        al::timer _{__func__};
        int n = nums1.size();
		int m = nums2.size();

		if (n > m)  //保证数组1一定最短
		{
			return median_of_two_sorted_vector5(nums2, nums1);
		}

		// Ci 为第i个数组的割,比如C1为2时表示第1个数组只有2个元素。LMaxi为第i个数组割后的左元素。RMini为第i个数组割后的右元素。
		int LMax1, LMax2, RMin1, RMin2, c1, c2, lo = 0, hi = 2 * n;  //我们目前是虚拟加了'#'所以数组1是2*n长度

		while (lo <= hi)   //二分
		{
			// if c1-1, c2+1
			// if c1+1, c2-1
			c1 = (lo + hi) / 2;  
			c2 = m + n - c1;

			LMax1 = (c1 == 0) ? INT32_MIN : nums1[(c1 - 1) / 2];
			RMin1 = (c1 == 2 * n) ? INT32_MAX : nums1[c1 / 2];
			LMax2 = (c2 == 0) ? INT32_MIN : nums2[(c2 - 1) / 2];
			RMin2 = (c2 == 2 * m) ? INT32_MAX : nums2[c2 / 2];

			if (LMax1 > RMin2)// if nums1's mid >= nums2's mid
				hi = c1 - 1; // c1-1, c2+1, 1 move left, 2 move right
			else if (LMax2 > RMin1) // if nums2's mid >= nums1's mid
				lo = c1 + 1; //c1+1, c2-1, 1 move right, 2 move left
			else
				break;
		}
		//only when lmax1-rmin1 has overlap with lmax2-rmin2
		return (max(LMax1, LMax2) + min(RMin1, RMin2)) / 2.0;
    }

    double median_of_two_sorted_vector6(vector<int>& nums1, vector<int>& nums2)
    {
        al::timer _{__func__};
        auto start1 = nums1.begin();
        auto end1 = nums1.end();
        auto start2 = nums2.begin();
        auto end2 = nums2.end();

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
                numToDelete = std::min(pos1, pos2);
                if(numToDelete == 0)
                {
                    if(*start1 >= *start2) start2++; else start1++;
                    if(*(end1-1) >= *(end2-1)) end1--; else end2--;
                }else 
                {
                    start1 += numToDelete;
                    end2 -= numToDelete;
                }
            }
            else 
            {
                numToDelete = std::min(pos1, pos2);
                if(numToDelete == 0)
                {
                    if(*start1 >= *start2) start2++; else start1++;
                    if(*(end1-1) >= *(end2-1)) end1--; else end2--;
                }else 
                {
                    end1 -= numToDelete;
                    start2 += numToDelete;
                }
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
        ret = median_of_two_sorted_vector5(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector6(v1, v2);
        cout << ret << endl;

        v1 = {1, 2};
        v2 = {-1, 3};
        ret = median_of_two_sorted_vector(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector2(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector3(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector4(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector5(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector6(v1, v2);
        cout << ret << endl;

        v1 = {1, 3};
        v2 = {2};
        ret = median_of_two_sorted_vector(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector2(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector3(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector4(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector5(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector6(v1, v2);
        cout << ret << endl;

        v1 = {2};
        v2 = {1,3,4};
        ret = median_of_two_sorted_vector(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector2(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector3(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector4(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector5(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector6(v1, v2);
        cout << ret << endl;

        v1 = {1,2,5};
        v2 = {3,4,6};
        ret = median_of_two_sorted_vector(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector2(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector3(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector4(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector5(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector6(v1, v2);
        cout << ret << endl;

        v1 = {1,5,6};
        v2 = {2,3,4};
        ret = median_of_two_sorted_vector(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector2(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector3(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector4(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector5(v1, v2);
        cout << ret << endl;
        ret = median_of_two_sorted_vector6(v1, v2);
        cout << ret << endl;
    }
};

}//namespace al

#endif // _AL_LEETCODE_004
