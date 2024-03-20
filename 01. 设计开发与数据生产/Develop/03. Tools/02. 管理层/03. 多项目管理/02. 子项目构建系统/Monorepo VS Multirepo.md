# Monorepo VS Multirepo

## 三种架构模式

### Monolith (单架构)

### Monorepo (单仓库)

Monorepo 是一种代码管理策略，把所有的项目代码都放在一个仓库里，每一个项目、每一个服务或者是每一个包就是这个仓库的一个子目录。

"Monorepo" 这个词是 “Monolithic Repository” 的缩写, 中文可以翻译为"单体仓库"。

一般对比另一种策略 -- Multirepo（多仓库），每一个项目或者包都使用一个独立的仓库进行管理。 

在Monorepo的代码管理方式下：

1. 共享代码非常方便：由于所有项目都在同一个仓库下，它们可以直接引用其他项目的代码，而不需要发布和维护各种共享库。 
2. 一致性：所有的项目都可以统一使用相同的构建工具和配置，所有人都在一份代码库上工作，大大提高了开发效率。 
3. 协同开发更简单：无需在多个仓库之间切换，项目之间的协作更为方便。 
4. 对整个项目的更改可以很容易看到，在提交代码时可以很容易地看到哪些服务或者包可能会受到影响。 

但是Monorepo也不是没有缺点的，因为所有的代码都在一个仓库里，所以这个仓库的规模可能会变得很大，对于资源和权限的管理可能会带来一些挑战。

谷歌、Facebook、微软和Twitter等大公司都在使用 Monorepo 管理他们的代码库。

### Multirepo (多仓库)

## 简单总结

### 使用场景

以前msy公司recorder项目还在用svn时，就属于单仓库，后来迁移到git后，就使用多仓库管理了

### 比较

Monorepo 和 Multirepo 是两种不同的代码存储库管理结构，各有自己的优点和缺点。

- Monorepo（单仓库）

  - 优点
    - 代码共享和重用：在单一存储库中，所有项目和代码都处于同一位置，使得代码共享和重用变得更简单
    - 协作：开发者可以更容易地跨项目协作
    - 简化构建和测试过程：构建工具可以在整个项目中运行，提供全局测试和构建
    - 统一版本：Monorepo 用一个存储库来存储所有代码，所有的变更都有统一的版本历史 

  - 缺点
    - 规模问题：随着项目和代码行数的增加，Monorepo 的大小会越大，可能会导致性能问题
    - 权限管理和安全性：在一个大型的仓库中，正确地设置代码的访问权限可能会更加复杂

- Multirepo（多仓库）

  - 优点
    - 简单性：每个项目都有自己的仓库，可以独立地管理和运行它，使得结构和管理变得更简单
    - 适用于小型团队：如果团队或项目较小，多仓库的方式更适合
    - 独立性：变更不会影响到其他项目
  - 缺点
    - 重复性工作：例如，如果需要更改或更新所有项目的某个公共库，可能需要在所有仓库中手动进行
    - 分散管理：需要在多个仓库中进行代码审查和合并
    - 版本管理：可能需要在多个仓库中跟踪和管理版本，同时需要更多的工具和流程来维护版本一致性

总的来说，选择使用哪种方式主要取决于项目的具体需求和团队的喜好

### GPT简单调研

Q：从各种项目的语言、框架来看，分别哪种比较受欢迎？比如Cpp、java、python、node.js的npm

---

选择Monorepo还是Multirepo并不完全取决于使用的编程语言或框架，而是取决于团队的协作方式、项目规模、开发流程等因素。但是，有些语言和框架的生态系统，可能使一种方式更受欢迎。

- C++

  - Monorepo：C++的构建系统（如Bazel和Buck等）在Monorepo体系中表现出色，谷歌和Facebook等公司都采用了这种方案。
  - Multirepo：但以C++为主的一些开源项目（如LLVM）还是采用多个仓库来组织代码。 

- Java

  - Monorepo：像谷歌和Twitter这样的大公司倾向于使用Monorepo来管理他们的Java项目。
  - Multirepo：然而，Java的包管理工具（如Maven和Gradle）在多仓库环境中也能很好地工作。 

- Python

  - Multirepo：在Python社区中，Multirepo似乎更受欢迎，主要原因可能是Python的包管理工具（如pip）在多仓库环境中工作得更好。 

