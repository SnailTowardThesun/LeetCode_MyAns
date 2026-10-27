// Author: hankun1991@outlook.com

/**
 * No.3551 数位和排序的最小交换次数 (2026-10-17)
 *
 * @题目描述
 * 给你一个由互不相同的正整数组成的数组 nums。
 * 你需要根据每个数字的数位和将数组升序排序；
 * 若两个数字的数位和相同，则较小的数字排在前面。
 * 返回将 nums 重排为该顺序所需的最小交换次数。
 * 一次交换指交换数组中两个不同位置上的值。
 * 数据范围：1 <= nums.length <= 10^5，1 <= nums[i] <= 10^9。
 *
 * @示例
 * 输入: nums = [37,100]
 * 输出: 1
 * 解释: 数位和分别为 [10,1]，目标顺序为 [100,37]，交换一次即可。
 *
 * 输入: nums = [18,43,34,16]
 * 输出: 2
 * 解释: 数位和分别为 [9,7,7,7]，目标顺序为 [16,34,43,18]，
 *       交换 18 与 16、43 与 34 即可。
 *
 * @解题思路
 * 排序 + 置换环分解：
 * 1. 为每个数字计算三元组「数位和、数值、原下标」；
 * 2. 按数位和升序、数值升序排序，得到目标排列（元组默认字典序即为此规则）；
 * 3. 目标排列与原数组之间形成一个置换。把置换拆成若干环，
 *    长度为 k 的环最少需要 k-1 次交换；
 * 4. 用 visited 标记访问过的下标并遍历所有环，累计 len-1。
 *
 * @复杂度分析
 * - 时间复杂度: O(n log n)，瓶颈是排序
 * - 空间复杂度: O(n)，存储三元组和访问标记
 */

fn min_swaps(nums: Vec<i32>) -> i32 {
    let digit_sum = |mut n: i32| {
        let mut sum = 0;
        while n != 0 {
            sum += n % 10;
            n /= 10;
        }
        sum
    };

    let n = nums.len();
    // 三元组：(数位和, 数值, 原下标)，元组字典序 = 数位和升序 + 数值升序
    let mut container: Vec<(i32, i32, usize)> = nums
        .iter()
        .enumerate()
        .map(|(i, &v)| (digit_sum(v), v, i))
        .collect();
    container.sort();

    let mut visited = vec![false; n];
    let mut ret = 0;
    for i in 0..n {
        if visited[i] {
            continue;
        }

        // 沿置换环走一圈，长度为 len 的环最少需要 len-1 次交换
        let mut len = 0;
        let mut j = i;
        while !visited[j] {
            visited[j] = true;
            j = container[j].2;
            len += 1;
        }

        ret += len - 1;
    }

    return ret;
}

#[test]
fn test_min_swaps() {
    // 官方示例 1：数位和 [10,1]，目标顺序 [100,37]
    assert_eq!(min_swaps(vec![37, 100]), 1);

    // 官方示例 2：数组已按数位和有序，无需交换
    assert_eq!(min_swaps(vec![22, 14, 33, 7]), 0);

    // 官方示例 3：相同数位和按数值排序，交换 18/16、43/34
    assert_eq!(min_swaps(vec![18, 43, 34, 16]), 2);

    // 一个长度为 4 的置换环，最少需要 3 次交换
    assert_eq!(
        min_swaps(vec![277993448, 416038674, 616955867, 539372283]),
        3
    );
}
