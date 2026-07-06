// @题目描述:
// 给你一个整数 n。将 n 中所有的非零数字按照它们的原始顺序连接起来，形成一个新的整数 x。
// 如果不存在非零数字，则 x = 0。sum 为 x 中所有数字的数字和。返回 x * sum 的值。
//
// @示例:
// 示例 1：
// 输入：n = 10203004
// 输出：12340
// 解释：非零数字是 1、2、3 和 4。因此，x = 1234。数字和为 sum = 1 + 2 + 3 + 4 = 10。
//       因此，答案是 x * sum = 1234 * 10 = 12340。
//
// 示例 2：
// 输入：n = 1000
// 输出：1
// 解释：非零数字是 1，因此 x = 1 且 sum = 1。因此，答案是 x * sum = 1 * 1 = 1。
//
// @解题思路:
// 1. 将整数 n 转换为字符串，遍历每个字符
// 2. 如果字符不是 '0'，将其添加到结果字符串中，并累加到数字和中
// 3. 将结果字符串转换为整数 x
// 4. 返回 x * sum
//
// 复杂度分析：
// - 时间复杂度：O(log n)，n 的十进制位数
// - 空间复杂度：O(log n)，存储结果字符串

#include <gtest/gtest.h>

#include <string>

using namespace std;

class Solution {
   public:
    long long sumAndMultiply(int n) {
        if (n == 0) {
            return 0;
        }
        string fin_str = "";
        long long step = 0;
        string num_str = to_string(n);
        for (auto& c : num_str) {
            if (c != '0') {
                fin_str += c;
                step += c - '0';
            }
        }
        return stoll(fin_str) * step;
    }
};

TEST(Daily, 3754) {
    Solution s;

    int n = 10203004;
    long long ret = s.sumAndMultiply(n);
    EXPECT_EQ(12340, ret);

    n = 1000;
    ret = s.sumAndMultiply(n);
    EXPECT_EQ(1, ret);

    n = 0;
    ret = s.sumAndMultiply(n);
    EXPECT_EQ(0, ret);
}
