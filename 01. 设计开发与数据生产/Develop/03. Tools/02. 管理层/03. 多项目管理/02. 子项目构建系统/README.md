# 子项目构建系统

## 推荐阅读顺序

Monorepo VS Multirepo > 构建系统 > Git子项目依赖

## 构建系统

各个语言和框架都有自己的构建系统。这里是一些语言的简单介绍：

1. C++，主要构建系统是 Makefile 和 CMakeLists.txt。
   - 在 Makefile  中，我们可以通过编写规则来指定如何编译和链接源代码文件。
   - 在 CMakeLists.txt  中，我们会用一种更高级的方式来管理项目，包括添加源代码、包含目录、库文件、编译参数等。
   - 此外，我们还可以使用 `add_subdirectory`  函数来添加子项目。 
2. Qt，主要构建系统是 qmake
   - 通过 .pro（项目）文件来管理项目。.pro 文件可以包含多个 .pri（包含）文件，以模块化管理项目配置。
   - `SUBDIRS` 变量可用于指定子目录，qmake 会在这些子目录中查找 .pro 文件并处理。 
3. Node.js 使用 npm 作为其包管理和构建系统
   - 通过 package.json 文件来管理项目的依赖和构建脚本。每个子项目可以有自己的 package.json 文件。 
   - 在 NPM 生态中，如果你希望在一个项目中管理和使用其它的 NPM 项目（例如库或工具），你通常需要将这些项目作为 `dependencies 或 devDependencies` 添加到父项目的 `package.json` 中
4. Python
   - 不像上述的编译型语言那样具有严格的构建系统，而是使用 setup.py 脚本及相关文件（如  MANIFEST.in、requirements.txt），通过 setuptools 来打包和构建项目。此外，Pipenv 和 Poetry  是更高级和方便的工具。 
5. Java 的构建系统有 Ant、Maven 和  Gradle
   - Ant 最初的目标是解决 Makefile 不同平台兼容性问题，但后来它一般只用于简单项目
   - Maven 通过 pom.xml  文件，提供强大的依赖管理和项目生命周期管理
   - Gradle 吸取了 Maven 和 Ant 的优点，可以实现更灵活的构建逻辑。 

以上都是本地构建系统的示例。在企业及大型项目中，经常会配合持续集成（CI）工具（如 Jenkins、Travis CI、GitHub Actions 等）来自动化构建和测试。

最后值得一提的是，尽管每个语言和框架都有自己的构建系统，然而也有**通用的构建工具**，如 Bazel 和 Buck，它们支持多语言和平台，提供一致的构建和测试环境。

## 子项目依赖类型

选型需求点

- 父项目使用者需求
  - 是否需要快捷修改子项目
  - 是否需要看子项目实现细节
  - 是否需要构建子项目
  - 是否需要被通知更新 (仅Git依赖可以实现这一需求)
- 嵌套问题
  - 三层 (顶层) 项目由多个二层项目组成，多个二层项目都依赖一个第一层的库

仓库类型

- Monorepo
  - 无独立版本号

- Multirepo
  - Git Submodule
  - Git Subtree


源码类型

- 非源码型： 项目中不包含子项目源码 / 只需要初始使用一次子项目
- 源码： 项目中包含子项目源码























