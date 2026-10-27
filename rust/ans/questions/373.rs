/**
 * No.373 查找和最小的 K 对数字
 *
 * @题目描述
 * 两个升序数组中找出和最小的 k 个数对。
 *
 * @示例
 * 输入：nums1 = [1,2,4], nums2 = [-1,1,2], k = 10
 *
 * @解题思路
 * 归并式指针：next[i] 记录 nums1[i] 已配对到 nums2 的位置，每轮在候选窗口 [floor, ceiling] 中挑和最小者。
 */

fn k_smallest_pairs(nums1: Vec<i32>, nums2: Vec<i32>, k: i32) -> Vec<Vec<i32>> {
    let mut sums_pair: Vec<Vec<i32>> = Vec::new();
    let (len1, len2) = (nums1.len(), nums2.len());

    if len1 == 0 || len2 == 0 {
        return sums_pair;
    }

    let mut next = vec![0; len1];

    let mut floor = 0;
    let mut ceiling = 0;
    let mut curr = 0;

    for _ in 0..k {
        sums_pair.push(vec![nums1[curr], nums2[next[curr]]]);
        next[curr] += 1;
        if next[curr] >= len2 {
            floor = curr + 1;
            if floor >= len1 {
                break;
            }
        }
        if curr == ceiling && ceiling + 1 < len1 {
            ceiling += 1;
        }
        let mut sum = i32::MAX;
        for c in floor..ceiling + 1 {
            if nums1[c] + nums2[next[c]] < sum {
                sum = nums1[c] + nums2[next[c]];
                curr = c;
            }
        }
    }

    return sums_pair;
}

#[test]
fn test_k_smallest_pairs() {
    let nums1 = vec![1, 2, 4];
    let nums2 = vec![-1, 1, 2];
    let ret = k_smallest_pairs(nums1, nums2, 10);
    let ret = ret;
    for i in 0..ret.len() {
        print!("[{}, {}]\n", ret[i][0], ret[i][1]);
    }
}
