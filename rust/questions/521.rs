/**
 * No.521 最长特殊序列 Ⅰ
 *
 * @题目描述
 * 两个字符串中最长「非公共子序列」的长度；两串相同返回 -1。
 *
 * @示例
 * 输入：a = "aba", b = "dcd"
 * 输出：3
 *
 * @解题思路
 * 两串不同时答案为较长者的长度（整串互不为对方子序列）；相同则任何子序列都公共，返回 -1。
 */

fn find_lu_slength(a: String, b: String) -> i32 {
    return if a == b {
        -1
    } else {
        (a.len().max(b.len())) as i32
    };
}

#[test]
fn test_find_lu_slength() {
    let a = String::from("aba");
    let b = String::from("dcd");
    let ret = find_lu_slength(a, b);
    println!("{}", ret);
}
