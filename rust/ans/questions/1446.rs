/**
 * No.1446 连续字符
 *
 * @题目描述
 * 只包含一种字符的最长连续子串长度。
 *
 * @示例
 * 输入："leetcode"
 * 输出：2（"ee"）
 *
 * @解题思路
 * 一次扫描：与前一个字符相同则延续计数并更新最大，否则重置。
 */

fn max_power(s: String) -> i32 {
    let mut max_length: i32 = 0;
    let mut res = 1;

    let mut pre_char = ' ';

    for c in s.chars() {
        match c == pre_char {
            true => {
                res = res + 1;
                max_length = max_length.max(res);
            }
            false => {
                res = 1;
                pre_char = c;
            }
        }
    }

    return max_length;
}

#[test]
fn test_max_power() {
    let ret = max_power(String::from("leetcode"));
    print!("{}", ret);
}
