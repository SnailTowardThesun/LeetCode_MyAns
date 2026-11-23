"""
@题目描述
    1352. 最后 K 个数的乘积。ProductOfNumbers 表示一个初始为空的整数流。
    add(num) 追加一个 0 到 100 的整数，getProduct(k) 返回最近 k 个数的乘积。
    查询时已有至少 k 个数，任意连续段的乘积均适合 32 位有符号整数。
    操作总数最多为 40000，1 <= k <= 40000。

@示例
    依次加入 3、0、2、5、4，查询最近 2、3、4 个数，分别返回 20、40、0。
    继续加入 8，再查询最近 2 个数，返回 32。

@解题思路
    保存最近一个零之后的前缀积，首项 1 表示空前缀。每次遇到零，重新从 [1] 开始。
    有 m 个连续非零数时，数组长度为 m + 1。若 k > m，最近 k 个数中有零，直接返回 0。
    否则用末项除以倒数第 k + 1 项，消去查询区间之前的所有因子。
    add 均摊 O(1)，getProduct 为 O(1)。累计加入 n 个数时，最坏空间为 O(n)。
"""


class ProductOfNumbers:
    def __init__(self) -> None:
        self._container = [1]

    def add(self, num: int) -> None:
        if num == 0:
            self._container = [1]
        else:
            self._container.append(self._container[-1] * num)

    def getProduct(self, k: int) -> int:
        if k >= len(self._container):
            return 0
        return self._container[-1] // self._container[-1 - k]


def test_solution() -> None:
    stream = ProductOfNumbers()
    stream.add(3)
    assert stream.getProduct(1) == 3
    stream.add(0)
    assert stream.getProduct(1) == 0
    stream.add(2)
    stream.add(5)
    stream.add(4)
    assert stream.getProduct(2) == 20
    assert stream.getProduct(3) == 40
    assert stream.getProduct(4) == 0
    assert stream.getProduct(5) == 0
    stream.add(8)
    assert stream.getProduct(2) == 32

    stream.add(0)
    stream.add(0)
    stream.add(1)
    assert stream.getProduct(1) == 1
    assert stream.getProduct(2) == 0


if __name__ == "__main__":
    test_solution()
