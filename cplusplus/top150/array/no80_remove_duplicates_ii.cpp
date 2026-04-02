/**
 * @file no80_remove_duplicates_ii.cpp
 * @brief LeetCode 80. 删除有序数组中的重复项 II
 *
 * @题目描述
 * 给你一个有序数组 nums，请你原地删除重复出现的元素，使得出现次数超过两次的元素只出现两次，
 * 返回删除后数组的新长度。不要使用额外的数组空间，你必须在原地修改输入数组并在使用 O(1)
 * 额外空间的条件下完成。
 *
 * @示例
 * 示例 1：
 * 输入: nums = [1,1,1,2,2,3]
 * 输出: 5, nums = [1,1,2,2,3,_]
 * 解释: 函数应返回新长度 length = 5，并且原数组的前五个元素被修改为 1, 1, 2, 2, 3。
 *      不需要考虑数组中超出新长度后面的元素。
 *
 * 示例 2：
 * 输入: nums = [0,0,1,1,1,1,2,3,3]
 * 输出: 7, nums = [0,0,1,1,2,3,3]
 * 解释: 函数应返回新长度 length = 7，并且原数组的前七个元素被修改为 0, 0, 1, 1, 2, 3, 3。
 *      不需要考虑数组中超出新长度后面的元素。
 *
 * @解题思路
 * 1. 通用解法（允许最多 k 次重复）：
 *    - 使用计数器记录当前元素出现次数
 *    - 当计数器超过 2 时，删除多余元素
 *
 * 2. 双指针优化法：
 *    - 慢指针指向当前可以写入的位置
 *    - 快指针遍历数组
 *    - 当快指针指向的元素与慢指针前第二个元素不同时，说明可以保留
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，需要遍历数组一次
 * - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(TOP150, No80_RemoveDuplicatesII) {
    class Solution {
    public:
        int remove_duplicates(vector<int>& nums) {
            for (auto it = nums.begin(); it < nums.end() - 2;) {
                if (*it == *(it + 2)) {
                    it + 2 = nums.erase(it + 2);
                } else {
                    it++;
                }
            }
            return nums.size();
        }
    };

    Solution solution;

    std::vector<int> nums{1, 1, 1, 2, 2, 3};
    auto ret = solution.remove_duplicates(nums);

    EXPECT_EQ(ret, 5);
}
