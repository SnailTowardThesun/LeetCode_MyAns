/**
 * No.74 搜索二维矩阵
 *
 * @题目描述
 * 矩阵每行有序、每行首元素大于前一行末元素，判断目标值是否在矩阵中。
 *
 * @示例
 * 输入：matrix = [[1,2,5,7],[10,11,16,20],[23,30,34,60]], target = 13
 * 输出：false
 *
 * @解题思路
 * 逐行 append 拉平成一维有序数组后二分查找。
 */

fn search_matrix(matrix: Vec<Vec<i32>>, target: i32) -> bool {
    let mut matrix = matrix;

    let mut container = vec![];
    for i in 0..matrix.len() {
        container.append(&mut matrix[i]);
    }

    fn helper(array: Vec<i32>, target: i32) -> bool {
        if array.is_empty() {
            return false;
        }

        let mut start = 0;
        let mut end = array.len() - 1;
        while start < end {
            let mid = (start + end) / 2;
            if array[mid] == target {
                return true;
            }
            if array[mid] < target {
                start = mid + 1;
            } else {
                end = mid;
            }
        }

        return array[start] == target;
    }

    return helper(container, target);
}

#[test]
fn test_search_matrix() {
    let example = vec![vec![1, 2, 5, 7], vec![10, 11, 16, 20], vec![23, 30, 34, 60]];
    let ret = search_matrix(example, 13);
    println!("{}", ret);
}
