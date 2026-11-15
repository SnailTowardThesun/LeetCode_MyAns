// @题目描述:
// 给你一个整数数组 arr，返回其中和为奇数的子数组的数目。由于答案可能很大，
// 请返回它对 10^9 + 7 取余的结果。
//
// @示例:
// 输入：arr = [1,3,5]
// 输出：4（奇数和子数组为 [1]、[3]、[5]、[1,3,5]）
// 输入：arr = [2,4,6]
// 输出：0
// 输入：arr = [1,2,3,4,5,6,7]
// 输出：16
//
// @解题思路:
// 前缀和奇偶配对计数（与 560 同款套路，把「等值查询」换成「奇偶差查询」）：
// 1. 子数组 nums[i..j] 的和 = s[j+1] - s[i]（前缀和，s[0] = 0），
//    和为奇数 <=> 两个前缀和奇偶性不同；
// 2. 扫描每个前缀和只记奇偶：当前为偶时，与此前所有奇前缀配对出奇和子数组，
//    反之亦然——只需 odd/even 两个计数器；
// 3. even 初值 1：空前缀 s[0] = 0 是偶数，漏掉它「从下标 0 开始的奇和子数组」
//    就查不到；
// 4. 答案上限约 n^2/2 ≈ 5*10^9 > INT_MAX，必须用 int64_t 累计、最后取模。
//
// 复杂度分析：
// - 时间复杂度：O(n)，一趟扫描
// - 空间复杂度：O(1)，三个计数器

#include <gtest/gtest.h>

#include <cstdint>
#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    int numOfSubarrays(vector<int>& arr) {
        const int64_t MODULO = 1000000007;

        int64_t result = 0;
        int64_t prefix = 0;
        int64_t odd = 0, even = 1;  // even 初值 1：空前缀 s[0]=0 计为偶

        for (auto i : arr) {
            prefix += i;
            if (prefix % 2 == 0) {
                result += odd;  // 偶前缀 - 奇前缀 = 奇和子数组
                even += 1;
            } else {
                result += even;  // 奇前缀 - 偶前缀 = 奇和子数组
                odd += 1;
            }
        }

        return static_cast<int>(result % MODULO);
    }
};
}  // namespace

TEST(Daily, 1524) {
    Solution s;

    // 官方示例
    vector<int> arr1{1, 3, 5};
    EXPECT_EQ(s.numOfSubarrays(arr1), 4);
    vector<int> arr2{2, 4, 6};
    EXPECT_EQ(s.numOfSubarrays(arr2), 0);
    vector<int> arr3{1, 2, 3, 4, 5, 6, 7};
    EXPECT_EQ(s.numOfSubarrays(arr3), 16);

    // 最小规模：单个奇数 / 单个偶数
    vector<int> arr4{1};
    EXPECT_EQ(s.numOfSubarrays(arr4), 1);
    vector<int> arr5{2};
    EXPECT_EQ(s.numOfSubarrays(arr5), 0);

    // 混合奇偶：[1] 与 [1,2]（和 3）两段
    vector<int> arr6{1, 2};
    EXPECT_EQ(s.numOfSubarrays(arr6), 2);

    // 大数取模：1e5 个 1（期望值经暴力+公式双重核对）
    vector<int> big(100000, 1);
    EXPECT_EQ(s.numOfSubarrays(big), 500049986);
}
