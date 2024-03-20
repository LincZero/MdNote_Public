# SCSS入门

# 目录

## CSS、SASS、SCSS

SASS与SCSS

> SCSS 是 Sass 3 引入新的语法，其语法完全兼容 CSS3，并且继承了 Sass 的强大功能。 大部分扩展，例如变量、parent references 和 指令都是一致的 唯一不同的是，SCSS 需要使用分号和花括号而不是换行和缩进

## 使用变量

变量定义与引用

变量作用域

```scss
$nav-color: #F90;
$highlight-border: 1px solid $highlight-color;
nav {
  $width: 100px;
  width: $width;
  color: $nav-color;
}

//编译后

nav {
  width: 100px;
  color: #F90;
}
```

变量命名

## 嵌套CSS 规则

嵌套规则

普通连接与&连接

```scss
#content {
  article {
    h1 { color: #333 }
    p { margin-bottom: 1.4em }
  }
  aside { background-color: #EEE }
  &:hover { color: red } // 注意这里伪类的&&&&&&&&，不会通过一个空格连接
}
```

群组选择器的嵌套

```scss
.container {
  h1, h2, h3 {margin-bottom: .8em}
}
nav, aside {
  a {color: blue}
}
```

子组合选择器和同层组合选择器：>、+和~

```scss
article {
  ~ article { border-top: 1px dashed #ccc }
  > section { background: #eee }
  dl > {
    dt { color: #333 }
    dd { color: #555 }
  }
  nav + & { margin-top: 0 }
}
```

属性嵌套，规则是 ': {}' 会用 '-' 连接

```scss
nav {
  border: {
  style: solid;
  width: 1px;
  color: #ccc;
  }
}
nav {
  border: 1px solid #ccc {
  left: 0px;
  right: 0px;
  }
}
```

## 导入SASS文件

css有一个特别不常用的特性，即@import规则，它允许在一个css文件中导入其他css文件。然而，后果是只有执行到@import时，浏览器才会去下载其他css文件，这导致页面加载起来特别慢。

