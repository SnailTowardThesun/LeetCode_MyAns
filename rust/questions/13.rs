/**
 * No.13 罗马数字转整数
 *
 * @题目描述
 * 把罗马数字字符串转换为整数。
 *
 * @示例
 * 输入："LVIII"
 * 输出：58
 *
 * @解题思路
 * 逐字符查表累加；若当前值大于前一个值，说明出现减法组合（如 IV），把前值的两倍扣回。
 */

fn roman_to_int(s: String) -> i32 {
    let mut num: i32 = 0;

    let mut val: i32;
    let mut last: i32 = 0;

    for i in s.chars() {
        match i {
            'M' => val = 1000,
            'D' => val = 500,
            'C' => val = 100,
            'L' => val = 50,
            'X' => val = 10,
            'V' => val = 5,
            'I' => val = 1,
            _ => val = 0,
        }

        if val > last {
            num -= last * 2;
        }
        last = val;
        num += val;
    }

    return num;
}

#[test]
fn test_roman_to_int() {
    assert_eq!(roman_to_int(String::from("LVIII")), 58);
}
