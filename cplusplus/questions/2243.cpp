// @题目描述:
// 给你一个由若干数字字符（0-9）组成的字符串 s 和一个整数 k。
// 如果 s 的长度大于 k，可以执行一轮操作：把 s 分割成长度为 k 的连续组
// （最后一组长度可能小于 k），再用每组数字之和组成的新字符串替换 s。
// 不断执行直到 s 的长度小于等于 k，返回最终的 s。
// 注意：组的和可能超过一位数（如 9+9=18），它以十进制形式拼进新串，
// 下一轮分组按新串的「字符」重新划分——多 digit 和会被拆开重组。
//
// @示例:
// 输入：s = "11111222223", k = 3
// 输出："135"（第一轮 111|112|222|23 -> 3+4+6+5 = "3465"；第二轮 346|5 -> "135"）
// 输入：s = "00000000", k = 3
// 输出："000"
//
// @解题思路:
// 按题意模拟：
// 1. arr 存当前串每位数字；len(s) <= k 时直接返回原串；
// 2. 每轮按 k 连续分组求和，拼成新串后重新逐位解析——和可能是两位数，
//    下一轮的分组对象是新串的字符而非「和」，必须回到逐位表示；
// 3. 每轮长度约缩减为原来的 1/k，轮数 O(log_k n)。
//
// 复杂度分析：
// - 时间复杂度：O(n·log_k n)，每轮 O(n)
// - 空间复杂度：O(n)

#include <gtest/gtest.h>

#include <string>
#include <vector>

using namespace std;

// 匿名命名空间：提供内部链接，避免与其他题解文件中同名 Solution 的 ODR 冲突
namespace {
class Solution {
   public:
    string digitSum(string s, int k) {
        auto ret = s;
        vector<int> arr;
        for (auto i : ret) {
            arr.emplace_back(i - '0');
        }

        while (ret.size() > k) {
            ret = "";
            for (int i = 0; i < arr.size(); i += k) {
                int sum = 0;
                for (int j = i; j < i + k && j < arr.size(); j++) {
                    sum += arr[j];
                }

                ret += to_string(sum);  // 和可能两位数，多位拼入新串
            }

            arr.clear();
            for (auto j : ret) {
                arr.emplace_back(j - '0');  // 按新串逐位重新解析
            }
        }

        return ret;
    }
};
}  // namespace

TEST(Daily, 2243) {
    Solution s;

    // 官方示例
    EXPECT_EQ(s.digitSum("11111222223", 3), "135");
    EXPECT_EQ(s.digitSum("00000000", 3), "000");

    // 多位数和级联：经历 6 轮才收敛（期望值由参考实现机器算出）
    EXPECT_EQ(s.digitSum("01234567890", 2), "27");

    // 长度本就不超过 k：原样返回
    EXPECT_EQ(s.digitSum("1234", 4), "1234");
    EXPECT_EQ(s.digitSum("1", 2), "1");

    // 大和触发两位数拆分重组
    EXPECT_EQ(s.digitSum("999999999", 3), "36");
}
