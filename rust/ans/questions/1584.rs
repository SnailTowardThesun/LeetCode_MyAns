/**
 * No.1584 连接所有点的最小费用
 *
 * @题目描述
 * 平面上把所有点连通的最小曼哈顿距离总费用（最小生成树）。
 *
 * @示例
 * 输入：[[0,0],[2,2],[3,10],[5,2],[7,10]]
 * 输出：20
 *
 * @解题思路
 * Kruskal：枚举所有点对距离排序，借 q547 的并查集 OrderedUnion 依次合并不连通的点对。
 */
use super::q547::OrderedUnion;

fn min_cost_connect_points(points: Vec<Vec<i32>>) -> i32 {
    // using Kruskal

    struct Node {
        x: usize,
        y: usize,
        distance: i32,
    }

    let mut container: Vec<Node> = vec![];
    // calculate all distance
    for i in 0..points.len() {
        for j in i + 1..points.len() {
            let dis = i32::abs(points[i][0] - points[j][0]) + i32::abs(points[i][1] - points[j][1]);
            container.push(Node {
                x: i,
                y: j,
                distance: dis,
            })
        }
    }

    container.sort_by(|a, b| a.distance.cmp(&b.distance));
    for i in 0..container.len() {
        println!(
            "{}, {}: {}",
            container[i].x, container[i].y, container[i].distance
        );
    }

    let mut count = 0;
    let mut obj = OrderedUnion::new(points.len());
    let mut ret = 0;

    for i in 0..container.len() {
        if count == points.len() - 1 {
            break;
        }

        if obj.connected(container[i].x as i32, container[i].y as i32) {
            continue;
        }

        obj.union(container[i].x as i32, container[i].y as i32);
        ret += container[i].distance;
        count += 1;
    }

    ret
}

#[test]
fn test_min_cost_connect_points() {
    let obj = vec![vec![0, 0], vec![2, 2], vec![3, 10], vec![5, 2], vec![7, 10]];
    let ret = min_cost_connect_points(obj);
    println!("result: {}", ret);
}
