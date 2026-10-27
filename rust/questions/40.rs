/**
 * No.40 组合总和 II
 *
 * @题目描述
 * 候选数组（含重复数字）中每个数字最多用一次，找出和为 target 的所有组合。
 *
 * @示例
 * 输入：candidates = [10,1,2,7,6,1,5], target = 8
 *
 * @解题思路
 * 排序后 DFS：同层跳过重复候选（i > idx 且与前值相同则 continue），递归下标 +1 保证每个数只用一次。
 */

fn combination_sum2(candidates: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
    let mut ret = vec![];

    fn dfs(
        candidates: &Vec<i32>,
        target: i32,
        cans: &mut Vec<i32>,
        ret: &mut Vec<Vec<i32>>,
        idx: usize,
    ) {
        if target < 0 {
            return;
        }

        if target == 0 {
            ret.push(cans.clone());
            return;
        }

        for i in idx..candidates.len() {
            if i > idx && candidates[i] == candidates[i - 1] {
                continue;
            }
            cans.push(candidates[i]);
            dfs(candidates, target - candidates[i], cans, ret, i + 1);
            cans.pop();
        }
    }

    let mut candidates = candidates;
    candidates.sort();
    dfs(&candidates, target, &mut vec![], &mut ret, 0);
    return ret;
}
#[test]
fn test_combination_sum2() {
    let candidates = vec![10, 1, 2, 7, 6, 1, 5];
    let ret = combination_sum2(candidates, 8);
    for i in 0..ret.len() {
        let tmp = ret.get(i).unwrap();
        for j in 0..tmp.len() {
            print!("{}\t", tmp.get(j).unwrap())
        }
        print!("\n");
    }
}
