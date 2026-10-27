/**
 * No.1716 计算力扣银行的钱
 *
 * @题目描述
 * 周一存 1 元，此后每天比前一天多 1 元，每周一比上一周一多 1 元，求 n 天总额。
 *
 * @示例
 * 输入：n = 10
 * 输出：37
 *
 * @解题思路
 * 模拟：i % 7 == 0 时起存金额 +1，每天累加 起存金额 + i % 7。
 */

fn total_money(n: i32) -> i32 {
    if n < 0 {
        return 0;
    }

    let mut total = 1;
    let mut begin = 1;
    for i in 1..n {
        if i % 7 == 0 {
            begin += 1;
        }

        total += begin + i % 7;
    }
    return total;
}

#[test]
fn test_total_money() {
    let ret = total_money(10);
    assert_eq!(ret, 37);
}
