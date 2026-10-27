/**
 * No.18 四数之和
 *
 * @题目描述
 * 找出所有和为 target 的不重复四元组。
 *
 * @示例
 * 输入：[2,2,2,2,2], target = 8
 * 输出：[[2,2,2,2]]
 *
 * @解题思路
 * 排序 + 双层枚举前两数（各自跳过重复）+ 双指针找剩余两数，命中后两侧跳过重复值。
 */

fn four_sum(nums: Vec<i32>, target: i32) -> Vec<Vec<i32>> {
    let mut ret = vec![];

    if nums.len() < 4 {
        return vec![];
    }
    let mut nums = nums;

    nums.sort();

    for i in 0..nums.len() - 3 {
        if i > 0 && nums[i] == nums[i - 1] {
            continue;
        }
        for j in i + 1..nums.len() - 2 {
            if j > i + 1 && nums[j] == nums[j - 1] {
                continue;
            }
            let new_target = target - nums[i] - nums[j];
            let mut l = j + 1;
            let mut r = nums.len() - 1;
            while l < r {
                let tmp = nums[l] + nums[r];
                if tmp == new_target {
                    ret.push(vec![nums[i], nums[j], nums[l], nums[r]]);
                    l = l + 1;
                    r = r - 1;
                    while nums[l] == nums[l - 1] && l < r {
                        l = l + 1;
                        continue;
                    }
                    while nums[r] == nums[r + 1] && l < r {
                        r = r - 1;
                        continue;
                    }
                    continue;
                }

                if tmp > new_target {
                    r = r - 1;
                }

                if tmp < new_target {
                    l = l + 1;
                }
            }
        }
    }

    return ret;
}
#[test]
fn test_four_sum() {
    let nums = vec![2, 2, 2, 2, 2];
    let ret = four_sum(nums, 8);
    for i in 0..ret.len() {
        for j in 0..ret[i].len() {
            print!("{}\t", ret[i][j]);
        }
        println!();
    }
}
