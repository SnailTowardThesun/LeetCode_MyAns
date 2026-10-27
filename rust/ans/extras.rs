//! 附加练习（无题号，历史代码迁移自 ans/main.rs）。

/**
 * 求最大的 A[i] - A[j]（i < j）
 *
 * @解题思路
 * 维护前缀最大 left_max 与后缀最小 right_min，取两者之差的最大值；
 * 注意当前实现中 right_min 的循环区间 `len-1..1` 为空区间（未配合 .rev()），
 * right_min 恒为 0，实际退化为返回数组最大值，待修正。
 */

fn find_max_distance(numbers: Vec<i32>) -> i32 {
    let mut ret = i32::MIN;

    // solution 2, O(n)
    let mut left_max = vec![0; numbers.len()];
    let mut right_min = vec![0; numbers.len()];

    left_max[0] = numbers[0];
    for i in 1..numbers.len() {
        left_max[i] = std::cmp::max(left_max[i - 1], numbers[i])
    }

    for i in numbers.len() - 1..1 {
        right_min[i] = std::cmp::min(right_min[i + 1], numbers[i]);
    }

    for i in 0..numbers.len() {
        ret = std::cmp::max(ret, left_max[i] - right_min[i]);
    }

    return ret;
}

#[test]
fn test_find_max_distance() {
    let numbers = vec![1, 2, 7, 4, 5, 10, 6, 7, 8, 9, 2, 3, 1, 0];
    let ret = find_max_distance(numbers);
    assert_eq!(ret, 10);
}
