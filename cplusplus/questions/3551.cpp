// @题目描述:
// 给你一个由互不相同的正整数组成的数组 nums。
// 你需要根据每个数字的数位和将数组升序排序；
// 若两个数字的数位和相同，则较小的数字排在前面。
// 返回将 nums 重排为该顺序所需的最小交换次数。
// 一次交换指交换数组中两个不同位置上的值。
// 数据范围：1 <= nums.length <= 10^5，1 <= nums[i] <= 10^9。
//
// @示例:
// 输入: nums = [37,100]
// 输出: 1
// 解释: 数位和分别为 [10,1]，目标顺序为 [100,37]，交换一次即可。
//
// 输入: nums = [18,43,34,16]
// 输出: 2
// 解释: 数位和分别为 [9,7,7,7]，目标顺序为 [16,34,43,18]，
//       交换 18 与 16、43 与 34 即可。
//
// @解题思路:
// 排序 + 置换环分解：
// 1. 为每个数字计算三元组「数位和、数值、原下标」；
// 2. 按数位和升序、数值升序排序，得到目标排列；
// 3. 目标排列与原数组之间形成一个置换。把置换拆成若干环，
//    长度为 k 的环最少需要 k-1 次交换；
// 4. 用 visited 标记访问过的下标并遍历所有环，累计 len-1。
//
// 复杂度分析：
// - 时间复杂度：O(n log n)，瓶颈是排序
// - 空间复杂度：O(n)，存储三元组和访问标记
//

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int minSwaps(vector<int>& nums) {
        auto digitSum = [](int n) {
            int sum = 0;
            while (n != 0) {
                sum += n % 10;
                n /= 10;
            }
            return sum;
        };

        int n = nums.size();
        vector<array<int, 3>> container;
        container.reserve(n);
        for (int i = 0; i < n; i++) {
            container.emplace_back(array<int, 3>{digitSum(nums[i]), nums[i], i});
        }

        sort(container.begin(), container.end(), [](const array<int, 3>& a, const array<int, 3>& b) {
            if (a[0] == b[0]) {
                return a[1] < b[1];
            }

            return a[0] < b[0];
        });

        int ret = 0;
        vector<bool> visited(n, false);
        for (int i = 0; i < n; i++) {
            if (visited[i]) {
                continue;
            }

            int len = 0;
            for (int j = i; !visited[j]; j = container[j][2]) {
                visited[j] = true;
                ++len;
            }

            ret += len - 1;
        }

        return ret;
    }
};
}  // namespace


TEST(Daily, 3551) {
    Solution s;

    // 官方示例 1：数位和 [10,1]，目标顺序 [100,37]
    vector<int> nums1 = {37, 100};
    EXPECT_EQ(1, s.minSwaps(nums1));

    // 官方示例 2：数组已按数位和有序，无需交换
    vector<int> nums2 = {22, 14, 33, 7};
    EXPECT_EQ(0, s.minSwaps(nums2));

    // 官方示例 3：相同数位和按数值排序，交换 18/16、43/34
    vector<int> nums3 = {18, 43, 34, 16};
    EXPECT_EQ(2, s.minSwaps(nums3));

    // 一个长度为 4 的置换环，最少需要 3 次交换
    vector<int> nums4 = {277993448, 416038674, 616955867, 539372283};
    EXPECT_EQ(3, s.minSwaps(nums4));
}
