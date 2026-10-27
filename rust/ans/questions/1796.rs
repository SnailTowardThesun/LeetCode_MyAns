/**
 * No.1796 字符串中第二大的数字
 *
 * @题目描述
 * 字符串中第二大的数字（去重后），不存在返回 -1。
 *
 * @示例
 * 输入："dfa12321afd"
 * 输出：2
 *
 * @解题思路
 * 布尔数组标记 0-9 哪些出现，倒序取第二个为 true 的数字。
 */

fn second_highest(s: String) -> i32 {
    let mut ar = [false; 10];

    s.as_bytes()
        .iter()
        .filter(|x| x.is_ascii_digit())
        .map(|x| x - b'0')
        .for_each(|x| ar[x as usize] = true);

    ar.iter()
        .enumerate()
        .filter_map(|(ind, val)| if *val { Some(ind as i32) } else { None })
        .rev()
        .nth(1)
        .unwrap_or(-1)
}

#[test]
fn test_second_highest() {
    second_highest(String::from("1234"));
}
