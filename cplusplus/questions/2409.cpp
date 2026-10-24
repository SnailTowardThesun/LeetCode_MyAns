// @题目描述:
// Alice 和 Bob 计划去纽约旅游。Alice 在 [arriveAlice, leaveAlice] 期间在纽约（包含边界），
// Bob 在 [arriveBob, leaveBob] 期间在纽约（包含边界）。日期字符串格式为 "MM-DD"，
// 题目日历为非闰年（全年 365 天），且保证 arriveAlice <= leaveAlice、arriveBob <= leaveBob。
// 给定四个字符串 arriveAlice、leaveAlice、arriveBob、leaveBob，求两人同时在纽约的天数。
// 题目：https://leetcode.cn/problems/count-days-spent-together/
//
// @示例:
// 输入：arriveAlice = "08-15", leaveAlice = "08-18", arriveBob = "08-16", leaveBob = "08-19"
// 输出：3（两人 08-16 ~ 08-18 同时在纽约）
// 输入：arriveAlice = "10-01", leaveAlice = "10-31", arriveBob = "11-01", leaveBob = "12-31"
// 输出：0（Alice 10-31 离开，Bob 11-01 才到，无重叠）
//
// @解题思路:
// 1. calDays 把 "MM-DD" 换算成「一年中的第几天」：day 从下标 3 开始截取（跳过下标 2 的分隔符 '-'），
//    累加 month 之前的整月天数（下标只到 month-2），再加上日号
// 2. 两人行程是数轴上两个闭区间，共同天数 = min(两个离开日) - max(两个到达日) + 1（双闭区间两端都计入）
// 3. 区间不相交（某人到达日晚于对方离开日）时提前返回 0
//
// 复杂度分析：
// - 时间复杂度：O(1)（每次换算最多累加 11 个月）
// - 空间复杂度：O(1)

#include <gtest/gtest.h>

using namespace std;

namespace {
class Solution {
   public:
    int calDays(string date) {
        int ret = 0;

        vector<int> dic{31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

        string month = date.substr(0, 2);
        string day = date.substr(3, 2);

        int mo = stoi(month);
        int d = stoi(day);

        for (int i = 0; i < mo - 1; i++) {
            ret += dic[i];
        }

        ret += d;

        return ret;
    }
    int countDaysTogether(string arriveAlice, string leaveAlice, string arriveBob, string leaveBob) {
        int i_arr_alice = calDays(arriveAlice);
        int i_lea_alice = calDays(leaveAlice);
        int i_arr_bob = calDays(arriveBob);
        int i_lea_bob = calDays(leaveBob);
        if (i_arr_alice > i_lea_bob) {
            return 0;
        }
        if (i_arr_bob > i_lea_alice) {
            return 0;
        }
        return min(i_lea_alice, i_lea_bob) - max(i_arr_alice, i_arr_bob) + 1;
    }
};
}  // namespace

TEST(Daily, 2409) {
    Solution s;

    // Example 1: Alice [08-15, 08-18], Bob [08-16, 08-19], 重叠 3 天
    EXPECT_EQ(s.countDaysTogether("08-15", "08-18", "08-16", "08-19"), 3);

    // Example 2: 区间不相交，重叠 0 天
    EXPECT_EQ(s.countDaysTogether("10-01", "10-31", "11-01", "12-31"), 0);

    // Edge: 完全相同的全年区间，重叠 365 天（非闰年）
    EXPECT_EQ(s.countDaysTogether("01-01", "12-31", "01-01", "12-31"), 365);

    // Edge: 部分重叠，Alice [09-01, 10-19] Bob [09-22, 10-12]，重叠 21 天
    EXPECT_EQ(s.countDaysTogether("09-01", "10-19", "09-22", "10-12"), 21);

    // Edge: Alice 仅停留一天且落在 Bob 区间内，重叠 1 天
    EXPECT_EQ(s.countDaysTogether("05-10", "05-10", "05-10", "05-20"), 1);
}
