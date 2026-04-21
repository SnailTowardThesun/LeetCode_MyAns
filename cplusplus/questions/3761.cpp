//
// Created by 韩堃 on 2026/4/17.
//
// 3761. 最小镜像对距离
// 题目：https://leetcode.com/problems/minimum-mirror-reverse-distance/
// 题目描述：
// 描述：给定一个整数数组 nums，找到两个元素 nums[i] 和 nums[j]，使得 nums[i] 是 nums[j] 的镜像（即 nums[i]
// 的数字反转后等于 nums[j]），
//       且 |i - j| 最小。返回这个最小距离。如果不存在这样的镜像对，返回 -1。
//
// 解题思路：
// 1. 使用数学方法反转数字，避免前导零问题
// 2. 遍历数组，使用哈希表记录每个数字反转后的位置
// 3. 当遇到一个数字时，检查哈希表中是否存在该数字（即之前是否出现过其镜像数字）
// 4. 如果存在，计算距离并更新最小距离
// 5. 将当前数字的反转结果存入哈希表
//
// 时间复杂度：O(n)，其中 n 是数组的长度
// 空间复杂度：O(n)，用于存储哈希表

#include <gtest/gtest.h>

#include <climits>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
   public:
    int minMirrorPairDistance(vector<int>& nums) {
        // 定义反转数字的函数
        auto reverseNum = [](int x) {
            int y = 0;
            while (x > 0) {
                y = y * 10 + x % 10;
                x /= 10;
            }
            return y;
        };

        int n = nums.size();
        unordered_map<int, int> prev;
        int ans = n + 1;

        for (int i = 0; i < n; ++i) {
            int x = nums[i];
            // 检查当前数字是否在prev中（即之前是否出现过其镜像数字）
            if (prev.count(x)) {
                ans = min(ans, i - prev[x]);
            }
            // 将当前数字的反转结果存入prev，记录当前位置
            prev[reverseNum(x)] = i;
        }

        return ans == n + 1 ? -1 : ans;
    }
};

TEST(Daily, 3761) {
    Solution s;

    // 测试用例 1：基本情况
    auto nums1 = vector<int>{12, 21, 45, 33, 54};
    auto ret1 = s.minMirrorPairDistance(nums1);
    EXPECT_EQ(ret1, 1);  // 12 和 21 的距离是 1

    // 测试用例 2：包含前导零的情况
    auto nums2 = vector<int>{120, 21};
    auto ret2 = s.minMirrorPairDistance(nums2);
    EXPECT_EQ(ret2, 1);  // 120 的镜像就是 21，距离是 1

    // 测试用例 3：不存在镜像对的情况
    auto nums3 = vector<int>{12, 34, 56};
    auto ret3 = s.minMirrorPairDistance(nums3);
    EXPECT_EQ(ret3, -1);

    // 测试用例 4：包含多个相同数字的情况
    auto nums4 = vector<int>{12, 45, 21, 54, 12};
    auto ret4 = s.minMirrorPairDistance(nums4);
    EXPECT_EQ(ret4, 2);  // 12（位置0）和 21（位置2）的距离是 2

    // 测试用例 5：非互为镜像对的情况（21 和 120）
    auto nums5 = vector<int>{21, 120};
    auto ret5 = s.minMirrorPairDistance(nums5);
    EXPECT_EQ(ret5, -1);  // 21 的反转是 12，120 的反转是 21，不是互为镜像对
}
