/**
 * No.9 回文数
 *
 * @题目描述
 * 判断整数是否为回文数。负数、以及非零且末位为 0 的数不是回文。
 *
 * @示例
 * 输入：121
 * 输出：true
 *
 * @解题思路
 * 反转一半数字：recv 从低位逐位重建，直到 recv >= tmp（原数砍半），比较两者是否相等（奇数位时 recv 去掉末位再比）。
 */

fn is_palindrome(x: i32) -> bool {
    if x < 0 || (x != 0 && x % 10 == 0) {
        return false;
    }

    let mut tmp: i32 = x;
    let mut recv: i32 = 0;
    while tmp > recv {
        recv = recv * 10 + tmp % 10;
        tmp = tmp / 10;
    }

    return tmp == recv || tmp == recv / 10;
}

#[test]
fn test_is_palindrome() {
    let demo1 = 121;
    assert_eq!(is_palindrome(demo1), true);
    let demo2 = -121;
    assert_eq!(is_palindrome(demo2), false);
}
