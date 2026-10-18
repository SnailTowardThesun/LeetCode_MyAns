//
// Created by hankun on 2026/10/18.
//

// LeetCode 153. 寻找旋转排序数组中的最小值
//
// @题目描述:
// 升序数组（元素互异）在未知下标处旋转过（如 [4,5,6,7,0,1,2]），求其中的最小值。
//
// @示例:
// 输入：nums = [4,5,6,7,0,1,2]
// 输出：0
//
// 思路：只比较 nums[mid] 与 nums[right]：
//       - nums[mid] > nums[right]：mid 处于旋转前的"高段"，最小值必在 mid 右侧（mid 本身不可能是最小），
//         left = mid + 1；
//       - nums[mid] < nums[right]：[mid, right] 有序，最小值在 mid 或 mid 左侧，right = mid
//         （不能写 mid - 1，mid 本身可能就是最小值）。
//       循环用 left < right，退出时 left == right 即最小值下标。

#include <gtest/gtest.h>

using namespace std;

namespace {
class Solution {
   public:
    int findMin(vector<int>& nums) {
        int left = 0;
        int right = nums.size() - 1;
        while (left < right) {
            int mid = (left + right) / 2;
            if (nums[mid] > nums[right]) {
                // 最小值严格在 mid 右侧
                left = mid + 1;
            } else {
                // 最小值在 mid 或 mid 左侧，mid 不能丢
                right = mid;
            }
        }

        return nums[left];
    }
};
}  // namespace

TEST(Top150, 153) {
    Solution s;
    vector<int> t1{4, 5, 6, 7, 0, 1, 2};
    EXPECT_EQ(s.findMin(t1), 0);
    vector<int> t2{2, 0, 1};  // 旋转点恰好落在首次 mid 上
    EXPECT_EQ(s.findMin(t2), 0);
    vector<int> t3{5, 1, 2, 3, 4};
    EXPECT_EQ(s.findMin(t3), 1);
    vector<int> t4{1, 2, 3};  // 不旋转
    EXPECT_EQ(s.findMin(t4), 1);
    vector<int> t5{2, 1};
    EXPECT_EQ(s.findMin(t5), 1);
    vector<int> t6{1};  // 单元素
    EXPECT_EQ(s.findMin(t6), 1);
}
