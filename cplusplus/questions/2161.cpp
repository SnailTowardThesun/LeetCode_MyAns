//
// Created by hankun on 6/8/26.
//

/**
 * @file 2161.cpp
 * @brief LeetCode 2161. Partition Array According to Given Pivot（根据给定的枢轴分割数组）
 *
 * @题目描述
 * 给你一个下标从 0 开始的整数数组 nums 和一个整数 pivot。
 * 请你将 nums 重新排列，使得以下条件均成立：
 *
 * 1. 所有小于 pivot 的元素都出现在所有大于 pivot 的元素之前。
 * 2. 所有等于 pivot 的元素都出现在小于和大于 pivot 的元素之间。
 * 3. 小于 pivot 的元素之间和大于 pivot 的元素之间的相对顺序保持不变。
 *
 * 请你返回重新排列后的数组。
 *
 * @示例
 * 示例 1：
 * 输入：nums = [9,12,5,10,14,3,10], pivot = 10
 * 输出：[9,5,3,10,10,12,14]
 * 解释：
 * 小于 10 的元素是 [9,5,3]，它们按原顺序出现在数组开头。
 * 等于 10 的元素是 [10,10]，它们出现在中间。
 * 大于 10 的元素是 [12,14]，它们按原顺序出现在数组末尾。
 *
 * 示例 2：
 * 输入：nums = [-3,4,3,2], pivot = 2
 * 输出：[-3,2,4,3]
 *
 * @解题思路
 * 1. 双指针法：
 *    - 创建一个结果数组，初始值全为 pivot
 *    - 使用两个指针：pre 从前往后填充小于 pivot 的元素，
 *      last 从后往前填充大于 pivot 的元素
 *    - 最后将大于 pivot 的部分反转，保持相对顺序
 *
 * 2. 算法步骤：
 *    - 初始化结果数组，大小与 nums 相同，初始值全为 pivot
 *    - pre 指针从 0 开始，last 指针从 nums.size()-1 开始
 *    - 遍历原数组，将小于 pivot 的元素放入 pre 位置，pre 后移
 *    - 将大于 pivot 的元素放入 last 位置，last 前移
 *    - 最后将大于 pivot 的部分反转，保持相对顺序
 *
 * 3. 复杂度分析：
 *    - 时间复杂度: O(n)，需要遍历数组两次（一次构建，一次反转）
 *    - 空间复杂度: O(n)，需要额外的数组存储结果
 */

#include <gtest/gtest.h>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
public:
    vector<int> pivotArray(vector<int> &nums, int pivot) {
        int pre = 0;
        int last = nums.size() - 1;
        vector<int> ret(nums.size(), pivot);
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] > pivot) {
                ret[last--]=nums[i];
            } else if (nums[i] < pivot) {
                ret[pre++]=nums[i];
            }
        }

        // reverse last
        std::reverse(ret.begin() + last+1, ret.end());

        return ret;
    }
};

TEST(Daily, 2161) {
    Solution s;
    vector<int> nums{9, 12, 5, 10, 14, 3, 10};
    int pivot = 10;
    auto ret = s.pivotArray(nums, pivot);
    EXPECT_EQ(ret[0], 9);
}
