/**
 * No.1189 「气球」的最大数量
 *
 * @题目描述
 * 用 text 中的字母最多能拼出多少个 "balloon"。
 *
 * @示例
 * 输入："nlaebolko"
 * 输出：1
 *
 * @解题思路
 * 统计 b/a/l/o/n 各字符数量，l 与 o 除以 2，取最小值。
 */
use std::collections::HashMap;

fn max_number_of_balloons(text: String) -> i32 {
    let mut container = HashMap::new();
    container.insert('b', 0);
    container.insert('a', 0);
    container.insert('l', 0);
    container.insert('o', 0);
    container.insert('n', 0);

    for i in text.chars() {
        if container.contains_key(&i) {
            *container.get_mut(&i).unwrap() += 1;
        }
    }

    let mut ret = i32::MAX;
    ret = ret.min(*container.get(&'b').unwrap());
    ret = ret.min(*container.get(&'a').unwrap());
    ret = ret.min(*container.get(&'l').unwrap() / 2);
    ret = ret.min(*container.get(&'o').unwrap() / 2);
    ret = ret.min(*container.get(&'n').unwrap());

    return ret;
}

#[test]
fn test_max_number_of_balloons() {
    let example = String::from("nlaebolko");
    let ret = max_number_of_balloons(example);
    println!("{}", ret);
}
