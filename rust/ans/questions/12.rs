/**
 * No.12 整数转罗马数字
 *
 * @题目描述
 * 把 1..3999 的整数转换为罗马数字。
 *
 * @示例
 * 输入：1994
 * 输出："MCMXC"
 *
 * @解题思路
 * 贪心：数值-符号对（含 4/9/40/90/400/900 组合）从大到小排列，不断减去能减的最大值并拼接对应符号。
 */

fn int_to_roman(num: i32) -> String {
    let mut num = num;
    let mut table = vec![
        (1, "I"),
        (4, "IV"),
        (5, "V"),
        (9, "IX"),
        (10, "X"),
        (40, "XL"),
        (50, "L"),
        (90, "XC"),
        (100, "C"),
        (400, "CD"),
        (500, "D"),
        (900, "CM"),
        (1000, "M"),
    ];

    let mut ret = String::from("");

    while let Some(&(value, roman)) = table.last() {
        if num < value {
            table.pop();
        } else {
            num -= value;
            ret += roman;
        }
    }

    return ret;
}

#[test]
fn test_int_to_roman() {
    assert_eq!(int_to_roman(3), "III");
    assert_eq!(int_to_roman(4), "IV");
    assert_eq!(int_to_roman(9), "IX");
    assert_eq!(int_to_roman(58), "LVIII");
    assert_eq!(int_to_roman(1994), "MCMXCIV")
}
