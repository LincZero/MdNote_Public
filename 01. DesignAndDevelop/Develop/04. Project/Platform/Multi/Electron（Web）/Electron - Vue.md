# Electron-Vue

## 项目创建

中文文档：https://simulatedgreg.gitbooks.io/electron-vue/content/cn/

本项目需要使用 `node@^7` 或更高版本

electron-vue 官方推荐 [`yarn`](https://yarnpkg.org) 作为软件包管理器，因为它可以更好地处理依赖关系，并可以使用 `yarn clean` 帮助减少最后构建文件的大小。

```shell
# 安装 vue-cli 和 脚手架样板代码
npm install -g vue-cli
vue init simulatedgreg/electron-vue my-project

# 安装依赖并运行你的程序
cd my-project
yarn # 或者 npm install，这步时间非常久
yarn run dev # 或者 npm
```

报错

```shell
ERROR in Template execution failed: ReferenceError: process is not defined
```

解决：

Solved by removing:（index.ejs）(移除可以，注释不行......很神奇)

```ejs
<!-- <% if (!process.browser) { %>
	<script>
		if (process.env.NODE_ENV !== 'development') window.__static = require('path').join(__dirname, '/static').replace(/\\/g, '\\\\')
	</script>
<% } %> -->
```

## electron-builder打包错误

错误信息：`cannot move downloaded into final location (another process downloaded faster?)`

解决：直接退出【火绒安全软件】

原理：

1. nodejs打包时，会创建 \cakeGUI\build\win-unpacked\electron.exe
2. 火绒实时监控在检测到文件生成后，会对改文件做扫描
3. 火绒实时监控的逻辑会保证在火绒扫描时，后续进程对该文件的同步操作被阻塞，以保证文件操作的原子性和完整性
4. 火绒查毒结束后，AlibabaProtect进程也会对该文件做内容分析（可能是病毒扫描，具体不清楚）
5. AlibabaProtect没有同步后续的文件操作，导致nodejs后续对\cakeGUI\build\win-unpacked\electron.exe尝试做删除操作时，由于AlibabaProtect正占用该文件而失败。