/**
 * No.2016 增量元素之间的最大差值
 *
 * @题目描述
 * nums[j] - nums[i]（j > i 且 nums[i] < nums[j]）的最大值，不存在返回 -1。
 *
 * @示例
 * 输入：[7,1,5,4]
 * 输出：4
 *
 * @解题思路
 * 从右往左维护后缀最大值 right_max，逐位比较取最大差。
 */

fn maximum_difference(nums: Vec<i32>) -> i32 {
    let mut ret = -1;

    let mut right_max = nums[nums.len() - 1 as usize];
    for i in (0..nums.len() - 1).rev() {
        if nums[i] >= right_max {
            right_max = std::cmp::max(nums[i], right_max);
        } else {
            ret = std::cmp::max(ret, right_max - nums[i]);
        }
    }

    return ret;
}

#[test]
fn test_maximum_difference() {
    let example = vec![
        999, 997, 980, 976, 948, 940, 938, 928, 924, 917, 907, 907, 881, 878, 864, 862, 859, 857,
        848, 840, 824, 824, 824, 805, 802, 798, 788, 777, 775, 766, 755, 748, 735, 732, 727, 705,
        700, 697, 693, 679, 676, 644, 634, 624, 599, 596, 588, 583, 562, 558, 553, 539, 537, 536,
        509, 491, 485, 483, 454, 449, 438, 425, 403, 368, 345, 327, 287, 285, 270, 263, 255, 248,
        235, 234, 224, 221, 201, 189, 187, 183, 179, 168, 155, 153, 150, 144, 107, 102, 102, 87,
        80, 57, 55, 49, 48, 45, 26, 26, 23, 15,
    ];
    let ret = maximum_difference(example);
    println!("{}", ret);
}
