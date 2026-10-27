/**
 * No.1984 学生分数的最小差值
 *
 * @题目描述
 * 选 k 个分数，最小化其中的最大值与最小值之差。
 *
 * @示例
 * 输入：nums = [9,4,1,7], k = 2
 * 输出：2
 *
 * @解题思路
 * 排序后定长滑窗：窗口取连续 k 个数，最小化 nums[i+k-1] - nums[i]。
 */

fn minimum_difference(nums: Vec<i32>, k: i32) -> i32 {
    if k == 1 {
        return 0;
    }

    let mut nums = nums;
    nums.sort();

    let mut ret = i32::MAX;

    for i in 0..(nums.len() - k as usize + 1) {
        let tmp = nums[i + k as usize - 1] - nums[i];
        ret = if tmp < ret { tmp } else { ret };
    }

    return ret;
}

#[test]
fn test_minimum_difference() {
    let example = vec![9, 4, 7, 1];
    let ret = minimum_difference(example, 2);
    println!("{}", ret);
}
