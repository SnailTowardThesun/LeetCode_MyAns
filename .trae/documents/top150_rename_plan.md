# Top150 文件夹重命名计划

## 任务分解和优先级

### [ ] 任务1: 重命名array文件夹内的文件
- **Priority**: P0
- **Depends On**: None
- **Description**:
  - 为array文件夹内的所有.cpp文件添加top150_前缀
  - 例如：no121_best_time_to_buy_sell_stock.cpp → top150_no121_best_time_to_buy_sell_stock.cpp
- **Success Criteria**:
  - array文件夹内所有文件都以top150_开头
- **Test Requirements**:
  - `programmatic` TR-1.1: 列出array文件夹内容，确认所有文件都有top150_前缀
- **Notes**: 保持文件名其余部分不变，只添加前缀

### [ ] 任务2: 重命名string文件夹内的文件
- **Priority**: P0
- **Depends On**: 任务1完成
- **Description**:
  - 为string文件夹内的所有.cpp文件添加top150_前缀
  - 例如：28.cpp → top150_28.cpp，no12_integer_to_roman.cpp → top150_no12_integer_to_roman.cpp
- **Success Criteria**:
  - string文件夹内所有文件都以top150_开头
- **Test Requirements**:
  - `programmatic` TR-2.1: 列出string文件夹内容，确认所有文件都有top150_前缀
- **Notes**: 注意处理没有no前缀的文件，如28.cpp

### [ ] 任务3: 检查文件注释和代码实现
- **Priority**: P1
- **Depends On**: 任务2完成
- **Description**:
  - 检查每个重命名后的文件，确保注释完整
  - 注释应包含题目描述、解题思路
  - 检查代码实现是否符合C++代码规范
- **Success Criteria**:
  - 所有文件都有完整的中文注释
  - 代码实现符合项目的C++代码规范
- **Test Requirements**:
  - `human-judgement` TR-3.1: 随机抽查3-5个文件，检查注释完整性
  - `human-judgement` TR-3.2: 检查代码格式和命名规范
- **Notes**: 参考CLAUDE.md中的代码规范

### [ ] 任务4: 提交代码到Github
- **Priority**: P1
- **Depends On**: 任务3完成
- **Description**:
  - 提交重命名后的文件到Github仓库
  - 确保提交信息清晰明了
- **Success Criteria**:
  - 代码成功提交到Github
  - 提交信息包含重命名操作的说明
- **Test Requirements**:
  - `programmatic` TR-4.1: 执行git push命令，确认无错误
- **Notes**: 提交前确保所有修改都已保存

## 实施步骤

1. 首先执行任务1，重命名array文件夹内的文件
2. 然后执行任务2，重命名string文件夹内的文件
3. 接着执行任务3，检查文件注释和代码实现
4. 最后执行任务4，提交代码到Github

## 注意事项

- 重命名时保持文件内容不变，只修改文件名
- 确保所有文件都有top150_前缀
- 检查注释是否完整，使用中文编写
- 提交前确认所有修改都已完成