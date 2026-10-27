/**
 * No.56 合并区间
 *
 * @题目描述
 * 合并所有重叠的区间。
 *
 * @示例
 * 输入：[[1,4],[4,5]]
 * 输出：[[1,5]]
 *
 * @解题思路
 * 排序后扫描：下一区间起点大于当前 end 时结算并开新区间，否则延伸 end。
 */

pub fn merge(intervals: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    let mut ret = vec![];

    let mut intervals = intervals;

    intervals.sort();

    let mut start = intervals[0][0];
    let mut end = intervals[0][1];

    for i in 1..intervals.len() {
        let target = intervals.get(i).unwrap();

        // add new start and end
        if target[0] > end {
            ret.push(vec![start, end]);
            start = target[0];
            end = target[1];
        }

        if target[1] > end {
            end = target[1]
        }
    }
    ret.push(vec![start, end]);

    return ret;
}

#[test]
fn test_merge() {
    let example = vec![vec![1, 4], vec![4, 5]];
    let ret = merge(example);
    println!("{}", ret.len());
}
