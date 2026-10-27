/**
 * No.16 最接近的三数之和
 *
 * @题目描述
 * 找三个整数使其和最接近 target，返回该和。
 *
 * @示例
 * 输入：nums = [-1,2,1,-4], target = 1
 * 输出：2（-1+2+1）
 *
 * @解题思路
 * 排序 + 固定首元素（跳重复）+ 双指针：按三数之和与 target 的差值决定收缩方向。
 */

pub fn three_sum_closest(nums: Vec<i32>, target: i32) -> i32 {
    if nums.len() < 3 {
        return 0;
    }

    let mut nums = nums;

    nums.sort();
    let mut ret = nums[0] + nums[1] + nums[2];

    for i in 0..(nums.len() - 2) {
        let mut left = i + 1;
        let mut right = nums.len() - 1;
        while left < right {
            let tmp = nums[i] + nums[left] + nums[right];
            if tmp == target {
                return target;
            }

            if (tmp - target).abs() < (ret - target).abs() {
                ret = tmp;
            }

            if tmp > target {
                right -= 1;
            } else {
                left += 1;
            }
        }
    }

    return ret;
}

#[test]
fn test_three_sum_closet() {
    let demo = vec![-1, 2, 1, -4];
    assert_eq!(three_sum_closest(demo, 1), 2);
}
