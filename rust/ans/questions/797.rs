/**
 * No.797 所有可能的路径
 *
 * @题目描述
 * 有向无环图（邻接表）中从 0 到 n-1 的所有路径。
 *
 * @示例
 * 输入：[[1,2],[3],[3],[]]
 * 输出：[[0,1,3],[0,2,3]]
 *
 * @解题思路
 * 队列 BFS：弹出部分路径后向每个邻接点扩展，到达终点收进结果（另附 DFS 注释版）。
 */

fn all_paths_source_target(graph: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
    // bfs
    let mut ret = vec![];

    use std::collections::VecDeque;

    let path: Vec<i32> = vec![0];
    let mut container = VecDeque::from(vec![path]);

    let mut _cc = 0;
    while container.len() > 0 {
        _cc += 1;
        let current = container.pop_front().unwrap().clone();
        let node = current[current.len() - 1];
        let tmp_c = graph[node as usize].clone();
        for i in tmp_c {
            let mut tmp_path = current.clone();
            tmp_path.push(i);
            if i == graph.len() as i32 - 1 {
                ret.push(tmp_path);
            } else {
                container.push_back(tmp_path);
            }
        }
    }

    return ret;
}

// fn all_paths_source_target(graph: Vec<Vec<i32>>) -> Vec<Vec<i32>> {
// dfs
//     fn dfs(graph: &Vec<Vec<i32>>, result: &mut Vec<Vec<i32>>, node: i32, path: &mut Vec<i32>) {
//         path.push(node);
//
//         if node == graph.len() as i32 - 1 {
//             result.push(path.clone());
//             return
//         }
//
//         let next_node = graph[node as usize].clone();
//         for i in next_node {
//             dfs(graph, result, i, path);
//             path.remove(path.len() - 1);
//         }
//
//     }
//
//     let mut ret = vec![];
//     let mut path = vec![];
//
//     dfs(&graph, &mut ret, 0, &mut path);
//
//     return ret;
// }

#[test]
fn test_all_paths_source_target() {
    let eg = vec![vec![1, 2], vec![3], vec![3], vec![]];

    let ret = all_paths_source_target(eg);
    for i in ret {
        for j in i {
            print!("{}->", j);
        }
        println!();
    }
}
