# 拆分 test_top_150_array_string.cpp 计划

## 目标

将 `cplusplus/top150/test_top_150_array_string.cpp` 按照 CLAUDE.md 的要求拆分为多个文件，并完善注释。

## 当前文件分析

原文件包含 26 道 LeetCode 题目（面试经典 150 题的数组/字符串部分）：

### 数组部分题目：
1. No88 - 合并两个有序数组 (MergeTwoSortedLists)
2. No27 - 移除元素 (RemoveElement)
3. No26 - 删除有序数组中的重复项 (RemoveDuplicatesFromSortedArray)
4. No80 - 删除有序数组中的重复项 II (RemoveDeplicates)
5. No169 - 多数元素 (MajorityElement)
6. No189 - 轮转数组 (Rotate)
7. No121 - 买卖股票的最佳时机 (MaxProfit)
8. No122 - 买卖股票的最佳时机 II (MaxProfit)
9. No55 - 跳跃游戏 (CanJump)
10. No45 - 跳跃游戏 II (jump)
11. No274 - H 指数 (HIndex)
12. No380 - O(1) 时间插入、删除和获取随机元素 (RandomizedSet)
13. No239 - 除自身以外数组的乘积 (ProductExceptSelf)
14. No134 - 加油站 (CanCompleteCircuit)
15. No135 - 分发糖果 (Candy)
16. No42 - 接雨水 (Trap)

### 字符串部分题目：
17. No13 - 罗马数字转整数 (RomainToInt)
18. No12 - 整数转罗马数字 (IntToRoman)
19. No58 - 最后一个单词的长度 (LengthOfLastWord)
20. No14 - 最长公共前缀 (LongestCommonPrefix)
21. No151 - 反转字符串中的单词 (ReverseWords)
22. No6 - Z 字形变换 (Z)

## 拆分方案

按照 CLAUDE.md 的规范：
- **C++ 源文件**: 每个算法题一个 `.cpp` 文件，文件名使用小写和下划线
- **注释要求**: 必须包含题目内容描述、解题思路说明，使用中文编写

### 目录结构

```
cplusplus/top150/
├── array/                               # 数组相关题目
│   ├── no88_merge_sorted_array.cpp           # No88
│   ├── no27_remove_element.cpp               # No27
│   ├── no26_remove_duplicates.cpp            # No26
│   ├── no80_remove_duplicates_ii.cpp         # No80
│   ├── no169_majority_element.cpp            # No169
│   ├── no189_rotate_array.cpp                # No189
│   ├── no121_best_time_to_buy_sell_stock.cpp # No121
│   ├── no122_best_time_to_buy_sell_stock_ii.cpp # No122
│   ├── no55_jump_game.cpp                    # No55
│   ├── no45_jump_game_ii.cpp                 # No45
│   ├── no274_h_index.cpp                     # No274
│   ├── no380_randomized_set.cpp              # No380
│   ├── no238_product_of_array_except_self.cpp # No238
│   ├── no134_gas_station.cpp                 # No134
│   ├── no135_candy.cpp                       # No135
│   └── no42_trapping_rain_water.cpp          # No42
├── string/                              # 字符串相关题目
│   ├── no13_roman_to_integer.cpp             # No13
│   ├── no12_integer_to_roman.cpp             # No12
│   ├── no58_length_of_last_word.cpp          # No58
│   ├── no14_longest_common_prefix.cpp        # No14
│   ├── no151_reverse_words_in_string.cpp     # No151
│   └── no6_zigzag_conversion.cpp             # No6
└── CMakeLists.txt                       # 更新构建配置
```

## 实施步骤

### 阶段 1: 创建目录结构
1. 创建 `cplusplus/top150/array/` 目录
2. 创建 `cplusplus/top150/string/` 目录

### 阶段 2: 拆分数组部分题目 (16 题)
为每个题目创建独立的 `.cpp` 文件，包含：
- 完整的中文题目描述注释
- 解题思路说明
- Solution 类实现
- Google Test 测试用例

### 阶段 3: 拆分字符串部分题目 (6 题)
同上，为字符串部分题目创建独立文件

### 阶段 4: 更新 CMakeLists.txt
- 移除旧的 `test_top_150_array_string.cpp` 引用
- 添加新的文件 glob 模式或逐个添加新文件

### 阶段 5: 验证构建
- 运行 cmake 和 make 确保编译成功
- 运行测试确保所有测试通过

## 注释模板规范

每个文件需要包含以下注释结构：

```cpp
/**
 * @file filename.cpp
 * @brief LeetCode XXX. 题目中文名
 *
 * @题目描述
 * 题目详细描述...
 *
 * @示例
 * 示例 1：
 * 输入: ...
 * 输出: ...
 * 解释: ...
 *
 * 示例 2：
 * ...
 *
 * @解题思路
 * 1. 思路一：...
 * 2. 思路二：...
 *
 * @复杂度分析
 * - 时间复杂度: O(...)
 * - 空间复杂度: O(...)
 */
```

## 注意事项

1. 保持原有代码逻辑不变，仅完善注释
2. 修复原文件中明显的代码问题（如 No169 的 bug）
3. 遵循 Google C++ Style（4 空格缩进，snake_case 命名等）
4. 确保每个文件都能独立编译
5. 测试用例保持与原文件一致
