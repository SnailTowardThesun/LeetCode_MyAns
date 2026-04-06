# 修复测试用例错误计划

## 问题分析

### 问题1: 3583.cpp 的测试用例错误

**文件**: `/Users/hankun/github/LeetCode_MyAns/cplusplus/questions/3583.cpp`

**问题描述**: 
- 3583.cpp 文件包含 `TEST(Daily, 3583)` 测试
- 但查看 CMakeLists.txt，测试文件是通过 `file(GLOB TEST_FILES "${TEST_SRC_DIR}/*.cpp")` 自动收集的
- 需要运行测试查看具体错误信息

**当前代码分析**:
- 题目: 统计特殊三元组
- 测试用例1: `nums = [6, 3, 6]`，期望输出 `1`
- 测试用例2: `nums = [0, 1, 0, 0]`，期望输出 `2`

**潜在问题**: 需要运行测试确认具体错误

### 问题2: NO14_LongestCommonPrefix 的错误

**文件**: `/Users/hankun/github/LeetCode_MyAns/cplusplus/top150/test_top_150_array_string.cpp` (第612行)

**问题描述**:
```cpp
TEST(TOP150, NO14_LongestCommonPrefix) {
    // ... solution code ...
    
    Solution solution;
    auto input = std::vector<std::string>{"abab", "aba", ""};
    auto ret = solution.longestCommonPrefix(input);
    EXPECT_EQ(ret, "fl");  // <-- 错误！期望是 "fl" 但实际应该是 ""
}
```

**问题分析**:
- 输入: `["abab", "aba", ""]`
- 第三个字符串是空字符串 `""`
- 最长公共前缀应该是 `""` (空字符串)，因为第三个字符串是空的
- 但测试期望 `"fl"`，这是错误的

**正确的测试用例应该是**:
- 输入: `["flower", "flow", "flight"]` 期望: `"fl"`
- 或者修改期望值为 `""` 以匹配当前输入

## 修复方案

### 修复1: 3583.cpp
- 先运行测试查看具体错误信息
- 根据错误信息修复代码或测试用例

### 修复2: NO14_LongestCommonPrefix
- 修改测试输入为 `["flower", "flow", "flight"]`，期望 `"fl"`
- 或者保持输入 `["abab", "aba", ""]`，修改期望为 `""`

**推荐方案**: 修改输入为 `["flower", "flow", "flight"]`，因为这是 LeetCode 14 题的标准示例

## 执行步骤

1. 运行测试查看 3583.cpp 的具体错误
2. 修复 3583.cpp 的问题
3. 修复 NO14_LongestCommonPrefix 的测试用例
4. 重新运行测试验证修复结果
