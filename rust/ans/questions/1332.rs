/**
 * No.1332 删除回文子序列
 *
 * @题目描述
 * 字符串只含 'a'/'b'，每次删一个回文子序列，求删空的最少次数。
 *
 * @示例
 * 输入："ababa"
 * 输出：1
 *
 * @解题思路
 * 整个串是回文则 1 次删空；否则先删所有 a 再删所有 b，2 次。
 */

fn remove_palindrome_sub(s: String) -> i32 {
    return if s == s.chars().rev().collect::<String>() {
        1
    } else {
        2
    };
}

#[test]
fn test_remove_palindrome_sub() {
    let s: String = String::from("ababa");
    let ret = remove_palindrome_sub(s);
    print!("{}\n", ret);
}
