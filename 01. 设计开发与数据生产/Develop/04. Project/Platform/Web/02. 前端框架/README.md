# 多个前端框架

## 9大前端框架

| 内容       | Repo                               | Intro | Total Stars (221118) |      | 官网                                                         |
| ---------- | ---------------------------------- | ----- | -------------------- | ---- | ------------------------------------------------------------ |
| Vue.js     | https://github.com/vuejs/vue       |       | 201k                 | 206  | https://reactjs.org/<br />简中：https://zh-hans.reactjs.org/ |
| React      | https://github.com/facebook/react  |       | 198k                 | 215  | https://vuejs.org/<br />简中：https://cn.vuejs.org/          |
| Svelte     | https://github.com/sveltejs/svelte |       | 63.2k                |      | https://svelte.dev/<br />中文官网：https://www.sveltejs.cn/  |
| Angular    | https://github.com/angular/angular |       | 84.9k                |      | https://angular.io/                                          |
| Alpine     |                                    |       |                      |      | https://alpinejs.dev<br />中文官网：https://www.alpinejs.cn  |
| Preact     |                                    |       |                      |      | https://preactjs.com                                         |
| LitElement |                                    |       |                      |      | https://lit.dev                                              |
| Stimulus   |                                    |       |                      |      | https://stimulus.hotwired.dev                                |
| Ember      |                                    |       |                      |      | https://emberjs.com                                          |

Svelte比较新。
Svelte 是一种全新的构建用户界面的方法。传统框架如 React 和 Vue 在浏览器中需要做大量的工作，而 Svelte 将这些工作放到构建应用程序的**编译阶段来处理**

![image-20221118001657520](README.assets/image-20221118001657520.png)

## Svelte vs Vue：比较框架的内部结构

参考：https://juejin.cn/post/7067855816283389965

### 目录

