# Typora

## Typora语法高亮原理

Typora的代码块语法高亮使用的是[CodeMirror](https://codemirror.net/)实现的

参考：

- 版本6流程：[CodeMirror主页](https://codemirror.net/) > [ 社区维护    语言包](https://codemirror.net/docs/community#language) > 主题 > [主题镜](https://thememirror.net/)，但怎么感觉没有旧版的多主题
- 版本5流程：[CodeMirror主页](https://codemirror.net/5/) > 特征 > [各种主题](https://codemirror.net/5/demo/theme.html)，



```css
/* https://www.cnblogs.com/Anber82/p/14120414.html */
/* 点击主题化：https://codemirror.net/ */
/* https://codemirror.net/theme/ */
/* 将其代码中所有的.cm-s-dracula改为.cm-s-inner */
/* Based on Sublime Text's Monokai theme */
```



```python
import React


```



我选的主题应该是：material-darker

```js
function findSequence(goal) {
  function find(start, history) {
    if (start == goal)
      return history;
    else if (start > goal)
      return null;
    else
      return find(start + 5, "(" + history + " + 5)") ||
             find(start * 3, "(" + history + " * 3)");
  }
  return find(1, "1");
}
```

