/**
 * No.414 第三大的数
 *
 * @题目描述
 * 返回数组中第三大的数（去重后）；不足三个返回最大值。
 *
 * @示例
 * 输入：[4,2,2,3,2,1]
 * 输出：2
 *
 * @解题思路
 * 排序 + dedup 去重后取倒数第三个，不足三个取最大。
 */

fn third_max(nums: Vec<i32>) -> i32 {
    let mut nums = nums;
    nums.sort();
    nums.dedup();
    if nums.len() < 3 {
        return nums[nums.len() - 1];
    }

    return nums[nums.len() - 3];
}

#[test]
fn test_third_max() {
    let arr = vec![4, 2, 2, 3, 2, 1];
    let ret = third_max(arr);
    print!("{}", ret);
}
