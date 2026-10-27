// Author: hankun1991@outlook.com

/**
 * No.2916 子数组不同元素平方和 II (2026-10-16)
 *
 * @题目描述
 * 给你一个下标从 0 开始的整数数组 nums。
 * 定义子数组 nums[i..j] 的不同计数为其中不同值的数目，
 * 请返回 nums 中所有子数组的不同计数的平方和。
 * 由于答案可能很大，返回其对 10^9 + 7 取模的结果。
 * 数据范围：1 <= nums.length <= 10^5，1 <= nums[i] <= 10^5。
 *
 * @示例
 * 输入: nums = [1,2,1]
 * 输出: 15
 * 解释: 六个子数组的不同计数分别为 1、1、1、2、2、2，
 *       平方和 = 1 + 1 + 1 + 4 + 4 + 4 = 15
 *
 * 输入: nums = [2,2]
 * 输出: 3
 * 解释: 三个子数组的不同计数均为 1，平方和 = 3
 *
 * @解题思路
 * 2913 的 Hard 加强版，n 放宽到 10^5，O(n^2) 暴力会超时，
 * 需要 O(n log n) 的贡献法 + 懒标记线段树：
 * 1. 枚举右端点 i，设 f(j) = 子数组 nums[j..i] 的不同计数，
 *    答案为每个 i 下 s = Σ f(j)^2 的累加取模；
 * 2. 平方和无法直接区间维护，利用恒等式 f^2 = 2*T(f) - f
 *    （T(f) = 1+2+…+f 为三角形数），转为分别增量维护 ΣT 与 Σf：
 *    当一段区间上每个 f 同时加 1 时，ΔΣT = Σf(旧值) + 区间长度，
 *    ΔΣf = 区间长度，故 s 的增量 = 2*Σf(旧值) + 区间长度；
 * 3. 设 x = nums[i] 上次出现的下标为 j（下标从 1 计，不存在则为 0），
 *    则左端点落在 [j+1, i] 的子数组恰好新增一个不同值 x，
 *    对这段的 f 整体 +1，其中「查询加一前的区间和 + 区间加一」
 *    合并为线段树的一次递归遍历（query_and_add1）；
 * 4. 线段树节点维护区间和 sum 与懒标记 todo（待下传的加值），
 *    进入子节点前先下传标记，回溯时由左右子节点上传合并。
 * 溢出检查：s <= n * n^2 = 10^15，线段树区间和 <= n^2 = 10^10，
 * 均在 i64 范围内，每步对 ans 取模。
 *
 * @复杂度分析
 * - 时间复杂度: O(n log n)，每个元素一次线段树区间查询+更新
 * - 空间复杂度: O(n)，线段树开 4n 个节点
 */
use std::collections::HashMap;

const MOD: i64 = 1_000_000_007;

// 线段树节点 o=1，区间 [l,r]，1 <= l <= r <= n
// 把 [ql,qr] 整体加一，同时返回加一之前的区间和
fn query_and_add1(
    sum: &mut Vec<i64>,
    todo: &mut Vec<i64>,
    o: usize,
    l: usize,
    r: usize,
    ql: usize,
    qr: usize,
) -> i64 {
    if ql <= l && r <= qr {
        let res = sum[o];
        sum[o] += (r - l + 1) as i64;
        todo[o] += 1;
        return res;
    }

    let m = (l + r) / 2;
    let add = todo[o];
    if add != 0 {
        // 下传懒标记
        sum[o * 2] += add * (m - l + 1) as i64;
        todo[o * 2] += add;
        sum[o * 2 + 1] += add * (r - m) as i64;
        todo[o * 2 + 1] += add;
        todo[o] = 0;
    }

    let mut res = 0;
    if ql <= m {
        res += query_and_add1(sum, todo, o * 2, l, m, ql, qr);
    }
    if m < qr {
        res += query_and_add1(sum, todo, o * 2 + 1, m + 1, r, ql, qr);
    }
    // 由左右子节点上传合并
    sum[o] = sum[o * 2] + sum[o * 2 + 1];
    res
}

fn sum_counts(nums: Vec<i32>) -> i32 {
    let n = nums.len();
    let mut sum = vec![0i64; n * 4];
    let mut todo = vec![0i64; n * 4];

    let mut ans: i64 = 0;
    let mut s: i64 = 0;
    let mut last: HashMap<i32, usize> = HashMap::new();

    for i in 1..=n {
        let x = nums[i - 1];
        let j = *last.get(&x).unwrap_or(&0);
        // [j+1, i] 内的子数组恰好新增一个不同值 x
        s += query_and_add1(&mut sum, &mut todo, 1, 1, n, j + 1, i) * 2 + (i - j) as i64;
        ans = (ans + s) % MOD;
        last.insert(x, i);
    }

    return ans as i32;
}

#[test]
fn test_sum_counts() {
    // 官方示例 1：六个子数组的不同计数 1、1、1、2、2、2
    assert_eq!(sum_counts(vec![1, 2, 1]), 15);

    // 官方示例 2：三个子数组的不同计数均为 1
    assert_eq!(sum_counts(vec![2, 2]), 3);

    // 手算用例：全不同元素 4*1 + 3*4 + 2*9 + 1*16 = 50
    assert_eq!(sum_counts(vec![1, 2, 3, 4]), 50);

    // 随机小数组与 O(n^2) 暴力对拍（固定种子保证可复现）
    use rand::prelude::*;
    let mut rng = StdRng::seed_from_u64(2916);
    for _ in 0..200 {
        let n = rng.gen_range(1..=50);
        let nums: Vec<i32> = (0..n).map(|_| rng.gen_range(1..=5)).collect();

        // 暴力：枚举全部子数组，哈希集合去重
        let mut brute: i64 = 0;
        for i in 0..n {
            let mut st = std::collections::HashSet::new();
            for j in i..n {
                st.insert(nums[j]);
                brute += (st.len() * st.len()) as i64;
            }
        }

        assert_eq!(sum_counts(nums) as i64, brute);
    }

    // 大规模取模：全不同元素时答案 = Σ (n-len+1)*len^2，n = 10^5
    let n = 100_000usize;
    let nums: Vec<i32> = (1..=n as i32).collect();
    let mut expect: i64 = 0;
    for len in 1..=n as i64 {
        expect = (expect + (n as i64 - len + 1) * len % MOD * len) % MOD;
    }
    assert_eq!(sum_counts(nums), expect as i32);
}
