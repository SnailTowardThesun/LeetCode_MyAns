/**
 * No.57 插入区间
 *
 * @题目描述
 * 插入一个新区间，返回合并后的不重叠区间列表。
 *
 * @示例
 * 输入：intervals = [[1,3],[6,9]], newInterval = [2,5]
 * 输出：[[1,5],[6,9]]
 *
 * @解题思路
 * 把新区间 push 进列表后直接复用 q56 的 merge 完成合并。
 */
use super::q56::merge;

fn insert(intervals: Vec<Vec<i32>>, new_interval: Vec<i32>) -> Vec<Vec<i32>> {
    let mut intervals = intervals;

    intervals.push(new_interval);
    return merge(intervals);
}

#[test]
fn test_insert() {
    let example = vec![vec![1, 3], vec![6, 9]];
    let new = vec![2, 5];
    let ret = insert(example, new);
    println!("{}", ret.len())
}
