# Git子项目依赖

## git项目依赖的多种选择

GPT



一个项目依赖另一项目应该使用哪种方式比较好：

1. git依赖，从仓库clone时自动拉取另一个依赖项目到指定位置
2. cmake编译/install时，再进行依赖安装
3. 进行CICD时，ci文件先进行对依赖项的clone，再进行编译

---

每种方式具有其自己的优点和适用场景，以下是一些可能的推荐：

1. Git 依赖（使用git submodules或者git subtrees）
   - 这种方式适合于你**经常需要更新或者修改依赖项的源代码**的场景。你可以在你的项目中直接编辑和更新依赖项的代码，并且可以很方便地跟踪这些改动。但是，如果你只是简单地使用依赖项而不需要对其代码做修改，这种方式可能会引入一些不必要的复杂性。 
2. CMake 编译/install 时，再进行依赖安装
   - 这种方式比较适合于你的依赖项是一些库或者编译工具，你不需要修改它们的代码，只需要在编译你的项目时使用它们。CMake可以自动下载和安装这些依赖项，这对于用户来说是比较方便的。 
3. 进行 CI/CD 时，ci文件先进行对依赖项的clone，再进行编译
   - 这种方式适合于你的项目已经有一个设定的CI/CD流程，你希望在每次构建时都能确保使用最新的依赖项。这种方式可以自动完成依赖项的更新和安装，无需用户手动介入。 

故对于哪种方式比较好，将取决于你特定的项目需求及你对软件建构流程的个人偏好。

还有其他的方式来处理项目间的依赖关系。例如，你可以使用包管理器（如Python的pip，JavaScript的npm或者C++的Conan）来管理你的依赖项。包管理器最大的优点是可以自动处理依赖项的版本和更新，而且通常配有大量的开源库供你选择。

---

选择

---

选择哪种方式，取决于你的特定需求。一些可能的考虑因素包括：

1. 你需要对依赖项目进行多少修改？如果你需要**频繁地修改**依赖项，可能**Git依赖**会更方便些。 
2. 你的项目有多少自动化？如果你的项目有自动化的构建和部署流程，CI/CD可能会更合适。 
3. 你的依赖项有多复杂？如果你的依赖项有很多，并且还有自己的依赖关系，包管理器可能会更好。 

---

使用

---

- git依赖
  - 你可以使用 `git submodule add` 命令来添加一个新的子模块，然后你就可以在你的仓库中直接编辑子模块的代码了。当你将改动推送到GitHub时，也需要将子模块的改动同时推送。 
- cmake依赖
  - 你需要在你的 CMakeLists.txt 文件中使用 `find_package` 或者 `add_subdirectory` 命令来添加你的依赖项。然后CMake会在编译时自动下载和安装这些依赖项。 
- CI/CD依赖
  - 你需要在你的CI配置文件中添加把依赖项作为构建步骤的一部分。例如，如果你使用的是GitHub Actions，你可以在你的工作流文件中添加一个新的步骤来clone你的依赖项的仓库。 
- 包管理器依赖
  - 你只需在你的项目配置文件中指明你的依赖项和对应的版本。包管理器会自动下载和安装所需的所有依赖项。例如：
    - Python的requirements.txt文件
    - JavaScript的package.json文件
    - C++的conanfile.txt文件

## Git Submodule & Git Subtree

### 简单介绍

- Git Submodule 是指建立 main repo 与 sub repo  的 HEAD commit 连结

- Git Subtree 是指将 main repo 包含 commit log 全部 copy 到新的 repo 中 

### 与 Monorepo & Multirepo 关系

