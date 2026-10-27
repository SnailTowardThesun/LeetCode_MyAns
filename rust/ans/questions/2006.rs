/**
 * No.2006 差的绝对值为 K 的数对数目
 *
 * @题目描述
 * |nums[i] - nums[j]| == k 的下标对 (i,j) 数量。
 *
 * @示例
 * 输入：nums = [3,2,1,5,4], k = 2
 * 输出：3
 *
 * @解题思路
 * 哈希计数：遍历到 x 时累加已出现的 x+k 与 x-k 的个数，再把 x 计入。
 */
use std::collections::HashMap;

fn count_k_difference(nums: Vec<i32>, k: i32) -> i32 {
    let mut mp = HashMap::new();
    let mut ans = 0;
    nums.iter().for_each(|x| {
        ans += *mp.get(&(*x + k)).unwrap_or(&0) + *mp.get(&(*x - k)).unwrap_or(&0);
        *mp.entry(*x).or_insert(0) += 1;
    });
    ans
}

#[test]
fn test_count_k_difference() {
    let example = vec![3, 2, 1, 5, 4];
    // let example = vec![1,2,2,1];
    let ret = count_k_difference(example, 2);
    println!("{}", ret);
}
