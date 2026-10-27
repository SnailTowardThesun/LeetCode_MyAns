/**
 * No.7 整数反转
 *
 * @题目描述
 * 给出 32 位有符号整数，反转其数字；溢出返回 0。
 *
 * @示例
 * 输入：-123
 * 输出：-321
 *
 * @解题思路
 * 逐位取模累加到 i64 缓冲避免中途溢出，结束后与 i32 边界比较，超界返回 0。
 */

fn reverse(x: i32) -> i32 {
    let mut num = x;
    let mut reverse_num: i64 = 0;
    while num != 0 {
        reverse_num = reverse_num * 10 + (num % 10) as i64;
        num = num / 10;
    }

    if reverse_num > i32::MAX as i64 || reverse_num < i32::MIN as i64 {
        return 0;
    }

    return reverse_num as i32;
}

#[test]
fn test_reverse() {
    let demo1 = -123;
    let ret = reverse(demo1);
    assert_eq!(ret, -321);
}
