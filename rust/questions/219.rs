/**
 * No.219 存在重复元素 II
 *
 * @题目描述
 * 是否存在 i ≠ j 使 nums[i] = nums[j] 且 |i - j| ≤ k。
 *
 * @示例
 * 输入：nums = [1,2,3,1], k = 3
 * 输出：true
 *
 * @解题思路
 * 哈希表存 值→最近下标，遇到重复值且下标差 ≤ k 即返回。
 */
use std::collections::HashMap;

fn contains_nearby_duplicate(nums: Vec<i32>, k: i32) -> bool {
    let mut container = HashMap::new();

    for i in 0..nums.len() {
        if let Some(j) = container.get(&nums[i]) {
            if i - j <= k as usize {
                return true;
            }
        }

        container.insert(nums[i], i);
    }
    return false;
}

#[test]
fn test_contains_nearby_duplicate() {
    let nums = vec![1, 2, 3, 1, 2, 3];
    println!("{}", contains_nearby_duplicate(nums, 2))
}
