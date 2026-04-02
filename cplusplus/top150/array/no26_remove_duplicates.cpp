/**
 * @file no26_remove_duplicates.cpp
 * @brief LeetCode 26. 删除有序数组中的重复项
 *
 * @题目描述
 * 给你一个非严格递增排列的数组 nums，请你原地删除重复出现的元素，使每个元素只出现一次，
 * 返回删除后数组的新长度。元素的相对顺序应该保持一致。然后返回 nums 中唯一元素的个数。
 * 考虑 nums 的唯一元素的数量为 k，你需要做以下事情确保你的题解可以被通过：
 * - 更改数组 nums，使 nums 的前 k 个元素包含唯一元素，并按照它们最初在 nums 中出现的顺序排列。
 * - nums 的其余元素与 nums 的大小不重要。
 * - 返回 k。
 *
 * @示例
 * 示例 1：
 * 输入: nums = [1,1,2]
 * 输出: 2, nums = [1,2,_]
 * 解释: 函数应该返回新的长度 2，并且原数组 nums 的前两个元素被修改为 1, 2。
 *      不需要考虑数组中超出新长度后面的元素。
 *
 * 示例 2：
 * 输入: nums = [0,0,1,1,1,2,2,3,3,4]
 * 输出: 5, nums = [0,1,2,3,4]
 * 解释: 函数应该返回新的长度 5，并且原数组 nums 的前五个元素被修改为 0, 1, 2, 3, 4。
 *      不需要考虑数组中超出新长度后面的元素。
 *
 * @解题思路
 * 1. 双指针法：
 *    - 慢指针指向当前已处理的不重复元素的下一个位置
 *    - 快指针遍历数组，寻找下一个不重复元素
 *    - 当快指针找到与慢指针前一个元素不同的元素时，将其复制到慢指针位置
 *
 * 2. 迭代器法：
 *    - 使用迭代器遍历数组
 *    - 当发现当前元素与下一个元素相同时，删除当前元素
 *    - 注意处理迭代器失效问题
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，需要遍历数组一次
 * - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(TOP150, No26_RemoveDuplicatesFromSortedArray) {
    class Solution {
    public:
        int remove_duplicates(vector<int>& nums) {
            for (auto it = nums.begin(); it != nums.end() - 1;) {
                if (*it == *(it + 1)) {
                    it = nums.erase(it);
                } else {
                    it++;
                }
            }

            return nums.size();
        }
    };

    Solution solution;
    std::vector<int> nums{1, 1, 2};
    auto ret = solution.remove_duplicates(nums);
    assert(ret == 2);
}
