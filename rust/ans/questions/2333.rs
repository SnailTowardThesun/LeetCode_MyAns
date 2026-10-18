// Author: hankun1991@outlook.com

/**
 * No.2333 最小平方和 (2026-10-10)
 *
 * @题目描述
 * 给定两个长度为 n 的正整数数组 nums1 和 nums2（下标从 0 开始）。
 * 可以对 nums1 执行两类操作任意次（可以为 0 次）：
 *   - 类型 1：任选下标 i，令 nums1[i] 加 1，最多共执行 k1 次；
 *   - 类型 2：任选下标 i，令 nums1[i] 减 1，最多共执行 k2 次。
 * 返回执行操作后 Σ(nums1[i] - nums2[i])^2 的最小值。
 * 题目保证答案不超过 2^53 - 1。
 * 数据范围：1 <= n <= 10^5，1 <= nums1[i], nums2[i] <= 10^5，0 <= k1, k2 <= 10^9。
 *
 * @示例
 * 输入：nums1 = [1,4,10,12], nums2 = [5,8,6,9], k1 = 1, k2 = 1
 * 输出：43
 * 解释：差值绝对值为 [4,4,4,3]，用 2 次操作把两个 4 降为 3，
 *       得 [3,3,4,3]，平方和 = 9 + 9 + 16 + 9 = 43。
 *
 * @解题思路
 * 1. 每个位置的修改只影响该位置自身的差值，因此把总步数 step = k1 + k2
 *    视作整体预算，每次操作让某个 |nums1[i] - nums2[i]| 减 1 最划算；
 * 2. 用桶数组 arr[d] 统计「差值绝对值为 d」的位置个数（d 上限 1e5）；
 * 3. 从大到小遍历 d，把高桶中的计数尽可能搬到低一档（每次搬运消耗 1 步/个），
 *    等价于不断削平最大的差值，即贪心 + 桶排序；
 * 4. 最后 Σ d^2 * arr[d] 即为答案。
 *
 * @复杂度分析
 * - 时间复杂度: O(n + M)，M 为差值上界 1e5
 * - 空间复杂度: O(M)
 */

fn min_sum_square_diff(nums1: Vec<i32>, nums2: Vec<i32>, k1: i32, k2: i32) -> i64 {
    // 桶 arr[d]：差值绝对值为 d 的位置个数
    let mut arr = vec![0i64; 100_001];

    for i in 0..nums1.len() {
        arr[(nums1[i] - nums2[i]).unsigned_abs() as usize] += 1;
    }

    // 总预算 k1 + k2，从最大差值往低一档搬运
    let mut step = (k1 as i64) + (k2 as i64);
    let mut i = arr.len() - 1;
    while i > 0 && step > 0 {
        let change = step.min(arr[i]);
        step -= change;
        arr[i - 1] += change;
        arr[i] -= change;
        i -= 1;
    }

    let mut ret: i64 = 0;
    for (d, &cnt) in arr.iter().enumerate() {
        ret += (d as i64) * (d as i64) * cnt;
    }

    return ret;
}

#[test]
fn test_min_sum_square_diff() {
    // 官方示例：差值 [4,4,4,3]，2 次操作削平两个 4 → 43
    let ret = min_sum_square_diff(vec![1, 4, 10, 12], vec![5, 8, 6, 9], 1, 1);
    assert_eq!(ret, 43);

    // 手算用例
    let ret = min_sum_square_diff(
        vec![7, 11, 4, 19, 11, 5, 6, 1, 8],
        vec![4, 7, 6, 16, 12, 9, 10, 2, 10],
        3,
        6,
    );
    assert_eq!(ret, 27);
}
