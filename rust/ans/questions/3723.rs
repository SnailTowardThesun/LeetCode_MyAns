// Author: hankun1991@outlook.com

/**
 * No.3723 最大平方和的好整数 (2026-10-14)
 *
 * @题目描述
 * 给你两个正整数 num 和 sum。
 * 如果一个正整数 n 满足以下两个条件，则称其为好整数：
 * 1. n 的位数恰好为 num；
 * 2. n 的各位数字之和恰好为 sum。
 * 一个好整数 n 的分数定义为 n 的各位数字的平方和。
 * 返回一个字符串，表示能够获得最大分数的好整数 n。
 * 若有多个可能的好整数，返回其中最大的；若不存在，返回空字符串。
 *
 * @示例
 * 输入: num = 2, sum = 3
 * 输出: "30"
 * 解释: 好整数有 12、21、30，平方和分别为 5、5、9，30 的分数最大。
 *
 * 输入: num = 2, sum = 17
 * 输出: "98"
 * 解释: 好整数有 89、98，平方和均为 145，返回其中更大的 98。
 *
 * 输入: num = 1, sum = 10
 * 输出: ""
 * 解释: 不存在一位数使其数字之和为 10，返回空字符串。
 *
 * @解题思路
 * 贪心 + 凸函数性质：
 * 1. 无解判断：num 位数各位数字之和最大为 9*num，若 9*num < sum 则无解，返回空串；
 * 2. 平方和最大化：由凸性，当 a+b <= 9 时 a*a+b*b <= (a+b)*(a+b)，
 *    数字应尽量"集中"——能合并成 9 就合并成 9。因此最优数字组合为：
 *    sum/9 个 9、一个余数位 sum%9（若非 0）、其余位全为 0；
 * 3. 同分数取最大好整数：同一组数字降序排列即为最大的数，
 *    即 9 在最前、余数位次之、0 垫底。
 *
 * @复杂度分析
 * - 时间复杂度: O(num)，构造长度为 num 的答案字符串
 * - 空间复杂度: O(num)，答案字符串本身
 */

fn max_sum_of_squares(num: i32, sum: i32) -> String {
    if 9 * num < sum {
        return String::new();
    }

    let mut ret = String::new();

    // 由凸性数字尽量集中：先放 sum/9 个 9
    for _ in 0..sum / 9 {
        ret.push('9');
    }

    // 余数位（若非 0）紧跟其后
    if sum % 9 != 0 {
        ret.push((b'0' + (sum % 9) as u8) as char);
    }

    // 剩余位用 0 补齐到恰好 num 位
    while ret.len() < num as usize {
        ret.push('0');
    }

    return ret;
}

#[test]
fn test_max_sum_of_squares() {
    // 官方示例 1：好整数 12/21/30 中 30 的平方和最大
    assert_eq!(max_sum_of_squares(2, 3), "30");

    // 官方示例 2：89 与 98 平方和相同，返回更大的 98
    assert_eq!(max_sum_of_squares(2, 17), "98");

    // 官方示例 3：一位数的数字和无法达到 10，无解
    assert_eq!(max_sum_of_squares(1, 10), "");

    // 边界：sum = 9，无余数位，1 个 9 + 1 个 0
    assert_eq!(max_sum_of_squares(2, 9), "90");

    // 边界：sum 恰好填满所有位
    assert_eq!(max_sum_of_squares(3, 27), "999");

    // 边界：num 较大而 sum 很小，1 后补 0
    assert_eq!(max_sum_of_squares(5, 1), "10000");
}
