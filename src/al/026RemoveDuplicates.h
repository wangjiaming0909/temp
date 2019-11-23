#include "leetcode.h"
#include <vector>


namespace al

{

class RemoveDuplicates : public ILeetCode
{

public:

	int removeDuplicates(vector<int>& nums)
	{
		if(nums.size() == 0) return 0;
		int lastV = nums[0];
		size_t index = 1;
		for(size_t i = 1; i < nums.size(); i++)
		{
			if(nums[i] != lastV)
			{
				lastV = nums[i];
				nums[index] = nums[i];
				index++;
			}
		}
		nums.resize(index);
		return index;
	}

	void print(vector<int>& v)
	{
		for(auto i : v)
		{
			cout << i << " " ;
		}
		cout << endl;
	
	}
	void test() override
	{
		vector<int> v{1,1,2,2,3,4,5,6};
		print(v);
		removeDuplicates(v);
		print(v);
	}



};

}

