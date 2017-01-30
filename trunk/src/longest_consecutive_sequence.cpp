/*
 * Given an unsorted array of integers,find the length of longest consecutive element sequence.
 * Foe example.
 * Given [100,4,200,1,3,2],
 * The longest consecutive elements sequence is [1,2,3,4].Return its length:4
 * Your algorithm should run in O(n) complexity
 */

#include <iostream>
#include <vector>
#include <map>
using namespace std;

class solution
{
public:
	map<int,int> mp;
	int longestconsecutivesequence(vector<int> &nums)
	{
		for(int i = 0; i < nums.size(); i++)
			mp[nums[i]] = 1;

		int result = 0;
		for(int i = 0; i < mp.size(); i++)
		{
			int sum = 1;
			if(mp.count(nums[i]))
			{
				mp[nums[i]] = 0;
				int left = nums[i] - 1;
				while(mp.count(left) && mp[left])
				{
					mp[left--] = 0;
					sum++;
				}
				int right = nums[i] + 1;
				while(mp.count(right) && mp[right])
				{
					mp[right++] = 0;
					sum++;
				}
			}
			if(result<sum) result = sum;
		}
		return result;
	}

};

int test()
{
	int a[] = {100,1,200,2,3,4};
	vector<int> tst(a,a+6);
	solution ss;
	cout<<ss.longestconsecutivesequence(tst)<<endl;
	return 0;
}
