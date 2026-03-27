# 修复 main.rs 警告计划

## 目标
消除 `main.rs` 中的所有编译器警告，使 VS Code 插件能够正确显示文件而不报错。

## 发现的警告类型

### 1. 未使用的导入
- `use std::option::Option;` (第5行) - Rust 中 Option 已自动导入，无需显式导入

### 2. 未使用的变量
- `get_hint` 函数中的 `secret` 和 `guess` 参数
- `longest_word` 函数中的 `words` 参数
- `all_paths_source_target` 函数中的 `cc` 变量

### 3. 不必要的 `mut` 声明
- `longest_word` 函数中的 `ret` 变量
- `all_paths_source_target` 函数中的多个变量

### 4. 函数/结构体未使用
- 大量 LeetCode 题解函数（这是正常的，但会产生警告）
- 对于这些函数，我们将添加 `#[allow(dead_code)]` 属性

## 修复步骤

1. **移除未使用的导入**
   - 删除 `use std::option::Option;`

2. **修复未使用的变量**
   - 在 `get_hint` 函数参数前添加下划线前缀
   - 在 `longest_word` 函数参数前添加下划线前缀
   - 在 `all_paths_source_target` 中的 `cc` 变量前添加下划线前缀

3. **移除不必要的 `mut`**
   - `longest_word` 中的 `ret`
   - `all_paths_source_target` 中的 `path`, `current` 等

4. **添加允许未使用代码的属性**
   - 在文件顶部添加 `#![allow(dead_code)]` 来抑制未使用函数的警告
   - 或者为每个函数单独添加 `#[allow(dead_code)]`

## 预期结果
- 运行 `cargo check` 和 `cargo clippy` 时无警告
- VS Code 中 Rust 插件不再显示警告
