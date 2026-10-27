/**
 * No.258 各位相加
 *
 * @题目描述
 * 反复把各位数字相加直到剩下一位数。
 *
 * @示例
 * 输入：38
 * 输出：2（3+8=11, 1+1=2）
 *
 * @解题思路
 * 数根公式：(num - 1) % 9 + 1，O(1)。
 */

fn add_digits(num: i32) -> i32 {
    return (num - 1) % 9 + 1;
}

#[test]
fn test_add_digits() {
    let ret = add_digits(35);
    println!("{}", ret);
}
