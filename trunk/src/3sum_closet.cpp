/*
Given an array S of n integers, find three integers in S such that the sum is closest to a given number, target. 
Return the sum of the three integers. You may assume that each input would have exactly one solution.

For example, given array S = {-1 2 1 -4}, and target = 1.

The sum that is closest to the target is 2. (-1 + 2 + 1 = 2).
*/

class Solution {
public:
	int threeSumClosest(vector<int>& nums, int target) {
		int ret = std::numeric_limits<int>::max() - abs(target);

		std::sort(nums.begin(), nums.end());
		int pos = 0;

		while ((pos < nums.size() - 1) && (nums[pos] < target || ret == std::numeric_limits<int>::max() - abs(target))) {
			int leftPointer = pos + 1;
			int rightPointer = nums.size() - 1;
			while (leftPointer != rightPointer) {
				auto tmpResult = nums[pos] + nums[leftPointer] + nums[rightPointer];
				ret = abs(tmpResult - target) < abs(ret - target) ? tmpResult : ret;
				if (ret == target) {
					break;
				}
				if (tmpResult < target) {
					leftPointer++;
				}
				else {
					rightPointer--;
				}
			}
			pos++;
		}

		return ret;
	}
};