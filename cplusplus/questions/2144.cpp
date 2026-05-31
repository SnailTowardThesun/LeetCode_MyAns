//
// @题目描述: 一家商店在卖糖果，每买两个糖果，商店会送一个免费的糖果。
//           免费糖果的价格必须不超过所购买的两个糖果中价格最低的那个。
//           给定一个整数数组 cost，其中 cost[i] 是第 i 个糖果的价格。
//           请返回购买所有糖果的最小成本。
//
// @示例: 输入: cost = [6,5,7,9,2,2]
//        输出: 23
//        解释: 购买价格为9和7的糖果，免费获得价格为6的糖果；
//             购买价格为5和2的糖果，免费获得价格为2的糖果；
//             总花费为 9+7+5+2 = 23
//
// @解题思路: 为了最小化成本，我们希望免费获得的糖果价格尽可能高。
//            因此将糖果价格按升序排序，然后从最贵的开始，每三个糖果为一组：
//            - 购买前两个（最贵的）
//            - 第三个（最便宜的）免费
//            从排序后的数组末尾开始，每隔三个取一个减去即可。
//            时间复杂度: O(n log n)，空间复杂度: O(1)
//
// Created by hankun on 6/1/26.
//

#include <gtest/gtest.h>
#include <vector>
using namespace std;

class Solution {
public:
    int minimumCost(vector<int>& cost) {
        int ret = 0;
        for (auto i : cost) {
            ret += i;
        }

        if (cost.size() <= 2) {
            return ret;
        }

        std::sort(cost.begin(), cost.end());
        for (int i = cost.size() - 3; i >= 0; i-=3) {
            ret -= cost[i];
        }

        return ret;
    }
};

TEST(Daily, 2144) {
    vector<int>cost{1,2,3};
    Solution s;
    auto ret = s.minimumCost(cost);
    EXPECT_EQ(5, ret);
}