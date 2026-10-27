/**
 * No.1688 比赛中的配对次数
 *
 * @题目描述
 * n 支队伍单败淘汰赛的总配对（比赛）次数。
 *
 * @示例
 * 输入：n = 7
 * 输出：6
 *
 * @解题思路
 * 每场淘汰一队，冠军产生前共淘汰 n-1 队，即比赛 n-1 场。
 */

fn number_of_matches(n: i32) -> i32 {
    return n - 1;
}

#[test]
fn test_number_of_matches() {
    number_of_matches(11);
}
