# AST-based C Code Minifier (基于AST的C语言代码最小化工具)

这是一个使用tree-sitter AST（抽象语法树）实现的C语言源代码最小化工具。相比基于正则表达式的方法，AST方法更加准确和可靠。

## 特点 (Features)

### 相比正则表达式方法的优势

1. **更准确的语法理解**: 使用tree-sitter解析器构建完整的AST，准确理解C语言语法结构
2. **更可靠的作用域处理**: 基于AST的作用域分析，不会出现正则表达式的误判
3. **更安全的重命名**: 准确识别变量声明和使用，避免误重命名
4. **更好的边界情况处理**: 正确处理复杂的嵌套结构、宏定义、预处理指令等

### 主要功能

1. **移除注释**:
   - 自动移除单行注释 (`// ...`)
   - 自动移除多行注释 (`/* ... */`)
   - 基于AST，不会误删字符串中的注释符号

2. **移除空白**:
   - 移除不必要的空格、制表符和换行符
   - 保留必要的空格以防止语法错误（例如关键字之间）
   - 智能压缩操作符周围的空格

3. **变量重命名 (Variable Renaming / Obfuscation)**:
   - **作用域感知**: 基于AST准确识别 `{ ... }` 代码块作用域
   - **局部变量混淆**: 将函数内部的局部变量重命名为短名称（如 `a`, `b`, `c`）
   - **参数混淆**: 自动重命名函数参数（如 `int func(int arg)` -> `int func(int a)`）
   - **静态全局变量混淆**: 重命名 `static` 修饰的全局变量，不影响外部链接
   - **安全机制**:
     - **不**重命名公开的全局变量、函数名或标准库函数（如 `printf`）
     - 正确处理变量遮蔽（Shadowing），内部作用域的重命名不影响外部
     - **不**重命名结构体/联合体/枚举的成员

4. **内容保护**:
   - 完整保留字符串常量 (`"..."`) 和字符常量 (`'...'`) 的内容
   - 正确保留预处理指令（如 `#include`, `#define`）所需的换行格式

## 配置 (Configuration)

你可以通过修改 `minify.py` 文件顶部的 `ENABLE_RENAMING` 变量来控制是否启用变量重命名功能：

```python
# Configuration
ENABLE_RENAMING = True  # set to False to disable renaming
```

## 安装 (Installation)

### 依赖要求

- Python 3.8+
- tree-sitter
- tree-sitter-c

### 安装步骤

1. 创建虚拟环境（推荐）:
```bash
python3 -m venv venv
source venv/bin/activate  # Linux/Mac
# 或 venv\Scripts\activate  # Windows
```

2. 安装依赖:
```bash
pip install tree-sitter tree-sitter-c
```

或者如果已有虚拟环境：
```bash
./venv/bin/pip install tree-sitter tree-sitter-c
```

## 使用介绍 (Usage)

### 基本用法

```bash
python3 minify.py <输入文件.c>
```

或使用虚拟环境：
```bash
./venv/bin/python3 minify.py <输入文件.c>
```

默认情况下，最小化后的代码会输出到标准输出 (stdout)。通常建议将其重定向到一个新文件中：

```bash
python3 minify.py input.c > output.c
```

### 示例

假设有一个文件 `example.c`：

```c
int main() {
    // 这是一个计数器
    int counter = 100;
    return counter;
}
```

运行：
```bash
python3 minify.py example.c
```

输出可能为：
```c
int main(){int a=100;return a;}
```

## 测试介绍 (Testing)

项目包含通过 `tests/` 文件夹管理的全面测试套件，涵盖：
- **01_basic.c**: 基础功能验证
- **02_strings.c**: 复杂字符串和转义字符处理
- **03_preprocessor.c**: 宏定义与预处理指令
- **04_scopes.c**: 嵌套作用域与变量遮蔽 (Shadowing)
- **05_integrated.c**: 综合功能测试
- **06_collision.c**: 许多变量的重命名冲突测试
- **07_structs.c**: 结构体成员保护测试
- **08-14**: 各种边界情况测试

### 一键运行测试

使用 `run_tests.py` 脚本即可自动运行所有测试。该脚本会：
1. 对每个测试文件运行最小化工具
2. 编译生成的最小化代码
3. 运行编译后的程序并检查退出代码

```bash
python3 run_tests.py
```

或使用虚拟环境：
```bash
./venv/bin/python3 run_tests.py
```

输出示例：
```
Found 14 tests in ./tests

Running test: 01_basic.c... PASSED
Running test: 02_strings.c... PASSED
Running test: 03_preprocessor.c... PASSED
Running test: 04_scopes.c... PASSED
...

Summary: 14/14 passed.
```

## 实现原理 (Implementation)

### AST-based 方法

本工具使用tree-sitter解析器将C代码解析为抽象语法树（AST），然后基于AST进行以下操作：

1. **注释移除**: 遍历AST，识别所有comment节点并标记删除
2. **变量重命名**: 
   - 遍历AST，识别所有identifier节点
   - 根据节点的父节点类型判断是声明还是使用
   - 维护作用域栈，跟踪每个作用域的变量映射
   - 对于声明，生成短名称并记录映射
   - 对于使用，查找作用域链并替换
3. **代码重构**: 应用所有删除和替换操作，生成新代码
4. **空白压缩**: 在保持语法正确的前提下，最小化空白字符

### 关键优势

- **准确性**: AST保证了对C语法的准确理解
- **可靠性**: 不会因为复杂的嵌套或特殊格式而出错
- **可扩展性**: 基于AST可以轻松添加更多优化功能

## 项目结构

```
cminify/
├── minify.py          # 主程序
├── run_tests.py       # 测试运行器
├── tests/             # 测试用例目录
│   ├── 01_basic.c
│   ├── 02_strings.c
│   └── ...
└── README.md          # 本文件
```


## 贡献 (Contributing)

欢迎提交Issue和Pull Request！