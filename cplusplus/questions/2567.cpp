// @题目描述:
// 给你一个下标从 0 开始的整数数组 nums。nums 的分数是 nums 中最大元素和
// 最小元素的差值。你需要恰好修改两个元素（可以改成任意值，包括当前已有的值），
// 返回修改后 nums 的最小分数。n >= 3，修改后数组大小不变。
//
// @示例:
// 输入：nums = [1,4,3]
// 输出：0（把 1 和 4 改成 3，极差 0）
// 输入：nums = [1,4,7,8,5]
// 输出：3（把 8 和 1 改成 5，[5,4,7,5,5] 极差 7-4 = 3）
//
// @解题思路:
// 排序 + 三种删法取最小：
// 1. 关键转化：把元素改成「保留元素中的某个值」最优，问题等价于
//    「删掉恰好两个元素，最小化剩余极差」；
// 2. 删两个元素的最优方案必是三种之一（排序后）：
//    - 删最大的两个：极差 nums[n-3] - nums[0]
//    - 删最大和最小：极差 nums[n-2] - nums[1]
//    - 删最小的两个：极差 nums[n-1] - nums[2]
//    （删中间元素不影响 min/max，不会更优）
// 3. 三者取最小即为答案。
//
// 复杂度分析：
// - 时间复杂度：O(n log n)，排序主导
// - 空间复杂度：O(1)

#include <gtest/gtest.h>

#include <algorithm>
#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int minimizeSum(vector<int>& nums) {
        int n = nums.size();
        sort(nums.begin(), nums.end());
        // 三种删法：删两个最大 / 删一大一最小 / 删两个最小
        return min(nums[n - 3] - nums[0], min(nums[n - 2] - nums[1], nums[n - 1] - nums[2]));
    }
};
}  // namespace

TEST(Daily, 2567) {
    Solution s;

    // 官方示例
    vector<int> nums1{1, 4, 3};
    EXPECT_EQ(s.minimizeSum(nums1), 0);
    vector<int> nums2{1, 4, 7, 8, 5};
    EXPECT_EQ(s.minimizeSum(nums2), 3);

    // 全相等：极差本就是 0
    vector<int> nums3{1, 1, 1};
    EXPECT_EQ(s.minimizeSum(nums3), 0);

    // 最小规模 n=3：必可全改成同一个值，答案恒 0
    vector<int> nums4{1, 2, 3};
    EXPECT_EQ(s.minimizeSum(nums4), 0);

    // n=4（期望值由暴力对照机器算出）
    vector<int> nums5{1, 2, 3, 4};
    EXPECT_EQ(s.minimizeSum(nums5), 1);

    // 两端离群、中间密集：砍掉两端后极差 0
    vector<int> nums6{100, 1, 50};
    EXPECT_EQ(s.minimizeSum(nums6), 0);
}
