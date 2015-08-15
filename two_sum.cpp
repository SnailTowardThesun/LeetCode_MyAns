#include <stdio.h>
#include <map>
#include <vector>
using namespace std;

/*
 * Given an array of integers,find two numbers such that they add up to a specific target number
 * The function twoSum should return indices of the two numbers such that they add up to the target,where index1 must be less than index2.Please note that your returned answers (both index1 and index2 are not zero-based.
 * Your may assume that each input would have exactly one solution.
 * Input :numbers = {2,7,11,15},target = 9
 * Output: index1 = 2,index2 = 7
 * */

class Solution
{
public:
	vector<int> twoSum(vector<int>& nums, int target)
	{
		int sum;
		vector<int> results;
		map<int,int> hmap;
		for(int i = 0; i< nums.size(); ++i)
		{
			hmap.insert(pair<int,int>(nums[i],i));
			if(hmap.count(target-nums[i]))
			{
				int n = hmap[target-nums[i];
				if(n < i)
				{
					results.push_back(n+1);
					results.push_back(i+1);
					return results;
				}
			}
		}
		return results;
	}
}

int main()
{
	return 0;
}
