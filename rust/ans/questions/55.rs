/**
 * No.55 跳跃游戏
 *
 * @题目描述
 * 每步最多跳 nums[i] 格，判断能否到达最后一格。
 *
 * @示例
 * 输入：[2,3,1,1,4]
 * 输出：true
 *
 * @解题思路
 * 维护可达区间 [start, end] 逐格扩张：end = max(end, i + nums[i])，end 覆盖末格即成功。
 */

fn can_jump(nums: Vec<i32>) -> bool {
    let (mut start, mut end) = (0, 0);
    while start <= end {
        end = end.max(nums[start] as usize + start);
        if end >= nums.len() - 1 {
            return true;
        }
        start += 1;
    }
    return end >= nums.len() - 1;
}

#[test]
fn test_can_jump() {
    let example = vec![2, 3, 1, 1, 4];
    let ret = can_jump(example);
    println!("{}", ret);
}
