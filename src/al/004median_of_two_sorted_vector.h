#ifndef _AL_MEDIAN_OF_TWO_STORED_VECTOR
#define _AL_MEDIAN_OF_TWO_STORED_VECTOR
#include <vector>
#include "../timer.h"
using namespace std;

namespace al{

namespace Nmedian_of_two_stored_vector{

double median_of_two_stored_vector(const vector<int>& nums1, const vector<int>& nums2){
    al::timer _{__func__};
    if(nums1.size() == 0){
        return median_of_two_stored_vector(nums2, nums2);
    }else if(nums2.size() == 0){
        return median_of_two_stored_vector(nums1, nums1);
    }
    int v1_start = 0, v1_end = nums1.size() - 1;
    int v2_start = 0, v2_end = nums2.size() - 1;
    while(true){
        if(v1_start <= v1_end && v2_start <= v2_end){
            if(v1_start == v1_end && v2_start == v2_end) break;
            if(nums1[v1_start] <= nums2[v2_start])
                v1_start++;
            else v2_start++;
            if(nums2[v2_end] >= nums1[v1_end])
                v2_end--;
            else v1_end--;
        }else{
            if(v2_start < v2_end - 1){
                vector<int> v{nums2.begin() + v2_start, nums2.begin() + v2_end + 1};
                return median_of_two_stored_vector(v, v);
            }else if(v1_start < v1_end - 1){
                vector<int> v{nums1.begin() + v1_start, nums1.begin() + v1_end};
                return median_of_two_stored_vector(v, v);
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
        if(v1_start > v1_end) return (nums2[v2_start] + nums2[v2_end])/2.0;
        else return (nums1[v1_start] + nums1[v1_end])/2;
    }
}


double median_of_two_stored_vector2(const vector<int>& nums1, const vector<int>& nums2){
    al::timer _{__func__};
    bool even = 0;
        int size1 = nums1.size();
        int size2 = nums2.size();
        priority_queue<int> tree;
        
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
            }
            else{
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

int test(){
    vector<int> v1{1,1,1,1,1,1,1,1,1,1,4,4,5,6,7,8,9,10,11,223,1212};
    vector<int> v2{1,3,4,4,4,4,4,4,4,4,4,4,5,6,7,8,9,10,11,223,1123,1123,1123,1123,1123,2231,2233,3333,4444,5555,6666,7777,8888};
    // v1 = {1,1,1};
    // v2 = {1,1,1};
    v1.reserve(10000);
    for(int i = 0; i < 10000; i++){
        v1[i] = i;
    }
    v2.reserve(20000);
    for(int i = 0; i < 20000; i++){
        v2[i] = i*2 + 19;
    }
    double ret = median_of_two_stored_vector(v1, v2);
    cout << ret << endl;
    ret = median_of_two_stored_vector2(v1, v2);
    cout << ret << endl;
}

} //namespace median_of_two_stored_vector
}//namespace al
#endif // _AL_MEDIAN_OF_TWO_STORED_VECTOR