[Git Submodule](http://shachiku.life/posts/difference-between-subtree-and-submodule/) 或 [Git Subtree](https://blog.darkthread.net/blog/git-subtree-notes/https://blog.puckwang.com/posts/2020/git-submodule-vs-subtree/) 都属于是 Multi-Repo 理念，而非 Monorepo



看上去，Git Subtree 是 monorepo，而 Git Submodule 是 multirepo。但正如我一开始说的，他们都是 multirepo

在某种程度上，您可以将 Git Subtree 与 Monorepo 模式联系起来，将 Git Submodule 与 Multirepo 模式联系起来。但它们并非严格的等同。

Monorepo（单体仓库）是一种将所有代码都存储在一个大型仓库中的策略，而不是将代码划分到各个单独的项目仓库中去。Git Subtree可以实现这种策略，因为它允许你将一个子仓库的内容包含到父仓库中，并且子仓库的所有更改也将出现在父仓库中。



git subtree除了可以理解为将子项目包含进父仓库中，是否也可以理解为，将父项目的一部分分离为一个子项目。

是的，使用Git Subtree，你既可以将其他库作为子项目引入到你的项目中，也可以将你的项目中的分支或目录作为一个新的Git项目进行管理。

（这个有点像公司旧Recorder的SVN存储方式）

### 比较

- Git Submodule 是指建立 main repo 与 sub repo  的 HEAD commit 连结
  - 特点：Submodule允许你将一个Git仓库作为另一个Git仓库的子仓库进行管理，它们依然是分开的，仍然保持各自独立的项目结构，**各自有各自的版本库和历史记录**。
  - 优点：这样如果你对子模块做出任何改变，不会影响主项目。如果你的项目需要包含其他项目，并且希望它们可以独立开发和版本控制，那么Submodule就很适合。 
  - 缺点：Submodule并不会跟随主项目同步更新。当主项目更新时，Submodule不会自动更新，需要手动更新。对于需要跟踪和管理许多子模块的项目来说，使用Submodule可能会变得复杂且难以处理。 

- Git Subtree 是指将 main repo 包含 commit log 全部 copy 到新的 repo 中
  - 特点：先将子项目的内容合并到一个目录中，然后将这个目录作为一个新的提交添加到父项目中。这样父项目就会有一个包含所有子项目代码的目录。这种方式下，所有的内容和历史记录都会以父项目的方式存在，可以让你直接把其**当作主项目的一个部分**来处理。 
  - 优点：这种方式的好处在于简单且易于使用，不需要额外的步骤就可以**看到所有的代码以及历史记录**，你将一个项目作为一个子树加入，他会和主项目一样更新和提交
  - 缺点：但如果你想把修改推送回子项目，这需要额外的步骤和注意事项。 





- **Git Submodule**：这是Git官方以前的推荐方案
- **Git Subtree**：从 Git 1.5.2 开始，Git 新增并推荐使用这个功能来管理子项目

submodule 与 subtree对比

- git submodule
  - 允许其他的仓库指定以一个commit嵌入仓库的子目录
  - 仓库 clone下来需要 init 和 update
  - 会产 .gitmodule 文件记录 submodule 版本信息
  - git submodule 删除起来比较费劲
- git subtree
  - 避免以上问题
  - 管理和更新流程比较方便
  - git subtree合并子仓库到项目中的子目录。不用像submodule那样每次子项目修改了后要init和update 。万一哪次没update就直接add . 将.gitmodule 也 commit上去就悲剧了
  - git v1.5.2 (2007年) 以后建议使用git subtree





- Git Submodule
  - 优点
    - 独立性：Submodules允许你将一个Git仓库作为另一个Git仓库的子目录。这使得每个Submodule可以拥有独立的历史记录
    - 避免冗余：如果多个项目使用相同的库，但是这些库又不经常更新，那么使用Submodule是一个好主意，因为它避免了代码库的冗余
    - 灵活性：不同的项目可以引用同一库的不同版本
  - 缺点
    - 复杂性：Submodules的主要缺点是它们的**复杂性**。它们在一些常用操作（如克隆和拉取）中需要额外的步骤，并可能产生混乱，特别是对于新手来说。
    - 跨Submodule工作困难：跨Submodule的工作也更加困难，这可能导致更多的提交。 
- Git Subtree
  - 优点
    - 简洁性：Subtree种植**简单**，你不必担心忘记下载额外的Submodules，或者理解需要处理Submodules的复杂命令。
    - 集中化：Subtree意味着你在主仓库中有一个完整的、唯一的**历史记录**，这比Submodule更加**集中**。
    - 跨仓库工作方便：使用Subtree，你可以在**主仓库中直接编辑子目录**，而无需在Submodules之间切换。 
  - 缺点
    - 冗余：如果**多个项目使用相同的库**，Subtree可能导致代码冗余。
    - 独立性较差：若需要在库的不同版本之间切换，则Subtree可能无法满足此类需求。 
- 结论
  - 选择使用Submodule还是Subtree，取决于你的具体需求。 
  - 如果你需要独立的项目和历史记录，或者希望避免代码冗余，那么可能会选择Submodule。
  - 相反，如果你希望管理起来更简洁，无需在多个 submodule 之间切换，那么 Subtree 可能是更好的选择。





##  Git Submodule

转载：https://www.jianshu.com/p/9000cd49822c

经常碰到这种情况：当你在一个Git 项目上工作时，你需要在其中使用另外一个Git 项目。也许它是一个第三方开发的Git 库或者是你独立开发和并在多个父项目中使用的。这个情况下一个常见的问题产生了：你想将两个项目单独处理但是又需要在其中一个中使用另外一个。

在Git 中你可以用子模块`submodule`来管理这些项目，`submodule`允许你将一个Git 仓库当作另外一个Git 仓库的子目录。这允许你克隆另外一个仓库到你的项目中并且保持你的提交相对独立。

### 初始化

#### 初始化，指定子项目

此文中统一将远程项目`https://github.com/maonx/vimwiki-assets.git`克隆到本地`assets`文件夹。

```bash
$ git submodule add https://github.com/maonx/vimwiki-assets.git assets
```

添加子模块后运行`git status`, 可以看到目录有增加1个文件`.gitmodules`, 这个文件用来保存子模块的信息。

```bash
$ git status
On branch master

Initial commit

Changes to be committed:
  (use "git rm --cached <file>..." to unstage)

    new file:   .gitmodules
    new file:   assets
```

#### 克隆包含子模块的项目 - 先clone父再更新子

克隆包含子模块的项目有二种方法：一种是先克隆父项目，再更新子模块；另一种是直接递归克隆整个项目。

```bash
$ git clone https://github.com/maonx/vimwiki-assets.git assets # 克隆父项目

$ git submodule # 查看子模块
 -e33f854d3f51f5ebd771a68da05ad0371a3c0570 assets # 子模块前面有一个-，说明子模块文件还未检入（空文件夹）
 
$ git submodule init # 初始化子模块，初始化模块只需在克隆父项目后运行一次
Submodule 'assets' (https://github.com/maonx/vimwiki-assets.git) registered for path 'assets'、

$ git submodule update # 更新子模块
Cloning into 'assets'...
remote: Counting objects: 151, done.
remote: Compressing objects: 100% (80/80), done.
remote: Total 151 (delta 18), reused 0 (delta 0), pack-reused 70
Receiving objects: 100% (151/151), 1.34 MiB | 569.00 KiB/s, done.
Resolving deltas: 100% (36/36), done.
Checking connectivity... done.
Submodule path 'assets': checked out 'e33f854d3f51f5ebd771a68da05ad0371a3c0570'
```

#### 克隆包含子模块的项目 - 递归clone

递归克隆整个项目，子模块已经同时更新了，一步到位

```bash
git clone https://github.com/maonx/vimwiki-assets.git assets --recursive 
```

### 通用方法

这里是一个让子模块类似普通模块一样的使用方式：

`git submodule foreach` + 普通命令。例如：

```bash
git submodule foreach git pull origin main
```

### 修改推拉

#### 更新子模块

- 更新项目内子模块到最新版本

  ```bash
  $ git submodule update
  ```

- 更新子模块为远程项目的最新版本

  ```
  更新子模块为远程项目的最新版本 
  ```

#### 修改子模块

在子模块中修改文件后，直接提交到远程项目分支

```bash
$ git add .
$ git ci -m "commit"
$ git push origin HEAD:master
```

### 其他

#### 查看子模块

```bash
$ git submodule
 e33f854d3f51f5ebd771a68da05ad0371a3c0570 assets (heads/master)
```

#### 删除子模块

**删除子模块比较麻烦，需要手动删除相关的文件，否则在添加子模块时有可能出现错误**
同样以删除`assets`文件夹为例

```bash
# 删除子模块文件夹
$ git rm --cached assets
$ rm -rf assets

# 删除.gitmodules文件中相关子模块信息
[submodule "assets"]
  path = assets
  url = https://github.com/maonx/vimwiki-assets.git
  
# 删除.git/config中的相关子模块信息
[submodule "assets"]
  url = https://github.com/maonx/vimwiki-assets.git
  
# 删除.git文件夹中的相关子模块文件
$ rm -rf .git/modules/assets

# 清完之后可能还需要commit一次，才能成功
```

## Git Subtree

### 初始化

#### 父项目部分分离为子项目

用Git Subtree将父项目的一部分分离为子项目的过程通常包括以下步骤：

```bash
# 将你想要分离的部分作为一个新的分支检出
# 例如，如果你想要将 `dir` 目录作为一个新的项目，你像下面这样做
# 这将会创建一个名为`new_project`的新分支，其中只包含`dir`目录的历史。 
git subtree split --prefix=dir --branch new_project

# 将这个新的分支推送到新的仓库
# 你可以先在远程Git服务器上创建一个新的仓库（我们假设叫做`new_repo`），然后将`new_project`分支推送到那里
# 这将会将你的 `new_project` 分支作为 `new_repo` 仓库的 `master` 分支
git push new_repo new_project:master
```


在这个过程中，你的原始项目（包括它的历史）将会保持不变。只有`dir`目录的历史被复制到了新的仓库。

并且，随后在父项目中对`dir`目录的改动，不会自动在新的仓库中反映。不过，你可以执行`git subtree push`命令，将这些改动推送到新的仓库。同样地，如果你在新的仓库中做了改动，并且想要将这些改动合并回父项目，你可以执行`git subtree pull`

#### 子项目插入到父项目

```bash
git sutree add --prefix=src/Common https://github.com/M76chao/Common.git master
```

### 修改推拉

#### 推送到子项目仓库

在主项目 git push 之后，对子项目修改的内容是不会直接更新到子项目自身的

需要执行 `git subtree push`

```bash
git subtree push --prefix=commonTools http://git.ninebot.cn:8888/tingtingtina/commontoolscopy.git master
```

#### 子项目仓库更新

如果单独对子项目做了更新，主项目就需要手动更新下了

```bash
$ git subtree pull --prefix=commonTools http://git.ninebot.cn:8888/tingtingtina/commontoolscopy.git master --squash
```

执行之后，仍然会在主项目中生成相关的 commit 记录

在 subtree 相关命令经常会用到 `<repository>` 每次都写地址还是比较麻烦，这里可以用 `git remote` 命令简化写法，为这个远程地址定义一个 “别名”

```bash
$ git remote add utils http://git.ninebot.cn:8888/tingtingtina/commontoolscopy.git
```

比如使用 subtree push 的时候就可以使用如下命令

```bash
$ git subtree push --prefix=commonTools utils master
```

### 其他

#### 移除子项目（切换子项目分支）

在添加 subtree 的时候是指定了分支的，如果要切换分支直接移除 subtree，重新加入子项目的分支

```bash
git rm <subtree>
git commit
git subtree add --prefix=<subtree> <repository_url> <subtree_branch>
```

# 实践

我的个人 vuepress 项目引入个人魔改的 `vupress-theme-hope` 主题，详见 VuePress2/Hope主题/Private/个人魔改 笔记

```bash
# 初始化
$ cd /h/Git/Private/LincZero-Vuepress
$ git submodule add git@github.com:LincZero/vuepress-theme-hope.git lib # 添加子项目
$ git submodule init   # 初始化子项目
$ git submodule update # 更新子项目
$ git submodule status # 检查子项目

# 构建子项目
$ cd lib
$ pnpm i
$ pnpm build
$ cd ../

# 替换依赖
$ pnpm uninstall vuepress-theme-hope # (之前用npm仓库的vuepress主题的话)
# 此时 "vuepress-theme-hope": "2.0.0-beta.237" 这一行没了，我们需要将其替换成新的本地路径：
"dependencies": {
    # 下面两种写法 pnpm i 正常，但后面运行 pnpm docs:dev时报错：Error [ERR_MODULE_NOT_FOUND]: Cannot find package 'H:\Git\Private\LincZero-Vuepress\node_modules\vuepress-theme-hope\' imported from H:\Git\Private\LincZero-Vuepress\src\.vuepress\config.ts.5ca87adb.mjs
	# "vuepress-theme-hope": "file:lib",
	# "vuepress-theme-hope": "file:lib/packages/theme/lib", 
	
    # 这种写法 pnpm i 会报错： ERR_PNPM_NO_MATCHING_VERSION_INSIDE_WORKSPACE  In : No matching version found for vuepress-theme-hope@* inside the workspace
	"vuepress-theme-hope": "workspace:*"
}
$ pnpm i

# 运行
$ pnpm docs:dev
```

















