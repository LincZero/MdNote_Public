# VuePress实践，GitHub and GitLab Pages

## Reference

项目参考个人网站项目：https://github.com/LincZero/LincZero.github.io

部署文档参考VuePress Hope主题部署文档：https://vuejs.press/zh/guide/deployment.html#gitlab-pages

## Why Not Gitee

一开始仅使用 GitHub Page 进行部署，但后来发现部分国内网友无法访问。于是在国内平台又进行了部署，选择了 GitLab Page。

Q：Why not Gitee？

A：https://myzye.com/posts/bebaa7f/，我后来也去验证了这个问题，确实是关闭不可用了（2024-06-22）

## GitLab Import GitHub Repo（镜像仓库）

### 方法

参考：

- https://www.cnblogs.com/kimiliucn/p/17693383.html
- https://www.bilibili.com/video/BV13u411L7ga

这个链接里教了：

- GitLab上自动推送到GitHub/Gitee
- Gitee上自动拉取/推送到GitHub
- （这里就有点奇怪了，Gitee上似乎能选择Push/Pull，但GitLab上似乎锁定了Pull，而无法设置Push方向）

例如 ：

- GitLab同步到GitHub：GitLab上设置：项目 > 左侧设置/仓库 > 镜像仓库。但方向只能选推送，所以没用
- Gitee自动拉取GitHub：GitLab上新建项目时选导入，然后在仓库 > 管理 > 仓库镜像管理 (限时开放) > 然后配置。需要注意下GitHub的token需要开启一个admin:repo_hook的授权 (名字叫Webhooks，在倒数第二个)，还算简单

### (扩展) Webhook

这里有一个通用概念：Webhook

参考：https://www.redhat.com/zh/topics/automation/what-is-a-webhook

#### 概述

Webhook 是一种基于 HTTP 的回调函数，可在 2 个应用编程接口（API）之间实现事件驱动的轻量级通信。许多 Web 应用都使用 Webhook 来接收来自其他应用的少量数据，但 Webhook 也可用于在 GitOps 环境中触发自动化工作流。

#### `Web API` vs `Webhook`

要设置 Webhook，客户端需向服务器 API 提供唯一的 URL，并指定其要了解的事件。设置 Webhook 后，客户端不再需要轮询服务器。发生特定的事件时，服务器会自动将相关的有效负载发送到客户端的 Webhook URL。 

Webhook 通常被称为“反向 API” 或“推送 API”，因为通信责任落在了服务器而非客户端上。与客户端不断发送 HTTP 请求来请求数据，直至服务器作出响应的方式不同，服务器在数据可用时会立即向客户端发送一个 HTTP POST 请求。虽然有这些别名，但其实 Webhook 并非 API，二者可以结合使用。应用必须具有 API 才能使用 Webhook。 

### GitLab 无法 Pull 问题的踩坑

> 1. Gitee的仓库镜像能支持自动从GitHub中Push和Pull，但 Gitee Page 现在已经暂停服务了
> 2. GitLab的Page似乎还能用，但其镜像功能似乎只能Push，无法切换Pull
> 3. 所以现在我得Gitee自动Pull Github再自动Push GitLab，然后将页面同步到GitLab Page上？好傻啊，不想这么搞
>
>
> 不一定要顺着上面的思路搞。本质问题是：GitHub Page我已经部署过了，但想多部署一个不用魔法上网的环境，如果各位大佬有其他方法也是可以

后来根据群友建议，放弃了，换用了 CloudFlare Pages 方案且成功了。详见 CloudFlare Pages 相关笔记

## YML

### Gitee yml（Page暂停服务，废弃）

（Page暂停服务，废弃）

### GitHub yml

```yml

name: 部署文档

on:
  push:
    branches:
      # 确保这是你正在使用的分支名称
      - main
  workflow_dispatch:

permissions:
  contents: write

jobs:
  deploy-gh-pages:
    runs-on: ubuntu-latest
    steps:
      - name: Checkout
        uses: actions/checkout@v4
        with:
          fetch-depth: 0
          # 如果你文档需要 Git 子模块，取消注释下一行
          submodules: true
          token: '${{ secrets.VUEPRESS }}'

      - name: Checkout - 更新子模块到最新
        run: |
          git submodule foreach git pull origin main

      - name: 安装 pnpm
        uses: pnpm/action-setup@v2
        with:
          run_install: true
          version: 8


      - name: 设置 Node.js
        uses: actions/setup-node@v3
        with:
          node-version: 20
          cache: pnpm


      - name: 构建文档
        env:
          NODE_OPTIONS: --max_old_space_size=8192
        run: |-
          pnpm run docs:build
          > src/.vuepress/dist/.nojekyll

      - name: 部署文档
        uses: JamesIves/github-pages-deploy-action@v4
        with:
          # 这是文档部署到的分支名称
          branch: gh-pages
          folder: src/.vuepress/dist

```

### GitLab Yml（未实验）

```yml
# 选择你要使用的 docker 镜像
image: node:18-buster

pages:
  # 每当 push 到 main 分支时触发部署
  only:
    - main

  # 缓存 node_modules
  cache:
    key:
      files:
        - pnpm-lock.yaml
    paths:
      - .pnpm-store

  # 安装 pnpm
  before_script:
    - curl -fsSL https://get.pnpm.io/install.sh | sh -
    - pnpm config set store-dir .pnpm-store

  # 安装依赖并运行构建脚本
  script:
    - pnpm install --frozen-lockfile
    - pnpm docs:build --dest public

  artifacts:
    paths:
      - public

```























