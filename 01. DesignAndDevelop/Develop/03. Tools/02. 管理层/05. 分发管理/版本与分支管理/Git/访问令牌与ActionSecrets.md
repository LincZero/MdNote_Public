# 访问令牌与ActionSecrets

## GitLab 访问令牌

### 创建

GitLab 是直接在仓库下的Setting就能看到对应选项并创建

```bash
git clone http://dependToken:glpat-CbkyNxTQ3ibn35m8dqBS@192.168.1.50/recorder/recorder.git
```

### 使用

例如：

```yml
prepare_linux_cpp:
  stage: prepare
  tags:
    - gcc48
  image: 192.168.1.208:9050/msy/android:jdk17
  script:
    - git clone http://dependToken:glpat-CbkyNxTQ3ibn35m8dqBS@192.168.1.50/recorder/recorder.git	# 这里clone，注意这里的`dependToken是令牌名`
    - mkdir -p app/src/main/cpp/cmake
    - mkdir -p app/src/main/cpp/src
    - cp -r recorder/cmake/* app/src/main/cpp/cmake
    - cp -r recorder/src/* app/src/main/cpp/src
    - cp recorder/main.cpp app/src/main/cpp/main.cpp
    - cp recorder/CMakeLists.txt app/src/main/cpp/CMakeLists.txt
    - cp recorder/config.h.in app/src/main/cpp/config.h.in
    - cp recorder/hconfig.h.in app/src/main/cpp/hconfig.h.in
  artifacts:
    paths:
      - app/
```

## GitHub 访问令牌

（感觉没GitLab的好用，坑更多）

### 创建

不同于GitLab，GitHub 相关设置不在仓库中，在个人设置里。
右上角头像 > Setting > 左侧栏 Developer Setting (一般在最下) >
左侧栏 Personal access tokens / Tokens (classic) > Generate new token > classic > 填好选项后创建成功 (推荐先创建再修改具体内容)

### 使用

除了比较常用的clone/pull/push等操作，访问令牌能调取各种 github/gitlab 的 api，例如获取CICD列表、获取构建产物等



旧版使用：