- Node.js的npm

  - Multirepo：由于npm的设计方式，Node.js社区倾向于选择Multirepo。每个npm包都有其自己独立的版本号和依赖关系，这可以在Multirepo中很好地管理。 

  - Monorepo：但是最近在一些大型项目中（包括一些使用JavaScript和Node.js的项目），Monorepo正在变得更加流行，工具像Lerna就是为此而设计的。

总的来说，对于大部分语言和框架来说，两者都是可行的，并且都有成功的实践案例。所以选择哪种方式更多地取决于项目的特性和团队的喜好。

## 【转】该用 Monorepo 吗？比较 Monolith vs Multi-Repo vs Monorepo

转自：[该用 Monorepo 吗？比较 Monolith vs Multi-Repo vs Monorepo](https://www.cythilya.tw/2023/01/28/monolith-vs-multi-repo-vs-mono-repo/)，并进行了繁体转简体

专案随著开发时间愈长，伴随而来的除了体积和复杂度增加之外，也产生难以扩充、缺乏弹性以及打包和部署时间长、效率差等问题。这时候就会开始考虑切分专案。

在这里来聊聊三种管理专案的架构

- [Monolith](https://www.cythilya.tw/2023/01/28/monolith-vs-multi-repo-vs-mono-repo/#Monolith)
- [Multi-Repo](https://www.cythilya.tw/2023/01/28/monolith-vs-multi-repo-vs-mono-repo/#Multi-Repo)
- [Monorepo](https://www.cythilya.tw/2023/01/28/monolith-vs-multi-repo-vs-mono-repo/#Monorepo)

这篇文章会谈到过去在建置专案时遇到的问题，以及根据不同情境而选用的解法，并在最后推荐工具与提供利用 Module Federation 达成 Micro Frontends 的范例来[快速上手](https://www.cythilya.tw/2023/01/28/monolith-vs-multi-repo-vs-mono-repo/#快速上手)和[总结比较](https://www.cythilya.tw/2023/01/28/monolith-vs-multi-repo-vs-mono-repo/#總結)。

![Monolith vs Multi-Repo vs Monorepo 示意圖](Monorepo VS Multirepo.assets/monolith-vs-multi-repo-vs-mono-repo.png)

![image-20231022152926033](Monorepo VS Multirepo.assets/image-20231022152926033.png)

### Monolith (单架构)

![Monolith](Monorepo VS Multirepo.assets/monolith.png)

```js
├── assets
├── components
│   ├── Button.js
│   ├── Modal.js
│   └── ...
├── node_modules
├── pages
│   ├── Chat			// Chat 聊天模块
│   │   ├── Contact.js
│   │   ├── Message.js
│   │   └── ...
│   ├── Mall			// Mall 购物模块
│   │   ├── Cart.js
│   │   ├── Product.js
│   │   └── ...
│   ├── News			// News 新闻/推荐模块
│   │   ├── Article.js
│   │   ├── Topic.js
│   │   └── ...
├── utils
├── package.json
├── jest.config.js
├── webpack.config.js
├── yarn.lock
└── README.md
```

模式

> 过去在建置专案时，大多选用 `Single-Repo Monolith` 的架构，意即将所有的功能都统一放在同一个  repository (简称 repo) 底下。
>
> 如上图所示，在 WebGether 这个产品的 repo 底下，包含 News、Mall 和  Chat 功能。

优点

> 这在产品开发初期或非大型规模专案，的确是个简单方便的好方法。

缺点

> - 在团队与产品不断扩张的状况下，这个 repo  变得超级**大**，导致打包和部署**时间长**、**效率差**
>
> - 不同团队可能会用到**不同的环境建置与技术栈** (tech stack) 而造成 **相依管理困难**  (dependency management) 、**难以扩充**、**缺乏弹性**。
>
>   - 场景举例：
>
>     WebGether 原本统一使用 React v15 作为前端开发框架，并且用 Redux 作为状态管理工具、
>
>     但某天 News  团队希望改用潮到出水的 Vue，Mall 团队希望能用 useReducer + useContext 取代 Redux，Chat 团队无法接受 React 升版 v16.8 导致某最爱的 package 失效。
>
>     这时候就要考虑分家了，将不同功能切分为不同专案，切分方式可分为两种：Multi-Repo、Monorepo

### MultiRepo (多仓库)

![Multi-Repo](Monorepo VS Multirepo.assets/multi-repo.png)

```js
// Chat 聊天模块
├── assets
├── components
│   ├── Button.js
│   ├── Modal.js
│   └── ...
├── node_modules
├── pages
│   ├── Contact.js
│   ├── Message.js
│   └── ...
├── utils
├── package.json
├── jest.config.js
├── webpack.config.js
├── yarn.lock
└── README.md

// Mall 购物模块
├── assets
├── components
│   ├── Button.js
│   ├── Modal.js
│   └── ...
├── node_modules
├── pages
│   ├── Cart.js
│   ├── Product.js
│   └── ...
├── utils
├── package.json
├── jest.config.js
├── webpack.config.js
├── yarn.lock
└── README.md

// News 新闻/推荐模块
├── assets
├── components
│   ├── Button.js
│   ├── Modal.js
│   └── ...
├── node_modules
├── pages
│   ├── Article.js
│   ├── Topic.js
│   └── ...
├── utils
├── package.json
├── jest.config.js
├── webpack.config.js
├── yarn.lock
└── README.md
```

模式

> Multi-Repo (或称 Polyrepo、Many-repo) 是指将个别功能放在不同 repo 底下，如前面的例子，在拆分 News、Mall 和 Chat 后，这三个功能便拥有各自独立的 repo，同时也能拥有各自的环境和工具的设定档与技术线。

优点

> - 专案体积小、高效率开发、技术栈独立
>
> - 相依管理简单、高弹性，因此权责切分干净、不同框架时更显优点
>
>   - 场景举例：
>
>     这里解决就前面说到的问题。News 果真改用 Vue 来做前端开发的框架，Mall 不再需要迁就 Chat 的守旧而能快乐使用 React Hooks 以及 Chat 可以继续使用他们最爱的恐龙级 package，皆大欢喜 ヽ(●´∀`●)ﾉ

缺点（缺点就是优点的反面）

> - 不易共享，像是环境与设定档重复配置 (CI/CD、webpack、test suite 等)、资源难以共用。
>
>   - 场景举例：
>
>     某天 News 团队开发了一个很棒的 sticker footer 元件，过去在 Monolith 时各团队只要引入这个元件即可共用，但现在可能要请 News 团队将这个元件打包成 NPM package 或抽到共用的元件的 repo 再用 Git Submodule  再引用的方式才能共用，共用的困难度增加。关于选 NPM package 还是 Git  Submodule，个人经验来说差异为打包、发布和更新上的不同，端看团队用起来谁比较顺手就好，这个[讨论](https://stackoverflow.com/questions/62598858/git-submodule-vs-npm-package/62605719)也许能提供一些参考
>
> - 当资源更新时，个别 repo 难以被通知而及时更新
>
> - 修 bug 或是 i18n 字串更新时若涉及多个 repo，处理与测试的困难度也会变高。
>
> - 建构、测试与发布流程上甚至是 rollback 都较困难。

其他补充

> 与 Multi-Repo 这个概念的相似解法，可参考 [Git Submodule](http://shachiku.life/posts/difference-between-subtree-and-submodule/) 或 [Git Subtree](https://blog.darkthread.net/blog/git-subtree-notes/https://blog.puckwang.com/posts/2020/git-submodule-vs-subtree/)
>
> - Git Submodule 是指建立 main repo 与 sub repo  的 HEAD commit 连结
> - Git Subtree 是指将 main repo 包含 commit log 全部 copy 到新的 repo 中
>
> 看完 Multi-Repo，有没有什么能同时 **兼顾弹性与共用** 的解法呢？接下来看 Monorepo

### MonoRepo (单仓库)

![Monorepo](Monorepo VS Multirepo.assets/mono-repo.png)

档案配置示意如下

```js
├── shared					// 共享部分
│   ├── assets
│   ├── components
│   │   ├── Button.js
│   │   ├── Modal.js
│   │   └── ...
│   ├── utils
│   └── ...
├── apps
│   ├── chat				// Chat 聊天模块
│   │   ├── components
│   │   ├── pages
│   │   │   ├── Contact.js
│   │   │   ├── Message.js
│   │   ├── utils
│   │   └── ...
│   ├── chat-e2e
│   ├── mall				// Mall 购物模块
│   │   ├── components
│   │   ├── pages
│   │   │   ├── Cart.js
│   │   │   ├── Product.js
│   │   ├── utils
│   │   └── ...
│   ├── mall-e2e
│   ├── news				// News 新闻/推荐模块
│   │   ├── components
│   │   ├── pages
│   │   │  ├── Article.js
│   │   │  ├── Topic.js
│   │   ├── utils
│   │   └── ...
│   └── news-e2e
├── node_modules
├── package.json
├── jest.config.js
├── webpack.config.js
├── yarn.lock
└── README.md
```

模式

> Monorepo 将个别功能放在同一 repo 的不同 package 底下，如前面的例子，在拆分 News、Mall 和 Chat 后，这三个功能虽然仍在同一个 repo 底下，但放置于不同的 pacakge 资料夹
>
> 个人知识盲区，补充一下：
>
> >  `e2e` 是一个用于进行端到端测试（End-to-End  Testing）的文件或文件夹。在软件开发中，端到端测试用于确保整个应用程序流程（从开始到结束）都可以正常工作。这种测试覆盖了所有的交互路径，包括外部系统和接口。这有助于验证系统和其组件是否能在实际环境中——从开始到结束——正常工作。
> >
> > e2e测试的定义并不是最初的字符"E"和最后的字符“E”代表一个客户端和服务端，而是指的是对整个应用程序，从开始到结束（end-to-end）的一个完整流程，将所有相关组件串联在一起进行的测试。
> >
> > "端对端"这个词是从"end to end"直接翻译过来的，原意是“从一端到另一端”，在这里是指整个软件系统从起始到结束，涵盖所有的交互过程和组件。所以，即使只有一个客户端或服务端，但只要测试覆盖了所有的用户场景和交互流程，仍然可以被称之为e2e测试。
> >
> > 翻译为"端对端测试"是为了准确表达其测试整个流程的含义，不能理解为只测试两个"端"（如客户端和服务端）之间的通信。在e2e测试中，"端（end）"应理解为流程的起始点和结束点，而不仅仅是物理设备或者是一个客户端/服务端。

优点

> - 能**共享资源**，在**同框架**时更显优势
> - 能**共享配置**，像是共享环境设定和 config 档，不需每个 app 再自建一套。这在建构、测试与发布流程上甚至是 rollback 是很方便的。
> - 当资源更新时，个别 app 能够**及时被通知而更新**
>

缺点

> - **体积大**，跟 Monolith 同样有 repo 庞大的问题，这在 codebase 很大的状况下很可能造成 Git 效能差 (细节和解法参考[这里](https://github.blog/2022-06-29-improve-git-monorepo-performance-with-a-file-system-monitor/))、SourceTree 当掉；
>
>   虽然说开发人员可自行设定 filter 来侦测 repo 更新和决定部署哪个 package，但开发平台像是 [Netlify](https://www.netlify.com/) 不会判断是哪个 app 有更新，只要 repo 有 change 就会 trigger deploy，repo 愈大开发与部署成本愈高，对这个议题和解法有兴趣的可参考[那里](https://www.netlify.com/blog/2020/04/21/deploying-nx-monorepos-to-netlify/)。
>
> - 是否共用要切分清楚，由于太容易共用了，在开发上需要制定明确规范。
>
>   例如：利用 linter or dependency graph  限制共用元件或工具必须放在 shared package，不属于自身 package 的 app 不能共用。这在开发和 PR review  时需要多多留心 codebase 的更新状况和是否修改在适当的范围之内。同样的，对于专属自身 app 想要安装使用的东西就放在自家  package.json 里面，记得注意 [package version hoist](https://www.jonathancreamer.com/inside-the-pain-of-monorepos-and-hoisting/) 的状况。
>
> - 在**开发人员众多**时**紊乱**、**难以控管**档案**权限**
>
>   - 无法针对 package 来限制谁能浏览或编辑
>   - 同时也会反应到开 **issue**、**回复 PR** 和**通知**过于紊乱的问题上。

其他 - 前后端问题

> 顺道一提，有些专案是将前后端一同整合至 Monorepo 上，这样的考量点可能是前后端的开发成员是同一批人、使用同一种语言或便于 Ops 统一管理与版控
>
> - 优点：能做到有效的资源共享、前后端整合是很便利的
> - 缺点：复杂度变高，一旦 repo 出现问题前后端都会受影响等
>
> 关于这个议题[这篇文章](https://blog.errorbaker.tw/posts/cwc329/monorepo/)提到不错的观点与说明。个人经验来说，由于大多待在前后端分离的团队，开发人员、语言和环境差异甚大 (React vs Go)，并且专案规模庞大，因此都是在这样的配置下选择此架构来达成 Micro Frontends。

### 快速上手

最后，在管理 Monorepo 的工具方面，推荐可用 PNPM、Lerna、Bit、[NX](https://www.youtube.com/watch?v=VUyBY72mwrQ) 等，有选择困难症的这里有[重点整理和比较](https://levelup.gitconnected.com/different-monorepo-solutions-in-2021-1d6f5e5fb95b#1de3)；而 NX 提供了很棒的 [Webpack Module Federation 范例](https://github.com/nrwl/react-module-federation)，加上 Vercel 对 NX 支援也很友善 ([还提供样板](https://vercel.com/templates/next.js/monorepo-nx)) ([注 1](https://www.cythilya.tw/2023/01/28/monolith-vs-multi-repo-vs-mono-repo/#備註))，可以参考看看。

### 总结

选用

> 就个人开发经验来说，会依据专案的团队成员组成、实作细节与维运的复杂度来决定要选用 Multirepo 还是 Monorepo  的架构。简单来说：
>
> - 需要**高度共用**、**紧密合作**的状况下会选用 Monorep
> - 若功能**差异大**、彼此没什么交集、不想被彼此影响，就会选用  Multirepo
>
> 其中 Monorepo 在易于分享配置与资源的同时，也能拥有各自想要的弹性，可说是共享与独立兼顾。

比较 Monolith、Multi-Repo 与 Monorepo 如下表。

| ＃       | Monolith                                                     | Multi-Repo                                                   | Monorepo                                                |
| -------- | ------------------------------------------------------------ | ------------------------------------------------------------ | ------------------------------------------------------- |
| 特色     | 将所有的功能放在单一 repo                                    | 将个别功能放在不同 repo                                      | 将个别功能放在同一 repo 的不同 package                  |
| 优点     | 简单方便                                                     | 1. 专案体积小、高效开发；2. 技术线独立、相依管理简单、高弹性 | 共享与独立兼顾                                          |
| 缺点     | 1. 专案过于庞大，开发低效；2. 相依管理困难、难以扩充、缺乏弹性 | 共享不易                                                     | repo 庞大、开发需明确规范、档案权限难以控管、Git 效能差 |
| 工具     | -                                                            | -                                                            | PNPM Lerna Bit NX 等                                    |
| 适用情境 | 产品开发初期或非大型规模专案                                 | 切分大型专案、相依和共享状况少                               | 切分大型专案、相依和共享状况多                          |
| 相似解法 | -                                                            | Git Submodules 或 Git Subtree                                | -                                                       |

这些架构都有各自适用的状况，评估后选用适合的解法即可 `(๑•̀ㅂ•́)و✧`

### 备注

- 注 1：部署 Monorepo 到 Netlify (同理 Vercel) 的设定可参考[这篇文章](https://www.netlify.com/blog/2020/04/21/deploying-nx-monorepos-to-netlify/)。

## 深入选型

参考：

- [【稀土掘金】"分"与"合"的哲学碰撞，Monorepo vs Multirepo](https://juejin.cn/post/6949882490324516894)
- [Monorepo与multirepo区别何在？为什么大公司像谷歌.微软.优步.Neflix.Nike都在Monorepo?](https://medium.com/@neatcoding/monorepo%E4%B8%8Emultirepo%E5%8C%BA%E5%88%AB%E4%BD%95%E5%9C%A8-%E4%B8%BA%E4%BB%80%E4%B9%88%E5%A4%A7%E5%85%AC%E5%8F%B8%E5%83%8F%E8%B0%B7%E6%AD%8C-%E5%BE%AE%E8%BD%AF-%E4%BC%98%E6%AD%A5-neflix-nike%E9%83%BD%E5%9C%A8monorepo-416a04d8b03b)
- [【知乎】REPO 风格之争：MONO VS MULTI](https://zhuanlan.zhihu.com/p/31289463)
- [【51CTO】2022 了，你还不知道 Multi-repo 和 Mono-repo 的区别么？](https://www.51cto.com/article/709468.html)























