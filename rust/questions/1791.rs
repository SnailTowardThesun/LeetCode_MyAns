/**
 * No.1791 找出星型图的中心节点
 *
 * @题目描述
 * 星型图（n-1 条边都过中心）的中心节点。
 *
 * @示例
 * 输入：edges = [[1,2],[1,3]]
 * 输出：1
 *
 * @解题思路
 * 哈希查重：中心在每条边都出现，扫描过程中第二个重复出现的节点即中心。
 */
use std::collections::HashMap;

fn find_center(edges: Vec<Vec<i32>>) -> i32 {
    let mut container = HashMap::new();

    for i in edges {
        for j in i {
            if container.contains_key(&j) {
                return j;
            }

            container.insert(j, true);
        }
    }

    return 0;
}

#[test]
fn test_find_center() {
    let example = vec![vec![1, 2], vec![1, 3]];
    let ret = find_center(example);
    println!("{}", ret);
}
