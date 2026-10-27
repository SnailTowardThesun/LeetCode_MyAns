/**
 * No.15 三数之和
 *
 * @题目描述
 * 找出数组中所有和为 0 的不重复三元组。
 *
 * @示例
 * 输入：[-1,0,1,2,-1,-4]
 * 输出：[[-1,-1,2],[-1,0,1]]
 *
 * @解题思路
 * 排序后枚举首元素（跳过重复值），内层用哈希 two_sum_in 在剩余元素中找和为 -nums[i] 的二元组。
 */
use std::collections::HashMap;

fn three_sum(nums: Vec<i32>) -> Vec<Vec<i32>> {
    if nums.len() < 3 {
        return vec![vec![]];
    }

    let mut nums = nums;

    nums.sort();

    let mut result: Vec<Vec<i32>> = Vec::new();

    // fn two_sum(nums: Vec<i32>, target: i32) -> Vec<i32> {
    fn two_sum_in(numbers: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
        let mut v: Vec<Vec<i32>> = Vec::new();

        let mut m = HashMap::new();

        for (index, value) in numbers.iter().enumerate() {
            let num = target - *value;
            if m.contains_key(&num) {
                v.push(vec![m[&num], index as i32]);
            }
            m.insert(value, index as i32);
        }

        return v;
    }

    let pos = nums.len() - 2;

    for i in 0..pos {
        if i != 0 && nums[i] == nums[i - 1] {
            continue;
        }

        let ret = two_sum_in(nums[i + 1..nums.len()].to_vec(), 0 - nums[i]);
        if ret.len() > 0 {
            for j in &ret {
                println!(
                    "{} : {} : {}",
                    nums[i],
                    nums[i + 1 + j[0] as usize],
                    nums[i + 1 + j[1] as usize]
                );
                result.push(vec![
                    nums[i],
                    nums[i + 1 + j[0] as usize],
                    nums[i + 1 + j[1] as usize],
                ]);
            }
        }
    }

    return result;
}

#[test]
fn test_three_sum() {
    let demo = vec![-1, 0, 1, 2, -1, -4];
    assert_eq!(three_sum(demo), vec![vec![-1, 0, 1], vec![-1, -1, 2]]);
}
