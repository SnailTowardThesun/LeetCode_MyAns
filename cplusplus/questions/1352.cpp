// @题目描述
// ProductOfNumbers 维护一个初始为空的整数流。add(num) 追加一个 0 到 100 的整数，
// getProduct(k) 返回最近 k 个数的乘积。查询时已有至少 k 个数，任意连续段的乘积均适合 32 位有符号整数。
// 两种操作合计最多调用 40000 次，1 <= k <= 40000。
//
// @示例
// 依次加入 3、0、2、5、4，最近 2、3、4 个数的乘积分别为 20、40、0。再加入 8，最近 2 个数的乘积为 32。
//
// @解题思路
// 从最近一个零之后重新计算前缀积。首项 1 表示空前缀的乘积，后续每项等于上一项乘以新数。
// 若 k 大于非零段长度，查询范围含零。否则用当前前缀积除以 k 个数之前的前缀积，得到精确的整数商。
// add 均摊 O(1)，getProduct 为 O(1)。累计加入 n 个数时，最坏空间为 O(n)。

#include <gtest/gtest.h>

#include <utility>
#include <vector>

namespace {
class ProductOfNumbers {
   public:
    std::vector<int> container{1};

    void add(int num) {
        if (num == 0) {
            container = std::vector<int>{1};
        } else {
            container.emplace_back(container.back() * num);
        }
    }

    int getProduct(int k) {
        if (std::cmp_greater_equal(k, container.size())) {
            return 0;
        }
        return container.back() / container[container.size() - 1 - k];
    }
};
}  // namespace

TEST(Daily, 1352) {
    ProductOfNumbers stream;
    stream.add(3);
    EXPECT_EQ(stream.getProduct(1), 3);
    stream.add(0);
    EXPECT_EQ(stream.getProduct(1), 0);
    stream.add(2);
    stream.add(5);
    stream.add(4);
    EXPECT_EQ(stream.getProduct(2), 20);
    EXPECT_EQ(stream.getProduct(3), 40);
    EXPECT_EQ(stream.getProduct(4), 0);
    EXPECT_EQ(stream.getProduct(5), 0);
    stream.add(8);
    EXPECT_EQ(stream.getProduct(2), 32);

    stream.add(0);
    stream.add(0);
    stream.add(1);
    EXPECT_EQ(stream.getProduct(1), 1);
    EXPECT_EQ(stream.getProduct(2), 0);
}
