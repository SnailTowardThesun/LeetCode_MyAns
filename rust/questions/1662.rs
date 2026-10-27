/**
 * No.1662 检查两个字符串数组是否相等
 *
 * @题目描述
 * 两个数组分别按序拼接后的字符串是否相同。
 *
 * @示例
 * 输入：["ab","c"] 与 ["abc"]
 * 输出：true
 *
 * @解题思路
 * join 拼接后直接比较。
 */

fn array_strings_are_equal(word1: Vec<String>, word2: Vec<String>) -> bool {
    let s1: String = word1.into_iter().collect();
    let s2: String = word2.into_iter().collect();

    return s1 == s2;
}

#[test]
fn test_array_strings_are_equal() {
    let w1 = vec![String::from("ab"), String::from("c")];
    let w2 = vec![String::from("abc")];
    print!("{}", array_strings_are_equal(w1, w2))
}
