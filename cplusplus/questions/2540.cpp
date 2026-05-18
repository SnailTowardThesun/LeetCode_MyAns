//
// Created by hankun on 5/19/26.
//

/**
 * @题目描述
 * 2540. 最小公共值
 * 给你两个整数数组 nums1 和 nums2，它们已经按非降序排序，请你返回两个数组的最小公共整数。
 * 如果两个数组没有公共整数，返回 -1。
 *
 * @示例
 * 示例 1:
 * 输入: nums1 = [1,2,3], nums2 = [2,4]
 * 输出: 2
 * 解释: 最小的公共整数是 2。
 *
 * 示例 2:
 * 输入: nums1 = [1,2,3,6], nums2 = [2,3,4,5]
 * 输出: 2
 * 解释: 公共整数有 2,3，最小的是 2。
 *
 * 示例 3:
 * 输入: nums1 = [6,7,8,9], nums2 = [1,2,3,10]
 * 输出: -1
 * 解释: 没有公共整数。
 *
 * @解题思路
 * 双指针法：
 * 1. 两个指针分别指向两个数组的开头
 * 2. 比较当前指针指向的元素：
 *    - 如果相等，返回该元素（因为数组已排序，这是最小公共值）
 *    - 如果 nums1[i] < nums2[j]，移动 nums1 的指针
 *    - 否则，移动 nums2 的指针
 * 3. 任意数组遍历完仍未找到，返回 -1
 *
 * 时间复杂度: O(m + n)，其中 m 和 n 是两个数组的长度
 * 空间复杂度: O(1)
 */

#include <gtest/gtest.h>
#include <vector>

using namespace std;

class Solution {
public:
    int getCommon(vector<int>& nums1, vector<int>& nums2) {
        int i = 0;
        int j = 0;
        while (i < nums1.size() && j < nums2.size()) {
            if (nums1[i] == nums2[j]) {
                return nums1[i];
            }

            if (nums1[i] < nums2[j]) {
                i++;
            } else {
                j++;
            }
        }

        return -1;
    }
};

TEST(Daily, 2540) {
    Solution s;

    // 测试用例 1：基本情况
    auto nums1 = vector<int>{1, 2, 3};
    auto nums2 = vector<int>{2, 4};
    EXPECT_EQ(s.getCommon(nums1, nums2), 2);

    // 测试用例 2：多个公共值
    auto nums3 = vector<int>{1, 2, 3, 6};
    auto nums4 = vector<int>{2, 3, 4, 5};
    EXPECT_EQ(s.getCommon(nums3, nums4), 2);

    // 测试用例 3：无公共值
    auto nums5 = vector<int>{6, 7, 8, 9};
    auto nums6 = vector<int>{1, 2, 3, 10};
    EXPECT_EQ(s.getCommon(nums5, nums6), -1);

    // 测试用例 4：公共值在开头
    auto nums7 = vector<int>{1, 3, 5};
    auto nums8 = vector<int>{1, 2, 4};
    EXPECT_EQ(s.getCommon(nums7, nums8), 1);

    // 测试用例 5：公共值在末尾
    auto nums9 = vector<int>{1, 2, 5};
    auto nums10 = vector<int>{3, 4, 5};
    EXPECT_EQ(s.getCommon(nums9, nums10), 5);

    // 测试用例 6：数组有重复元素
    auto nums11 = vector<int>{2, 2, 3};
    auto nums12 = vector<int>{2, 2, 4};
    EXPECT_EQ(s.getCommon(nums11, nums12), 2);
}