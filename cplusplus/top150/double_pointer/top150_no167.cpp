//
// @题目描述: 给你一个已按升序排列的整数数组 numbers 和一个目标值 target。
//            数组中存在两个数，它们的和等于目标值。
//            返回这两个数的下标（按1-indexed），假设只存在唯一答案。
//
// @示例: 输入: numbers = [2,7,11,15], target = 9
//        输出: [1,2]
//        解释: numbers[0] + numbers[1] = 2 + 7 = 9
//
// @解题思路: 利用数组已排序的特性，使用双指针从两端向中间遍历。
//            如果两数之和等于target，直接返回下标。
//            如果小于target，说明需要更大的和，左指针右移。
//            如果大于target，说明需要更小的和，右指针左移。
//            时间复杂度: O(n)，空间复杂度: O(1)
//
// Created by hankun on 5/31/26.
//

#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> twoSum(vector<int>& numbers, int target) {
        vector<int> result;
        int pre = 0, last = numbers.size() - 1;
        while (pre < last) {
            if (numbers[pre] + numbers[last] == target) {
                return vector<int>{pre, last};
            }

            if (numbers[pre] + numbers[last] < target) {
                pre++;
            } else {
                last--;
            }
        }

        return result;
    }
};

TEST(top150, 167) {
    auto numbers = vector<int>{2,7,11,15};
    auto target = 9;
    Solution s;
    auto ret = s.twoSum(numbers, target);
    EXPECT_EQ(ret[0], 0);
    EXPECT_EQ(ret[1], 1);
}