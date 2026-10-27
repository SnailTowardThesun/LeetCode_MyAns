/**
 * No.1748 唯一元素的和
 *
 * @题目描述
 * 数组中恰好出现一次的元素之和。
 *
 * @示例
 * 输入：[1,2,3,4,5]
 * 输出：15
 *
 * @解题思路
 * 计数数组统计频次，取频次为 1 的元素求和。
 */

fn sum_of_unique(nums: Vec<i32>) -> i32 {
    let mut container = vec![0; 100];

    for i in 0..nums.len() {
        container[nums[i] as usize - 1] += 1;
    }

    let mut sum = 0;
    for i in 0..100 {
        if container[i] == 1 {
            sum += i + 1;
        }
    }
    return sum as i32;
}

#[test]
fn test_sum_of_unique() {
    let example = vec![1, 2, 3, 4, 5];
    let ret = sum_of_unique(example);
    print!("ret: {}\n", ret);
}
