/**
 * @file top150_no27_remove_element.cpp
 * @brief LeetCode 27. 移除元素
 *
 * @题目描述
 * 给你一个数组 nums 和一个值 val，你需要原地移除所有数值等于 val 的元素，
 * 并返回移除后数组的新长度。不要使用额外的数组空间，你必须仅使用 O(1) 额外空间
 * 并原地修改输入数组。元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
 *
 * @示例
 * 示例 1：
 * 输入: nums = [3,2,2,3], val = 3
 * 输出: 2, nums = [2,2,_,_]
 * 解释: 函数应该返回新的长度 2，并且 nums 中的前两个元素均为 2。
 *      你不需要考虑数组中超出新长度后面的元素。
 *
 * 示例 2：
 * 输入: nums = [0,1,2,2,3,0,4,2], val = 2
 * 输出: 5, nums = [0,1,4,0,3,_,_,_]
 * 解释: 函数应该返回新的长度 5，并且 nums 中的前五个元素为 0, 1, 3, 0, 4。
 *      注意这五个元素可为任意顺序。你不需要考虑数组中超出新长度后面的元素。
 *
 * @解题思路
 * 1. 双指针法（快慢指针）：
 *    - 快指针遍历整个数组
 *    - 慢指针指向当前可以放置非 val 元素的位置
 *    - 当快指针指向的元素不等于 val 时，将其复制到慢指针位置，慢指针前进
 *
 * 2. 迭代器法：
 *    - 使用 vector 的 erase 方法直接删除元素
 *    - 注意 erase 会返回下一个有效迭代器
 *
 * @复杂度分析
 * - 时间复杂度: O(n)，需要遍历数组一次
 * - 空间复杂度: O(1)，只使用常数额外空间
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

TEST(TOP150, No27_RemoveElement) {
    class Solution {
    public:
        int remove_element(vector<int>& nums, int val) {
            for (auto it = nums.begin(); it != nums.end();) {
                if (*it == val) {
                    it = nums.erase(it);
                } else {
                    it++;
                }
            }

            return nums.size();
        }
    };

    Solution solution;

    vector<int> nums{3, 2, 2, 3};
    int val = 3;

    int k = solution.remove_element(nums, val);

    cout << k << std::endl;
}
