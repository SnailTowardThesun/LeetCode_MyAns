/**
 * No.1779 找到最近的有相同 X 或 Y 坐标的点
 *
 * @题目描述
 * 与给定点 x 或 y 坐标相同的点中曼哈顿距离最小者的下标，无则 -1。
 *
 * @示例
 * 输入：x = 3, y = 4, points = [[1,2],[3,1],[2,4],[2,3],[4,4]]
 * 输出：2
 *
 * @解题思路
 * 迭代器链：filter 同 x 或同 y → map (下标, 距离) → min_by_key。
 */

fn nearest_valid_point(x: i32, y: i32, points: Vec<Vec<i32>>) -> i32 {
    // let mut dis = i32::MAX;
    // let mut ret:i32 = -1;

    // for i in 0..points.len() {
    //     if x == points[i][0] || y == points[i][1] {
    //         let target = (x-points[i][0]).abs() + (y-points[i][1]).abs();
    //         if target < dis {
    //             dis = target;
    //             ret = i as i32;
    //         }
    //     }
    // }

    // return ret;

    points
        .iter()
        .enumerate()
        .filter(|(_, p)| p[0] == x || p[1] == y)
        .map(|(i, p)| (i, (p[0] - x).abs() + (p[1] - y).abs()))
        .min_by_key(|&(_, d)| d)
        .map_or(-1, |(i, _)| i as i32)
}

#[test]
fn test_nearest_valid_point() {
    let x = 3;
    let y = 4;
    let points = vec![vec![1, 2], vec![3, 1], vec![2, 4], vec![2, 3], vec![4, 4]];

    println!("{}", nearest_valid_point(x, y, points))
}
