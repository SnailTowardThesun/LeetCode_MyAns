/**
 * No.1 两数之和
 *
 * @题目描述
 * 给定整数数组 nums 和目标值 target，找出和为 target 的两个整数并返回下标，题目保证恰好存在一个解。
 *
 * @示例
 * 输入：nums = [2,7,11,15], target = 9
 * 输出：[0,1]（nums[0]+nums[1]=9）
 *
 * @解题思路
 * 哈希表记录 值→下标；遍历时查 target-当前值 是否已出现，出现即返回，O(n) 一次遍历。
 */
use std::collections::HashMap;

fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
    let v: Vec<i32> = Vec::new();
    let mut m = HashMap::new();

    for (index, value) in nums.iter().enumerate() {
        let num = target - *value;
        if m.contains_key(&num) {
            return vec![m[&num], index as i32];
        }
        m.insert(value, index as i32);
    }

    return v;
}

#[test]
fn test_two_sum() {
    let v = vec![2, 7, 11, 9];
    let ans = two_sum(v, 9);

    assert_eq!(ans[0], 0);
    assert_eq!(ans[1], 1);
}
