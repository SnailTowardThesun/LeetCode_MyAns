/**
 * No.747 至少是其他数字两倍的最大数
 *
 * @题目描述
 * 最大数至少是其余所有数的两倍则返回其下标，否则返回 -1。
 *
 * @示例
 * 输入：[1,2,3,4]
 * 输出：-1
 *
 * @解题思路
 * 一次扫描维护最大值与次大值（及最大值下标），最后比较 max >= 2 * second。
 */

fn dominant_index(nums: Vec<i32>) -> i32 {
    if nums.len() == 1 {
        return 0;
    }

    let mut max = i32::MIN;
    let mut max_pos = 0;

    let mut second_max = i32::MIN;

    for i in 0..nums.len() {
        if nums[i] > max {
            second_max = max;
            max = nums[i];
            max_pos = i;
            continue;
        }

        if nums[i] > second_max {
            second_max = nums[i]
        }
    }

    if max < second_max * 2 {
        return -1;
    }

    return max_pos as i32;
}

#[test]
fn test_dominant_index() {
    let nums = vec![1, 2, 3, 4];
    let ret = dominant_index(nums);
    assert_eq!(ret, -1)
}