旧版的使用方式是类似[这样](https://blog.csdn.net/chengwenyang/article/details/120060010)或[这样](https://docs.github.com/zh/authentication/keeping-your-account-and-data-secure/managing-your-personal-access-tokens#%E5%9C%A8%E5%91%BD%E4%BB%A4%E8%A1%8C%E4%B8%8A%E4%BD%BF%E7%94%A8-personal-access-token)的

就是直接clone，然后会让你输入账号和密码，此时可以用tokens代替。但是现在Github由于安全原因，不再允许使用账号密码方式了。该方法不再能使用



新版使用 (将token放置到url中)：

```bash
git clone https://oauth2:[Your_Access_Token]@[Git_Host]/[User_Or_Org]/[Repo_Name].git
# 例如：
git clone https://oauth2:1234567890abcdef@github.com/user/repo.git
# 注意这里的oauth2是协议前缀，指定Git操作使用OAuth 2.0协议进行身份验证。
# 这个前缀通常与你的个人访问令牌一起使用，以便在不需要输入用户名和密码的情况下，通过令牌来验证你对GitHub仓库的访问权限。
# 这个前缀似乎是可选的，不必填
```



手把手demo：

> github的访问令牌怎么clone
>
> 我的令牌：`github_pat_11AGFN......MVrMIq`
>
> 我的仓库：`git@github.com:LincZero/MdNote_Work.git` 或 `https://github.com/LincZero/MdNote_Work.git `
>
> ---
>
> 最终命令：
>
> ```bash
> # 格式
> git clone https://YOUR_PAT@github.com/LincZero/MdNote_Work.git
> # (你会发现这个地址类似于git+https版的混合，其实就是https版多了个 `pat@` 部分而已)
> 
> # 即
> git clone https://github_pat_11AGFN......MVrMIq@github.com/LincZero/MdNote_Work.git
> ```
>
> _

### 遇到的坑

#### GitHub的令牌创建位置居然在个人设置而非仓库里

如题，害我找半天

#### classic 的细粒度太低，不能针对仓库，要用beta那个token

如题。但是这两者的设置又不太一样。前者的资料比较多，后者很少，害我又踩了些坑

#### 资料陈旧

例如现在的Github不支持帐密的问题

再例如权限名的问题：

- 例如 **classic tokens** 的权限一般只用开 repo 那几个，[参数文档](https://docs.github.com/en/apps/oauth-apps/building-oauth-apps/scopes-for-oauth-apps)

  而在 beta 版的 **fine-grained tokens** 里，这里权限的名字又有所不同，[参数文档](https://docs.github.com/en/rest/authentication/permissions-required-for-fine-grained-personal-access-tokens?apiVersion=2022-11-28)

#### 权限问题

github的访问令牌需要什么权限才能clone，我设置了：

```bash
Administration Access: Read-only
Commit statuses Access: Read-only
Contents Access: Read-only
Metadata Access: Read-only
```

然后使用：

```bash
git clone github_pat_11AGFNV...WNZ4gzta@github.com:LincZero/MdNote_Work.git
```

但报错：

```bash
......TGN7WNZ4gzta@github.com: Permission denied (publickey). fatal: Could not read from remote repository. Please make sure you have the correct access rights and the repository exists. 
```

原因：命令写错了，要用https的基础上加token才对

## 在CICD工具流中使用的技巧

**（以 GitHub 为例）**

### Actions secrets and variables

应用场景

> 我有个Github工作流权限相关问题：
>
> 例如我将网页源码分别放在三个仓库：VuePress工程、共建笔记库、只读笔记库。
>
> 其中第一个开源，第三个不开源，而第一个仓库会通过 github action 拉取“只读笔记库”的笔记。
>
> 这个时候一般的做法是什么？笔记库创建一个只读的访问令牌？然后 VuePress工程使用 Github Setting/Security/Actions 里的Repository sercrets？

设置

>  得到访问令牌后，在 Github Setting/Security/Actions 里添加一个 Secrets，例如这里我添加一个名为 “VUPRESS” 的 Secrets

工作流中使用，例如：

```yml
- name: 更新子模块到最新 (通过访问令牌)
        # ${{ secrets.VUEPRESS }}
        run: |
          export VUEPRESS_TOKEN = ${{ secrets.VUEPRESS }}
          git config --global http.extraheader "Authorization: token $VUEPRESS_TOKEN"
          git config --global url."https://x-access-token:${{ secrets.VUEPRESS }}@github.com/".insteadOf "https://github.com/"
          git submodule foreach git pull origin main
```

### 环境config方法

有时我们不仅是使用 clone 方法，例如在 CICD 中使用：

```yml
- name: 更新子模块到最新 (通过访问令牌)
        # ${{ secrets.VUEPRESS }}
        run: |
          export VUEPRESS_TOKEN = ${{ secrets.VUEPRESS }}
          git config --global http.extraheader "Authorization: token $VUEPRESS_TOKEN"
          # 或
          git config --global url."https://x-access-token:${{ secrets.VUEPRESS }}@github.com/".insteadOf "https://github.com/"
          git submodule foreach git pull origin main
```

### CICD语法糖

通过 `uses: actions/checkout@v3` (或v4)，可以很方便地处理好子模块、以及token。

不需要也不能像前面那样再通过 `git config --global ...` 来配置tokens，否则会因为重复设置 tokens 报错 重复头 问题

```yml
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
```

## 组织令牌问题

Github的token太奇怪了，不在仓库中……文档也没说，找了半天

1. 首先需要在组织中开启允许个人创建令牌的开关（但他不叫这个）
   https://docs.github.com/en/authentication/keeping-your-account-and-data-secure/managing-your-personal-access-tokens
2. 然后接下来的流程同个人创建tokens，在个人设置>开发者选项里设置
3. 此时需要注意！你可以在这个页面里先切换资源拥有者，切换成组织（如果这里没看到组织，就是你在组织那没设置好）
4. 切回去组织里，Personal access tokens > Active tokens，看一下token生效了没

## user:token还是只token？

在有的资料中，我看到格式是 `https://<user>:<secrets>@github.com/...` ，但有的资料却有没最前面那个 `user`。

反正我试下来就是：

- github的话。不加直接user也行加也行，加的话他是用户名（如果是组织token也是填你的个人用户名）。不是组织名，也不是token名
- gitlab的话。不加似乎不行（不知道是不是与设置有关），提示上是 `dependToken:` `oauth2:`，我忘了具体是什么来着，和github的似乎不一样。不是填用户名，好像是填token名，或者固定字符 `oauth2`？













