/**
 * No.547 省份数量
 *
 * @题目描述
 * 相邻矩阵表示的城市连通关系，返回省份数（连通分量个数）。
 *
 * @示例
 * 输入：isConnected = [[1,1,0],[1,1,0],[0,0,1]]
 * 输出：2
 *
 * @解题思路
 * 并查集（按秩合并 OrderedUnion，见 q1584 复用）：合并所有相连城市后统计不同根的个数。
 */
use std::collections::HashMap;

pub struct OrderedUnion {
    root: Vec<i32>,
    rank: Vec<i32>,
}

impl OrderedUnion {
    pub fn union(&mut self, target1: i32, target2: i32) {
        let r1 = self.find(target1 as usize);
        let r2 = self.find(target2 as usize);

        if r1 != r2 {
            if self.rank[r1 as usize] > self.rank[r2 as usize] {
                self.root[r2 as usize] = r1
            } else if self.rank[r1 as usize] < self.rank[r2 as usize] {
                self.root[r1 as usize] = r2
            } else {
                self.root[r2 as usize] = r1;
                self.rank[r1 as usize] += 1;
            }
        }

        for i in 0..self.root.len() {
            print!("{}\t", self.root[i]);
        }
        println!();
    }

    pub fn find(&mut self, t: usize) -> i32 {
        if self.root[t] == t as i32 {
            return t as i32;
        }

        self.root[t as usize] = self.find(self.root[t] as usize);
        return self.root[t];
    }

    pub fn connected(&mut self, t1: i32, t2: i32) -> bool {
        self.find(t1 as usize) == self.find(t2 as usize)
    }

    pub fn new(size: usize) -> OrderedUnion {
        let mut obj = OrderedUnion {
            root: vec![0; size],
            rank: vec![1; size],
        };

        for i in 0..obj.root.len() {
            obj.root[i] = i as i32;
        }

        return obj;
    }
}

fn find_circle_num(is_connected: Vec<Vec<i32>>) -> i32 {
    let mut obj = OrderedUnion::new(is_connected[0].len());

    for i in 0..is_connected.len() {
        for j in 0..is_connected[0].len() {
            if is_connected[i][j] == 1 {
                obj.union(i as i32, j as i32)
            }
        }
    }

    let mut map = HashMap::new();
    for i in 0..obj.root.len() {
        map.insert(obj.root[i], 0);
    }

    map.len() as i32
}

#[test]
fn test_find_circle_num() {
    let obj = vec![
        vec![1, 0, 0, 1],
        vec![0, 1, 1, 0],
        vec![0, 1, 1, 1],
        vec![1, 0, 1, 1],
    ];
    println!("{}", find_circle_num(obj));
}
