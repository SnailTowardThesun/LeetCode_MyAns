/**
 * No.1423 可获得的最大点数
 *
 * @题目描述
 * 每次只能从卡牌数组两端取一张，共取 k 张，求最大和。
 *
 * @示例
 * 输入：cardPoints = [1,2,3,4,5,6,1], k = 3
 * 输出：12
 *
 * @解题思路
 * 转化：留中间 n-k 张和最小 → 定长滑窗；初始和取末尾 k 张，逐张与开头 k 张交换取最大。
 */

fn max_score(card_points: Vec<i32>, k: i32) -> i32 {
    let mut init: i32 = card_points
        .iter()
        .skip(card_points.len() - k as usize)
        .sum();
    let mut res = init;
    for (sub, add) in card_points
        .iter()
        .skip(card_points.len() - k as usize)
        .zip(card_points.iter().take(k as usize))
    {
        init -= sub;
        init += add;
        if init > res {
            res = init;
        }
    }

    res
}

#[test]
fn test_max_score() {
    max_score(vec![1, 2, 3, 4, 5, 6, 1], 3);
}
