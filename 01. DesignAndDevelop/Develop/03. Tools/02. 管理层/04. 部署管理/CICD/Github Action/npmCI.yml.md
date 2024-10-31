---
type: yml
---
# npmCI.yml

```yaml
name: Node.js CI/CD Pipeline  # 工作流名

on:                           # 触发器，定义何时运行此工作流
  push:
    branches: [master]        # 默认分支名!
  pull_request:
    branches: [master]
  workflow_despatch:

jobs:                         # 工作流
  build:                      # 作业名
    runs-on: ubuntu-latest    # 环境 - 基于镜像
    steps:                    # 作业步骤！
    - uses: actions/checkout@v3   # 环境 - 检出代码 (使用的是官方提供的action)
    - name: Use Node.js           # 环境 - node环境 (使用的是官方提供的action)，Node.js版本
      uses: actions/setup-node@v3
      with:
        node-version: '20'
    - run: npm ci                 # 脚本 - 安装依赖，npm ci代替npm install以获得更快的速度
    - run: npm run build          # 脚本 - 构建脚本
    - name: Upload Build Artifact # 其他 - 保存构建产物 (使用的是官方提供的action)
      if: always()                    # 即使之前的构建步骤失败，也会上载构建产物
      uses: actions/upload-artifact@v3
      with:
        name: build-artifact          # 构建产物的名称
        path: |                       # 构建产物的路径
          main.js
          styles.css
          manifest.json
```

```yml
name: Node.js CI/CD Pipeline  # 工作流名

on:                           # 触发器，定义何时运行此工作流
  push:
    branches: [main]          # 默认分支名!
  pull_request:
    branches: [main]
    workflow_dispatch:        # 手动执行

jobs:                         # 工作流
  build:                      # 作业名
    runs-on: ubuntu-latest    # 环境 - 基于镜像
    steps:                    # 作业步骤！(name是可选的，但我都加上了方便调试和修改)
    - name: checkout repo
      uses: actions/checkout@v3   # 检出代码 (使用的是官方提供的action)
    - name: env use node.js
      uses: actions/setup-node@v3 # 配置node环境 (使用的是官方提供的action)，Node.js版本
      with:
        node-version: '20'
    - name: npm depend1
      run: npm ci                 # (npm ci代替npm install以获得更快的速度)
    - name: npm depend2
      working-directory: ./src/ABConverter/
      run: npm ci
    - name: npm build
      run: npm run build
    - name: upload build artifact
      if: always()                      # 即使之前的构建步骤失败，也会上载构建产物
      uses: actions/upload-artifact@v3  # 保存构建产物 (使用的是官方提供的action)
      with:
        name: build-artifact            # 构建产物的名称
        path: |                         # 构建产物的路径
          main.js
          styles.css
          manifest.json
```
