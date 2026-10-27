/**
 * No.334 递增的三元子序列
 *
 * @题目描述
 * 是否存在 i < j < k 使 nums[i] < nums[j] < nums[k]。
 *
 * @示例
 * 输入：[1,2,3,4,5]
 * 输出：true
 *
 * @解题思路
 * 贪心：维护目前最小值 small 与次小值 mid，出现大于 mid 的数即成立。
 */

fn increasing_triplet(nums: Vec<i32>) -> bool {
    if nums.len() < 3 {
        return false;
    }

    let mut small = i32::MAX;
    let mut mid = i32::MAX;

    for i in nums {
        if small >= i {
            small = i;
        } else if mid >= i {
            mid = i;
        } else if i > mid {
            return true;
        }
    }

    return false;
}

#[test]
fn test_increasing_triplet() {
    let example = vec![1, 2, 3, 4, 5];
    let ret = increasing_triplet(example);
    assert_eq!(ret, true);
}
