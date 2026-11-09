// @题目描述:
// 你有 k 个服务器，编号为 0 到 k-1，它们可以同时处理多个请求组。每个服务器有无穷的
// 计算能力但是不能同时处理超过一个请求。请求分配到服务器的规则如下：
// - 第 i（序号从 0 开始）个请求到达时，如果所有服务器都已被占据，该请求被舍弃；
// - 如果第 (i % k) 个服务器空闲，那么对应服务器会处理该请求；
// - 否则，将请求安排给下一个空闲的服务器（服务器构成一个环，必要的话从第 0 个
//   服务器开始继续找下一个空闲的服务器）。
// 给定严格递增的正整数数组 arrival（第 i 个请求的到达时间）和数组 load（第 i 个
// 请求的工作量，即服务器完成它所需的时间），返回处理请求数最多的服务器编号列表
// （可能有多个，按编号升序返回）。
//
// @示例:
// 输入：k = 3, arrival = [1,2,3,4,5], load = [5,2,3,3,3]
// 输出：[1]
// 解释：前 3 个请求由服务器 0/1/2 依次处理；请求 3 到达时服务器 1 已空闲，接力
// 处理（共 2 个）；请求 4 到达时全部繁忙，被舍弃。服务器 1 最忙。
//
// @解题思路:
// 双小根堆模拟 + 空闲编号重定位技巧：
// 1. busy 堆按 (结束时间, 编号) 组织，请求 i 到达时先把结束时间 <= arrival[i] 的
//    服务器归还空闲堆；
// 2. 关键技巧：归还时把空闲编号 j 重定位为 i + ((j - i) % k + k) % k，即 >= i 且
//    与 j 同余 (mod k) 的最小值。这样空闲堆（小根堆）的堆顶就是从 i%k 开始环形
//    搜索遇到的第一个空闲服务器，弹出后对 k 取模还原真实编号；
//    注意 C++ 的 % 对负数是截断取余（与 Python 语义不同），必须 +k 再 %k 修正；
//    若误写成 i + j % k，空闲令牌会被认成别的服务器，计数全乱；
// 3. 空闲堆为空则丢弃该请求；否则弹出堆顶服务器，把 (到达时间+耗时, 编号) 压入
//    busy 堆并给该服务器计数；
// 4. 取计数最大值，所有计数等于最大值的编号即答案；k > n 时每个请求各占一台空闲
//    服务器，编号 0..n-1 全部并列，直接返回。
//
// 复杂度分析：
// - 时间复杂度：O((n + k) log k)，每台服务器每次空闲/忙碌进出堆各一次
// - 空间复杂度：O(k)，两个堆与计数数组（busy 堆至多同时存 k 个元素）

#include <gtest/gtest.h>

#include <algorithm>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

namespace {
class Solution {
   public:
    vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
        vector<int> ret;
        if (k > arrival.size()) {
            for (auto i = 0; i < arrival.size(); i++) {
                ret.emplace_back(i);
            }
            return ret;
        }

        priority_queue<int, vector<int>, greater<int>> idle;
        for (int i = 0; i < k; i++) {
            idle.push(i);
        }

        priority_queue<vector<int>, vector<vector<int>>, greater<vector<int>>> busy;
        vector<int> cnt(k, 0);
        for (int i = 0; i < arrival.size(); i++) {
            int time = arrival[i];
            int duration = load[i];

            while (!busy.empty() && busy.top()[0] <= time) {
                auto item = busy.top();
                busy.pop();
                idle.push(i + ((item[1] - i) % k + k) % k);
            }

            if (idle.empty()) {
                continue;
            }

            auto item = idle.top() % k;
            idle.pop();
            busy.push(vector<int>{time + duration, item});
            cnt[item] += 1;
        }

        auto mm = *max_element(cnt.begin(), cnt.end());
        for (auto i = 0; i < k; i++) {
            if (cnt[i] == mm) {
                ret.emplace_back(i);
            }
        }

        return ret;
    }
};
}  // namespace

TEST(Daily, 1606) {
    Solution s;

    // 官方示例 1：服务器 1 处理 2 个请求
    vector<int> arrival1{1, 2, 3, 4, 5};
    vector<int> load1{5, 2, 3, 3, 3};
    EXPECT_EQ(s.busiestServers(3, arrival1, load1), (vector<int>{1}));

    // 官方示例 2：请求 3 时刻服务器 0 恰好空闲，环首接力，共处理 2 个
    vector<int> arrival2{1, 2, 3, 4};
    vector<int> load2{1, 2, 1, 2};
    EXPECT_EQ(s.busiestServers(3, arrival2, load2), (vector<int>{0}));

    // 官方示例 3：三台各处理 1 个请求，全部并列
    vector<int> arrival3{1, 2, 3};
    vector<int> load3{10, 12, 11};
    EXPECT_EQ(s.busiestServers(3, arrival3, load3), (vector<int>{0, 1, 2}));

    // 官方示例 4：服务器 1 处理 4 个请求
    vector<int> arrival4{1, 2, 3, 4, 8, 9, 10};
    vector<int> load4{5, 2, 10, 3, 1, 2, 2};
    EXPECT_EQ(s.busiestServers(3, arrival4, load4), (vector<int>{1}));

    // 回归用例：i=1 时服务器 0 的空闲令牌若未按 (j - i) % k 重定位（误写成 i + j），
    // 键值 1 会被误认成服务器 1 消费掉，最终错答 [2]；正确答案是 [0,1]
    vector<int> arrival5{1, 2, 3, 4, 8};
    vector<int> load5{1, 5, 5, 1, 1};
    EXPECT_EQ(s.busiestServers(3, arrival5, load5), (vector<int>{0, 1}));

    // 边界：服务器数多于请求数，编号 0..n-1 全部并列
    vector<int> arrival6{1, 2};
    vector<int> load6{3, 4};
    EXPECT_EQ(s.busiestServers(5, arrival6, load6), (vector<int>{0, 1}));

    // 边界：单台服务器串行处理所有请求
    vector<int> arrival7{1, 2};
    vector<int> load7{1, 1};
    EXPECT_EQ(s.busiestServers(1, arrival7, load7), (vector<int>{0}));
}
