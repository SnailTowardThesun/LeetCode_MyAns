/**
 * No.539 最小时间差
 *
 * @题目描述
 * 时间点列表（HH:MM）中任意两个的最小分钟差。
 *
 * @示例
 * 输入：["23:59","00:01"]
 * 输出：2
 *
 * @解题思路
 * 转成分钟后排序，取相邻差的最小值；注意首尾环绕差（首 + 1440 - 尾）。
 */
use std::cmp::min;

fn find_min_difference(time_points: Vec<String>) -> i32 {
    fn get_minutes(str: String) -> i32 {
        let b = str.as_bytes();
        return ((b[0] - '0' as u8) as i32 * 10 + (b[1] - '0' as u8) as i32) * 60
            + (b[3] - '0' as u8) as i32 * 10
            + (b[4] - '0' as u8) as i32;
    }

    let mut container = vec![];
    let time_points = time_points;
    for i in 0..time_points.len() {
        container.push(get_minutes(time_points[i].to_string()));
    }

    container.sort();
    let mut ret = i32::MAX;
    for i in 1..container.len() {
        let tmp = container[i] - container[i - 1];
        ret = min(tmp, ret);
    }

    ret = min(ret, container[0] + 1440 - container[container.len() - 1]);
    return ret;
}

#[test]
fn test_find_min_difference() {
    let example = vec![
        String::from("23:59"),
        String::from("00:01"),
        String::from("00:12"),
    ];
    let ret = find_min_difference(example);
    print!("{}", ret);
}
