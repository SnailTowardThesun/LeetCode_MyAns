/**
 * No.11 盛最多水的容器
 *
 * @题目描述
 * 垂直线高度数组中选两根，与 x 轴围成容器使水最多。
 *
 * @示例
 * 输入：[1,8,6,2,5,4,8,3,7]
 * 输出：49
 *
 * @解题思路
 * 双指针从两端向内收缩：每步移动较矮的一侧——宽度递减时只有换更高的线才可能更优。
 */

fn max_area(height: Vec<i32>) -> i32 {
    let mut max = 0;
    let mut left = 0;
    let mut right = height.len() - 1;

    while left < right {
        let len = (right - left) as i32;
        let h = height[left].min(height[right]);

        max = max.max((len * h) as i32);

        if height[left] > height[right] {
            right -= 1;
        } else {
            left += 1;
        }
    }

    return max;
}

#[test]
fn test_max_area() {
    let demo = vec![1, 8, 6, 2, 5, 4, 8, 3, 7];
    assert_eq!(max_area(demo), 49);
}
