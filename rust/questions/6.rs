/**
 * No.6 Z 字形变换
 *
 * @题目描述
 * 把字符串按 Z 字形（竖折线）写入 numRows 行后，逐行读出。
 *
 * @示例
 * 输入：s = "PAYPALISHIRING", numRows = 3
 * 输出："PAHNAPLSIIGYIR"
 *
 * @解题思路
 * 按行模拟：维护当前行号与步进方向，到达首行/末行时反向，逐字符追加到对应行，最后按行拼接。
 */

fn convert(s: String, num_rows: i32) -> String {
    if num_rows == 1 || num_rows >= s.len() as i32 {
        return s;
    }

    let mut ret: Vec<Vec<char>> = vec![vec![]; num_rows as usize];

    let mut row = 0;
    let mut step: i32 = 1;

    for c in s.chars() {
        ret[row].push(c);
        if row == 0 {
            step = 1;
        }

        if row == num_rows as usize - 1 {
            step = -1;
        }

        row = (row as i32 + step) as usize;
    }

    let mut str_ret = String::new();
    for i in 0..num_rows {
        for j in &ret[i as usize] {
            str_ret.push(*j);
        }
    }

    return str_ret;
}

#[test]
fn test_convert() {
    let s = String::from("PAYPALISHIRING");
    let row = 3;
    let ret = convert(s, row);

    assert_eq!(ret, "PAHNAPLSIIGYIR");
}