- [Vue的基本原理](#fundamentals-vue)
- [Svelte的基本原理](#fundamentals-svelte)
- [开始学习](#getting-started)
- 组件结构和语法比较
  - [声明式渲染](#declarative-rendering)
  - [数据绑定](#data-binding)
  - [计算属性](#computed-property)
- [事件](#events)
- 反应性
  - [构建时间反应性](#build-time-reactivity)
- [完善的静态分析阶段](#svelte-static-analysis-phase)
- [Svelte 渲染阶段](#svelte-rendering-phase)
- Vue运行时活动
  - [反应性模块](#reactivity-module)
  - [安装模块](#mount-module)
  - [渲染器模块](#render-module)
- [总结](#conclusion)



### 先引

曾几何时，React、Angular和Ember站在网络开发的最前沿，争相成为最好的JavaScript框架，后来Vue大行其道，将[Ember踢到了一边，取而代之。](https://link.juejin.cn?target=https%3A%2F%2Fblog.logrocket.com%2Fgetting-started-with-ember-js-in-2020%2F)

快进到2022年，历史似乎正在重演，因为[Svelte，一个相对较新的框架](https://link.juejin.cn?target=https%3A%2F%2Fblog.logrocket.com%2Fbuilding-a-pwa-with-svelte%2F)[，](https://link.juejin.cn?target=https%3A%2F%2Fblog.logrocket.com%2Fbuilding-a-pwa-with-svelte%2F)正在以指数级的速度流行起来。我们不禁要问自己，Svelte是否具备成为顶级竞争者的条件。

Svelte似乎借鉴了Vue的玩法，实现并改进了让我们一开始就喜欢Vue的东西，比如高性能、轻量级和熟悉的模板语法，以及简单的学习曲线。

在这篇文章中，我们将研究Svelte和Vue在语法上的差异，比较它们在引擎盖下的工作方式。



### Vue的基本原理

Vue是一个渐进的、开源的JavaScript框架，用于构建用户界面和单页应用程序。

Vue被设计成**渐进式集成**，这意味着你可以将Vue添加到现有前端项目的任何部分，而不需要重新构建整个项目。
**Vue只依赖于JavaScript，不像Svelte这样的框架，它使用了编译器**。

要用Vue构建一个单页应用程序，你必须使用它的CLI，这是一个命令行实用工具，可以用不同的构建系统快速搭建Vue模板项目的支架。

Vue的**核心**是一些从其竞争对手Angular和React那里继承的概念。

- 首先，Vue利用了Angular的反应式[**双向数据绑定**](https://link.juejin.cn?target=https%3A%2F%2Fangular.io%2Fguide%2Ftwo-way-binding)，在模型和视图之间建立了反应式连接。
- 另一个是React的Virtual DOM diffing，它可以防止Vue在每次有变化时都要动手术更新DOM。
- 部分受到MVVM设计模式的启发，Vue的重点在于视图层，或模板。
  然而，Vue应用程序中的每个组件实例都被称为[ViewModel](https://link.juejin.cn?target=https%3A%2F%2F012.vuejs.org%2Fguide%2F%23ViewModel)，或`vm` 变量。`vm` 是连接视图和模型-视图层的数据绑定系统。



### Svelte的基本原理

Svelte是一个开源的、用于创建交互式UI的前端框架。

与Vue不同，Svelte是一个**编译器**，可以将声明性的状态驱动组件转换为直接更新DOM的命令式JavaScript代码。

通过虚拟DOM差异化技术，单体框架在运行时编译声明性代码。虽然这种方法高效快速，但它要求浏览器在渲染网页之前执行额外的任务，产生影响应用程序性能的开销。

通过解析并将其声明性代码编译成浏览器可以在构建时使用的JavaScript代码，Svelte避免了这种性能开销，[使其比](https://link.juejin.cn?target=https%3A%2F%2Fkrausest.github.io%2Fjs-framework-benchmark%2F2022%2Ftable_chrome_97.0.4692.71.html)使用虚拟DOM并在运行时编译的[框架快2倍](https://link.juejin.cn?target=https%3A%2F%2Fkrausest.github.io%2Fjs-framework-benchmark%2F2022%2Ftable_chrome_97.0.4692.71.html)。



### ……



### 总结

尽管Svelte带来了很多好处，但很多开发者还没有准备好迁移到它，主要是因为它缺乏灵活性和小的社区支持。

毫无疑问，Svelte是一个高性能的框架，但Vue已经有多年的时间和大量的支持来实现和改进这些方面。Svelte是一个相对较新的框架，仍在努力寻找其在生态系统中的立足点。

希望Svelte的创造者Rich Harris和Vercel之间的合作能将Svelte推向它应有的高度。我希望你喜欢这篇文章!

The post[Svelte vs Vue:框架内部](https://link.juejin.cn?target=https%3A%2F%2Fblog.logrocket.com%2Fsvelte-vs-vue-comparing-framework-internals%2F)的比较首次出现在[LogRocket博客](https://link.juejin.cn?target=https%3A%2F%2Fblog.logrocket.com)上。



# Web组件

还有一个叫 Web原生组件 的东西

一些比较知名的Web组件库/框架有：

1. Polymer：Google推出的一个轻量级Web组件库，允许开发者创建自定义的可重用组件。 
2. LitElement：也是由Polymer团队开发的，用于创建轻量级Web组件的JavaScript库。 
3. Stencil：由Ionic团队开发，它是一个Web组件编译器，旨在创建可跨框架使用的组件。 
4. Slim.js：一个快速、强大、自我包容的Web组件库。 

其实更多的时候，Web组件常常作为一个底层的标准被用于构建更高级的、丰富的框架或者库（比如Angular，React，Vue等）。另外，还有一些开源的组件库由Web组件构成，例如Vaadin和Ionicons等。

虽然已经有一些成熟的Web组件库，但是与Vue, React或Angular等框架的生态系统比起来，Web组件的生态系统还是相对较小。





















