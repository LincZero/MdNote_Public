# VuePress

# 目录

# VuePress

## VuePress2 + Typescript版本

详见VuePress的笔记

略，这里使用不算稳定的VuePress2，是因为我并不是在上面部署稳定服务。开发插件内容主要依赖Md-it而非VuePress专属插件，VuePress接口更替对我来说应该影响不大。

环境准备：

```bash
# init
git init
pnpm init

# vuepress和vue相关包
pnpm add -D vuepress@next @vuepress/client@next vue

# 不需要md-it相关包 (VuePress已经自带了)
# pnpm install --save markdown-it
# pnpm install --save-dev @types/markdown-it
```

准备package.json，往里面添加一些script：

```json
{
  "scripts": {
    "docs:dev": "vuepress dev docs",
    "docs:build": "vuepress build docs"
  }
}
```

准备其他文件，包括.gitignore和README.md

```bash
echo 'node_modules' >> .gitignore
echo '.temp' >> .gitignore
echo '.cache' >> .gitignore
mkdir docs
echo '# Hello VuePress' > docs/README.md
```

启动服务

```bash
pnpm docs:dev
```

插件的基本使用：在你的 `.vuepress/config.js` 文件中增加一个"markdown"字段，并使用插件：

```js
module.exports = {
  markdown: {
    extendMarkdown: md => {
      md.use(require('markdown-it-checkbox'))
    },
  },
};
```











































