# Mdit-Plugins项目

参考：

- Mdit-Plugins
  - 网页：https://mdit-plugins.github.io/zh/
  - Github：https://github.com/mdit-plugins/mdit-plugins
- VuePress-Hope-Theme MdEnhance
  - 简易文档：https://theme-hope.vuejs.press/zh/config/plugins/md-enhance.html#%E4%BB%8B%E7%BB%8D
  - 专题文档：https://plugin-md-enhance.vuejs.press/zh/config.html
  - 对应Github：https://github.com/vuepress-theme-hope/vuepress-theme-hope/tree/main/packages/md-enhance/
- 上面两者的关系
  - VuePress-Hope-Theme MdEnhance 依赖 Mdit-Plugins 对应的一些模块子包

我主要学习下 MdEnhance 选项如何减少体积，按需使用

## 依赖

从 https://github.com/vuepress-theme-hope/vuepress-theme-hope/tree/main/packages/md-enhance/package.json 来看，不直接依赖于对应的第三方插件，而是先由 `@mdit` 包装一层然后去依赖 `@mdit/...`





 
