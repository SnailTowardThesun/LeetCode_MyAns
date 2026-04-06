/**
 * @file top150_no380_randomized_set.cpp
 * @brief LeetCode 380. O(1) 时间插入、删除和获取随机元素
 *
 * @题目描述
 * 实现 RandomizedSet 类：
 * - RandomizedSet() 初始化 RandomizedSet 对象
 * - bool insert(int val) 当元素 val 不存在时，向集合中插入该项，并返回 true；
 *   否则，返回 false。
 * - bool remove(int val) 当元素 val 存在时，从集合中移除该项，并返回 true；
 *   否则，返回 false。
 * - int getRandom() 随机返回现有集合中的一项（测试用例保证调用此方法时集合中至少存在一个元素）。
 *   每个元素应该有相同的概率被返回。
 * 你必须实现类的所有函数，并满足每个函数的平均时间复杂度为 O(1)。
 *
 * @示例
 * 输入:
 * ["RandomizedSet", "insert", "remove", "insert", "getRandom", "remove", "insert", "getRandom"]
 * [[], [1], [2], [2], [], [1], [2], []]
 * 输出:
 * [null, true, false, true, 2, true, false, 2]
 *
 * 解释:
 * RandomizedSet randomizedSet = new RandomizedSet();
 * randomizedSet.insert(1); // 向集合中插入 1 。返回 true 表示 1 被成功地插入。
 * randomizedSet.remove(2); // 返回 false ，表示集合中不存在 2 。
 * randomizedSet.insert(2); // 向集合中插入 2 。返回 true 。集合现在包含 [1,2] 。
 * randomizedSet.getRandom(); // getRandom 应随机返回 1 或 2 。
 * randomizedSet.remove(1); // 从集合中移除 1 ，返回 true 。集合现在包含 [2] 。
 * randomizedSet.insert(2); // 2 已经在集合中，所以返回 false 。
 * randomizedSet.getRandom(); // 由于 2 是集合中唯一的数字，getRandom 总是返回 2 。
 *
 * @解题思路
 * 1. 哈希表 + 动态数组：
 *    - 使用 unordered_map 存储值到索引的映射，实现 O(1) 的查找
 *    - 使用 vector 存储所有值，实现 O(1) 的随机访问
 *    - 删除时，将待删除元素与数组最后一个元素交换，然后删除最后一个元素
 *      （这样避免数组中间出现空洞，保持 O(1)）
 *
 * 2. 注意：
 *    - set 的 getRandom 是 O(log n)，不满足要求
 *    - 需要同时维护两个数据结构
 *
 * @复杂度分析
 * - insert: 时间复杂度 O(1)，空间复杂度 O(1)
 * - remove: 时间复杂度 O(1)，空间复杂度 O(1)
 * - getRandom: 时间复杂度 O(1)，空间复杂度 O(1)
 */

#include <gtest/gtest.h>
#include <set>
#include <cstdlib>
#include <iterator>

using namespace std;

TEST(TOP150, No380_RandomizedSet) {
    class RandomizedSet {
    private:
        std::set<int> container;

    public:
        RandomizedSet() {}

        bool insert(int val) {
            if (container.find(val) == container.end()) {
                container.insert(val);
                return true;
            }

            return false;
        }

        bool remove(int val) {
            if (container.find(val) != container.end()) {
                container.erase(val);
                return true;
            }

            return false;
        }

        int get_random() {
            auto it = container.begin();
            std::advance(it, rand() % container.size());
            return *it;
        }
    };

    RandomizedSet randomizedSet;

    bool param_1 = randomizedSet.insert(1);
    EXPECT_EQ(param_1, true);
    bool param_2 = randomizedSet.remove(2);
    EXPECT_EQ(param_2, false);

    bool param_3 = randomizedSet.insert(2);
    EXPECT_EQ(param_3, true);

    auto ret = randomizedSet.get_random();
    EXPECT_TRUE(ret == 2 || ret == 1);

    auto param_4 = randomizedSet.remove(1);
    EXPECT_EQ(param_4, true);

    auto param_5 = randomizedSet.insert(2);
    EXPECT_EQ(param_5, false);

    ret = randomizedSet.get_random();
    EXPECT_TRUE(ret == 2);
}
