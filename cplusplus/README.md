# C++ 算法题解

本目录包含使用 C++ 语言实现的 LeetCode 算法题解。

## 技术栈

- **语言**: C++17 标准
- **构建工具**: CMake 3.31+
- **测试框架**: Google Test
- **代码格式化**: ClangFormat

## 代码结构

```
cplusplus/
├── questions/              # 每日一题（按题目编号命名）
│   ├── 1.cpp
│   ├── 2.cpp
│   └── ...
├── top150/                # 面试经典 150 题
│   ├── array/             # 数组相关题目
│   │   ├── top150_no121_best_time_to_buy_sell_stock.cpp
│   │   └── ...
│   └── string/            # 字符串相关题目
│       ├── top150_28.cpp
│       └── ...
├── CMakeLists.txt         # CMake 构建配置文件
├── .clang-format          # ClangFormat 配置文件
└── README.md              # 项目说明文档
```

## 编译与运行

### 构建项目

```bash
# 进入 C++ 项目目录
cd cplusplus

# 创建构建目录并编译
mkdir -p build && cd build
cmake ..
make
```

### 运行测试

```bash
# 运行所有测试
./tests

# 或者使用 ctest
ctest --verbose
```

### 代码格式化

```bash
# 使用 ClangFormat 格式化代码
clang-format -i *.cpp
clang-format -i */*.cpp
```

## 代码规范

- **标准**: C++17
- **缩进**: 4 个空格，不使用 Tab
- **行宽限制**: 120 字符
- **格式**: 遵循 Google C++ Style (通过 `.clang-format` 配置)
- **命名规范**:
  - 类名: `PascalCase` (如 `Solution`)
  - 函数名: `snake_case` (如 `two_sum`)
  - 变量名: `snake_case` (如 `max_length`)
- **头文件**: 使用 `#pragma once` 或标准头文件保护

## 注意事项

- 新增题目时，请确保代码注释完整，包含题目描述和解题思路
- 测试用例应包含基本测试用例和边界条件测试
- 保持代码风格一致，使用 ClangFormat 确保代码质量
- 避免使用 `using namespace std;` 在头文件中
- 避免使用裸指针，优先使用智能指针
- 不要提交编译生成的文件 (已配置 `.gitignore`)
- 避免代码中出现硬编码的魔法数字
- 不要使用已过时的 C++ 特性

## 参考资料

- [C++ 标准库参考](https://en.cppreference.com/w/)
- [LeetCode 官网](https://leetcode.com/)
- [Google C++ 风格指南](https://google.github.io/styleguide/cppguide.html)
- [CMake 官方文档](https://cmake.org/documentation/)
