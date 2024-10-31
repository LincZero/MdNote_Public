# README.202309调研

## GPT简单调研

评价 Vitest、Svelte、Solid.js、lit 等新的前端框架，可以与旧的三大框架Vue React Angular比较

---

在评价新的前端框架Vitest、Svelte、Solid.js、lit时，有几个重要参数值得参考，包括性能、大小、生态系统、API设计、易用性和灵活性。

1. Vitest: Vitest是一个为Vite生态系统打造的全新测试工具。与Vue, React, Angular等框架比起来，它专注于测试，相对较新，其生态系统可能不如三大框架丰富。 
2. Svelte: Svelte是一种新的方式来构建web应用。它在构建阶段进行编译，而不是在运行时解释，这意味着你将能够编写更高效的代码。相比于Vue,  React和Angular，Svelte通常可以产生更小的bundle和更快的加载时间。然而，由于它相对较新，其生态系统和可用资源可能不如三大框架丰富。 
3. Solid.js: Solid.js是高性能的反应性UI库，特点是微小的大小和高性能。它与React的主要区别在于，Solid.js是编译时框架，而React是运行时框架。相比之下，Solid.js可以提供更高的性能和速度，但React由于其更成熟的社区，可能提供更丰富的插件和工具。 
4. lit (LitElement): lit是一款使用简单，轻量级的构建Web组件的库。与 Vue，React和Angular等更复杂的库相比，lit更加轻巧，更加注重基于Web组件的开发。而且，由于lit使用原生Web组件，所以兼容性更好。 

对比来说，这些新框架每个都有自己的优势，例如更小的bundle大小，更快的速度，或更好的模块化，但通常情况下他们的生态系统不如Vue，React，Angular丰富。选择哪个框架取决于具体的项目需求和使用场景。

---

Svelte的提前编译，和使用底层语言进行的wasm还是有区别的吧

---

是的，Svelte 的提前编译（Ahead-of-Time Compilation，也被称为 AOT）和使用 WebAssembly (WASM) 的底层语言编译确实是两个不同的概念。它们的目标都是提高应用程序的性能，但它们的实现方式和具体效果存在差异。

Svelte 的提前编译主要是将组件在构建阶段就编译成高效的 JavaScript，而不是等到运行时。这种方式可以减少运行时的计算，使应用程序能以更快的速度运行。而且，由于生成的 JavaScript 代码更少，因此可以产生更小的应用程序包，节省网络带宽。

而 WASM 是一种可以在现代浏览器中运行的二进制代码格式。与 JavaScript 相比，WASM 可以提供更靠近原生的性能。你可以将 C/C++、Rust 等低级别的语言编译成 WASM，然后在浏览器中执行。

这两种技术都可以提高web应用的性能，但它们的适用场景不同。Svelte 的 AOT 编译更适合于构建用户界面，而 WASM 则更适用于需要高性能计算或者运行现有的底层语言代码库的场景。

## 0

排行：https://pgmr.cloud/most-popular-front-end-frameworks-2023























