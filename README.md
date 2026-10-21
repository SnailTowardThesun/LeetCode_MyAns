# LeetCode_MyAns
My submission of leetcode
Here's my code of leetcode

## 使用 Turborepo 管理

本仓库使用 Turborepo 进行代码管理，支持以下命令：

### 安装依赖
```bash
npm install
```

### 构建所有项目
```bash
npm run build
```

### 运行所有测试
```bash
npm run test
```

### 运行所有代码格式化
```bash
npm run lint
```

### 项目结构
- `cplusplus/` - C++ 实现的 LeetCode 题解
- `rust/` - Rust 实现的 LeetCode 题解
- `python/` - Python 实现的 LeetCode 题解（uv 管理，详见 [python/README.md](python/README.md)）


### 各项目命令

#### C++ 项目
- 构建：`npm run build --workspace=cplusplus`
- 测试：`npm run test --workspace=cplusplus`
- 格式化：`npm run lint --workspace=cplusplus`

#### Rust 项目
- 构建：`npm run build --workspace=rust`
- 测试：`npm run test --workspace=rust`
- 格式化：`npm run lint --workspace=rust`

#### Python 项目
- 构建（初始化 uv 环境）：`npm run build --workspace=python`
- 测试：`npm run test --workspace=python`
- 格式化：`npm run lint --workspace=python`


