/**
 * No.60 排列序列
 *
 * @题目描述
 * 返回 1..n 按字典序排列的第 k 个排列。
 *
 * @示例
 * 输入：n = 3, k = 3
 * 输出："213"
 *
 * @解题思路
 * 康托展开：逐位确定——(k-1)/(剩余阶乘) 定位当前位应取剩余数字中的第几个，取出后 k 对阶乘取余、阶乘递减。
 */

fn get_permutation(n: i32, k: i32) -> String {
    let (mut seq, mut res) = (
        String::with_capacity(n as usize),
        String::with_capacity(n as usize),
    );
    (1..=(n as u8)).for_each(|x| {
        seq.push((b'0' + x) as char);
    });
    let (mut base, mut k) = ((1..=(n - 1)).fold(1, |m, x| x * m), k - 1);

    for i in (1..=(n - 1)).rev() {
        let pos = (k / base) as usize;
        let c = seq.chars().nth(pos);
        res.push(c.unwrap());
        seq.remove(pos);
        k %= base;
        base /= i;
    }

    res.push(seq.chars().nth(0).unwrap());

    res
}

#[test]
fn test_get_permutation() {
    let ret = get_permutation(3, 3);
    println!("{}", ret);
}
