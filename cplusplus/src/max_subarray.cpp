/*
 * Find the contiguous subarray within an array (containing at least one number) which has the largest sum.
 * For example, given the array [-2,1,-3,4,-1,2,1,-5,4],
 * the contiguous subarray [4,-1,2,1] has the largest sum = 6.
 */

#include <iostream>
#include <vector>
using namespace std;

class MaxSub
{
public:
    MaxSub() {};
    virtual ~MaxSub() {};
public:
    int maxSubArray(vector<int>& nums) {
            int global = nums[0];
            int local = nums[0];
            int size = nums.size();
            for(int i=1;i<size;i++)
            {
                    local = nums[i] > local+nums[i] ? nums[i] : local+nums[i];
                    global = local > global ? local : global;
            }
            return global;
    }
};