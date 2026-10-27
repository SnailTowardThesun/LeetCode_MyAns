/**
 * No.1342 将数字变成 0 的操作次数
 *
 * @题目描述
 * 偶数除 2、奇数减 1，问变 0 的操作次数。
 *
 * @示例
 * 输入：14
 * 输出：6
 *
 * @解题思路
 * 按规则模拟计数。
 */

fn number_of_steps(num: i32) -> i32 {
    if num == 0 {
        return 0;
    }

    let mut ret = 0;

    let mut num = num;
    loop {
        if num == 0 {
            break;
        }

        if num % 2 == 0 {
            num = num / 2;
        } else {
            num = num - 1;
        }

        ret += 1;
    }

    return ret;
}

#[test]
fn test_number_of_steps() {
    let ret = number_of_steps(14);
    println!("{}", ret);
}
