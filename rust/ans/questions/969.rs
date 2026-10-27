/**
 * No.969 煎饼排序
 *
 * @题目描述
 * 每次 flip 前 k 张饼，返回使数组升序的操作序列（k 从 1 计）。
 *
 * @示例
 * 输入：[3,2,4,1]
 * 输出：[3,4,2,3,2] 之类
 *
 * @解题思路
 * 选择排序式：每轮把未排序部分的最大值先翻到头部，再整段翻到底部，递归处理剩余前缀。
 */

fn pancake_sort(arr: Vec<i32>) -> Vec<i32> {
    let mut ret = vec![];

    let mut arr = arr;

    fn helper(arr: &mut Vec<i32>, container: &mut Vec<i32>) {
        if arr.len() == 0 {
            return;
        }

        let mut sorted = arr.clone();
        sorted.sort();
        if sorted == *arr {
            return;
        }

        fn get_max(arr: &Vec<i32>) -> i32 {
            let mut tmp = i32::MIN;
            let mut pos = 0;
            for i in 0..arr.len() {
                if arr[i] > tmp {
                    pos = i as i32;
                    tmp = arr[i];
                }
            }

            return pos;
        }

        fn reverse(arr: &mut Vec<i32>, end: usize) {
            let mut tmp = vec![];

            for i in 0..=end {
                tmp.push(arr[i]);
            }
            tmp.reverse();

            for i in 0..=end {
                arr[i] = tmp[i];
            }
            for i in arr {
                print!("{}\t", i)
            }
            println!();
        }

        let pos = get_max(arr);
        if pos != 0 {
            container.push(pos + 1);
            reverse(arr, pos as usize);
        }
        container.push(arr.len() as i32);
        reverse(arr, arr.len() - 1);
        let mut next = vec![];
        for i in 0..arr.len() - 1 {
            next.push(arr[i]);
        }
        helper(&mut next, container);
    }

    helper(&mut arr, &mut ret);
    return ret;
}

#[test]
fn test_pancake_sort() {
    let example = vec![3, 2, 4, 1];
    let ret = pancake_sort(example);
    for i in ret {
        print!("{}\t", i);
    }
}
