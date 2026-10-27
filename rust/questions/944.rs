/**
 * No.944 删列造序
 *
 * @题目描述
 * 删除若干列使每行字符按列非降序，求最少删除列数。
 *
 * @示例
 * 输入：["cba","daf","ghi"]
 * 输出：1（删第 0 列）
 *
 * @解题思路
 * 逐列比较上下相邻字符，出现降序则该列计入删除数并 break。
 */

fn min_deletion_size(strs: Vec<String>) -> i32 {
    let mut ret = 0;

    let mut new_strs: Vec<Vec<char>> = Vec::new();

    for i in 0..strs.len() {
        new_strs.push(strs[i].chars().collect::<Vec<char>>());
    }

    for i in 0..new_strs[0].len() {
        for j in 1..new_strs.len() {
            if new_strs[j - 1][i] > new_strs[j][i] {
                ret += 1;
                break;
            }
        }
    }

    return ret;
}

#[test]
fn test_min_deletion_size() {
    let strs = vec![
        String::from("cba"),
        String::from("daf"),
        String::from("ghi"),
    ];
    let pos = min_deletion_size(strs);
    print!("{}", pos)
}
