"""
@file 2409.py
@brief LeetCode 2409. 统计共同度过的日子

@题目描述
    Alice 和 Bob 计划去纽约旅游。Alice 在 arriveAlice 到 leaveAlice 之间旅游（包含边界），
    Bob 在 arriveBob 到 leaveBob 之间旅游（包含边界）。
    每个日期字符串都由 5 个字符组成，格式为 "MM-DD"，对应某个月中的某一天。
    给你四个字符串 arriveAlice、leaveAlice、arriveBob、leaveBob，
    请你计算 Alice 和 Bob 同时在纽约旅游的天数。
    注：题目使用的日历为非闰年，一年共 365 天。

@示例
    示例 1：
    输入：arriveAlice = "08-15", leaveAlice = "08-18", arriveBob = "08-16", leaveBob = "08-19"
    输出：3
    解释：Alice 与 Bob 同时在纽约的日子为 08-16、08-17、08-18，共 3 天。

    示例 2：
    输入：arriveAlice = "10-01", leaveAlice = "10-31", arriveBob = "11-01", leaveBob = "12-31"
    输出：0
    解释：Alice 于 10-31 离开纽约，Bob 于 11-01 到达，两人没有同时在纽约的日子。

@解题思路
    1. cal_days 把 "MM-DD" 转成一年中的第几天：累加前 month-1 个月的天数
       （非闰年 2 月固定 28 天）再加上日号，四个日期各转一次；
    2. 先判不相交：Alice 的离开日早于 Bob 的到达日，或 Alice 的到达日晚于
       Bob 的离开日，两种情况直接返回 0；
    3. 相交时交集是闭区间 [max(两个到达日), min(两个离开日)]，
       天数 = min - max + 1（双闭区间，两端都要计入）。

    时间复杂度 O(1)（cal_days 最多累加 11 个月），空间复杂度 O(1)

来源：LeetCode
链接：https://leetcode.cn/problems/count-days-spent-together/description/
"""


class Solution:
    def countDaysTogether(self, arriveAlice: str, leaveAlice: str, arriveBob: str, leaveBob: str) -> int:
        def cal_days(d):
            days = [31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31]
            dds = d.split("-")
            rt = 0
            for i in range(int(dds[0]) - 1):
                rt += days[i]
            rt += int(dds[1])
            return rt

        int_arr_alice = cal_days(arriveAlice)
        int_lea_alice = cal_days(leaveAlice)
        int_arr_bob = cal_days(arriveBob)
        int_lea_bob = cal_days(leaveBob)

        if int_lea_alice < int_arr_bob or int_arr_alice > int_lea_bob:
            return 0

        return min(int_lea_alice, int_lea_bob) - max(int_arr_alice, int_arr_bob) + 1


def test_count_days_together() -> None:
    s = Solution()

    # ---- 官方示例 ----
    assert s.countDaysTogether("08-15", "08-18", "08-16", "08-19") == 3  # 08-16 ~ 08-18
    assert s.countDaysTogether("10-01", "10-31", "11-01", "12-31") == 0  # 相邻月份不重叠

    # ---- 区间完全相同 ----
    assert s.countDaysTogether("01-01", "12-31", "01-01", "12-31") == 365  # 全年 365 天

    # ---- 包含关系 ----
    assert s.countDaysTogether("01-01", "12-31", "02-10", "03-10") == 29  # Bob 被包含：2 月 19 天 + 3 月 10 天
    assert s.countDaysTogether("06-01", "06-10", "01-01", "12-31") == 10  # Alice 被包含

    # ---- 部分重叠 ----
    assert s.countDaysTogether("08-15", "09-10", "09-01", "09-20") == 10  # Alice 在前，跨月交集 09-01 ~ 09-10
    assert s.countDaysTogether("03-05", "03-12", "03-01", "03-08") == 4  # Bob 在前，交集 03-05 ~ 03-08

    # ---- 不相交（左邻 / 右邻）----
    assert s.countDaysTogether("01-01", "01-10", "01-11", "01-20") == 0  # Alice 先离开
    assert s.countDaysTogether("12-20", "12-31", "01-01", "12-19") == 0  # Bob 先离开

    # ---- 单点 / 单日边界 ----
    assert s.countDaysTogether("02-25", "02-28", "02-28", "03-05") == 1  # 仅共享 02-28（非闰年）
    assert s.countDaysTogether("01-01", "01-01", "01-01", "01-01") == 1  # 两人同一天到达并离开
    assert s.countDaysTogether("05-05", "05-05", "05-06", "05-06") == 0  # 两个单日行程不重合
    assert s.countDaysTogether("05-05", "05-05", "05-05", "05-20") == 1  # 单日行程落在对方区间端点


if __name__ == "__main__":
    test_count_days_together()
    print("✅ 2409 全部测试通过")
