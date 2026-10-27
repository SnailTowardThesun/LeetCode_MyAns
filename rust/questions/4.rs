/**
 * No.4 寻找两个正序数组的中位数
 *
 * @题目描述
 * 两个正序数组求中位数，要求时间复杂度 O(log(m+n))。
 *
 * @示例
 * 输入：nums1 = [1,3], nums2 = [2]
 * 输出：2.0
 *
 * @解题思路
 * 在较短的数组上二分划分点 part_x，另一数组的划分点 part_y 由总元素数推出；比较四个边界值直到两侧划分合法，按总数奇偶计算中位数。
 */

fn get_median_of_two_sorted_arrays(nums1: Vec<i32>, nums2: Vec<i32>) -> f64 {
    let ret: f64 = 0.0;

    let short;
    let long;

    if nums1.len() <= nums2.len() {
        short = nums1;
        long = nums2;
    } else {
        short = nums2;
        long = nums1;
    }

    let mut low = 0;
    let mut high = short.len();

    let mut part_x;
    let mut part_y;

    while low <= high {
        part_x = (low + high) / 2;
        part_y = (short.len() + long.len() + 1) / 2 - part_x;

        // get the value in short array
        let short_left = if part_x == 0 {
            i32::MIN
        } else {
            short[part_x - 1]
        };

        let short_right = if part_x == short.len() {
            i32::MAX
        } else {
            short[part_x]
        };

        // get the value in long array
        let long_left = if part_y == 0 {
            i32::MIN
        } else {
            long[part_y - 1]
        };

        let long_right = if part_y == long.len() {
            i32::MAX
        } else {
            long[part_y]
        };

        if short_left <= long_right && long_left <= short_right {
            if (short.len() + long.len()) % 2 == 0 {
                return f64::from(short_left.max(long_left) + short_right.min(long_right)) / 2.0;
            } else {
                return f64::from(short_left.max(long_left));
            }
        } else if short_left > long_right {
            high = part_x - 1;
        } else {
            low = part_x + 1;
        }
    }

    return ret;
}

#[test]
fn test_get_median_of_two_sored_arrays() {
    assert_eq!(1, 1);

    let demo1_num1 = vec![1, 3];
    let demo1_num2 = vec![2];

    assert_eq!(2.0, get_median_of_two_sorted_arrays(demo1_num1, demo1_num2));

    let demo2_num1 = vec![1, 2];
    let demo2_num2 = vec![3, 4];

    assert_eq!(2.5, get_median_of_two_sorted_arrays(demo2_num1, demo2_num2));
}
