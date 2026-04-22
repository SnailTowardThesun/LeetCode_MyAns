// 题目：2615. 等值距离和
// 描述：给你一个下标从 0 开始的整数数组 nums 。对于每个下标 i（0 <= i < nums.length），
//       计算其对应 nums[i] 的所有下标 j 的绝对差之和，其中 j != i 且 nums[j] == nums[i] 。
//       返回一个整数数组 answer，其中 answer[i] 是上述差之和。
// 示例：
// 输入：nums = [1,3,1,1,2]
// 输出：[5,0,3,4,0]
// 解释：
// - i=0: 另一个 1 在下标 2, 3 处。|0-2| + |0-3| = 2 + 3 = 5
// - i=1: 只有一个 3，所以和为 0
// - i=2: 另一个 1 在下标 0, 3 处。|2-0| + |2-3| = 2 + 1 = 3
// - i=3: 另一个 1 在下标 0, 2 处。|3-0| + |3-2| = 3 + 1 = 4
// - i=4: 只有一个 2，所以和为 0

#include <gtest/gtest.h>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<long long> distance(vector<int>& nums) {
        // 使用哈希表存储每个数值对应的所有下标
        unordered_map<int, std::vector<long long>> container;
        for (long long i = 0 ; i < nums.size(); ++i) {
            container[nums[i]].push_back(i);
        }

        std::vector<long long> ret(nums.size(), 0);
        // 对每个数值的下标列表计算距离和
        for (auto &it : container) {
            // 如果只有一个下标，距离和为0
            if (it.second.size() == 1) {
                continue;
            }

            // 计算所有下标的总和
            long long total_sum = 0;
            for (auto &iit: it.second) {
                total_sum += iit;
            }

            // 前缀和，用于快速计算左侧距离和
            long long prefix_sum = 0;
            for (int i = 0; i < it.second.size(); ++i) {
                auto cidx = it.second[i];
                // 左侧距离和：i个元素，每个元素到cidx的距离和
                auto left = i * cidx - prefix_sum;
                // 右侧距离和：总长度-1-i个元素，每个元素到cidx的距离和
                long long suffix_sum = total_sum - prefix_sum - cidx;
                long long right = suffix_sum - (it.second.size() - 1 - i) * cidx;

                ret[cidx] = left + right;

                prefix_sum += it.second[i];
            }

        }

        return ret;
    }
};

TEST(Daily, 2615) {
    Solution s;
    // 测试用例1：基本示例
    auto nums1 = vector<int>{1,3,1,1,2};
    auto ret1= s.distance(nums1);
    EXPECT_EQ(ret1.size(), 5);
    EXPECT_EQ(ret1[0], 5);
    EXPECT_EQ(ret1[1], 0);
    EXPECT_EQ(ret1[2], 3);
    EXPECT_EQ(ret1[3], 4);
    EXPECT_EQ(ret1[4], 0);

    // 测试用例2：所有元素相同
    auto nums2 = vector<int>{2,2,2,2};
    auto ret2= s.distance(nums2);
    EXPECT_EQ(ret2.size(), 4);
    EXPECT_EQ(ret2[0], 6); // |0-1| + |0-2| + |0-3| = 1+2+3=6
    EXPECT_EQ(ret2[1], 4); // |1-0| + |1-2| + |1-3| = 1+1+2=4
    EXPECT_EQ(ret2[2], 4); // |2-0| + |2-1| + |2-3| = 2+1+1=4
    EXPECT_EQ(ret2[3], 6); // |3-0| + |3-1| + |3-2| = 3+2+1=6

    // 测试用例3：所有元素都不同
    auto nums3 = vector<int>{1,2,3,4,5};
    auto ret3= s.distance(nums3);
    EXPECT_EQ(ret3.size(), 5);
    for (auto val : ret3) {
        EXPECT_EQ(val, 0);
    }
}
