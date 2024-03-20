



## [Element, HTMLElement, HTMLHtmlElement有什么区别](https://segmentfault.com/q/1010000014625383)

Q：在[MDN的API参考](https://link.segmentfault.com/?enc=0FaBigFMhBnYfjUNDGyT4g%3D%3D.6YWl9dboNmMqGMFNh%2BGBrm%2BqFePNIriN0dohFhxvqWZyKIRdRRpJr2uOqXjFSKJ3GuOqTohh7riOnlq15eLCPA%3D%3D)中，有这三个API，它们有什么区别，体现在网页上有什么不一样。

A：element是一个html元素，或者标签，每一个标签在dom中就是一个节点node，节点下面有element，document，characterData,attr.document代表一个html或xml文档，element类型代表该文档中的一个元素。HTMLElement和HTMLDocument只针对HTML文档和元素
画了一幅图：

![preview](DOM.assets/view.png)

继承自Element的不止有HTMLElement