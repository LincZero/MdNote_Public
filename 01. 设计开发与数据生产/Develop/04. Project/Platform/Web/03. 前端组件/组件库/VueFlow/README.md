---
create_time: 2024-10-17
author: LincZero翻译的VueFlow官方文档
---

# README

## 资料

- Github: https://github.com/bcakmakoglu/vue-flow
- 官网: https://vueflow.dev/
- 文档
  - Guide https://vueflow.dev/guide/
  - Examples https://vueflow.dev/examples/
  - Typedocs https://vueflow.dev/typedocs/ (API接口文档)

## 翻译问题

这里的翻译基于 V1.41.2 版本的官方文档，基本上是翻译的，如果有译者补充的内容，会额外进行标注

## 文档显示节点画布的补充

我们看到vueflow的官网文档是有节点的显示的，并且是vitepress部署的文档

### 网站相关

首先看一下他的md源码表示，参考：

https://github.com/bcakmakoglu/vue-flow/blob/master/docs/src/guide/theming.md

```html
<div class="mt-4 bg-[var(--vp-code-block-bg)] rounded-lg h-50">
  <VueFlow v-model="elements" fit-view-on-init>
    <template #node-custom="props">
      <CustomNode v-bind="props" />
    </template>
    <Background />
  </VueFlow>
</div>

<style>
.vue-flow__node-custom {
  background: purple;
  color: white;
  border: 1px solid purple;
  border-radius: 4px;
  box-shadow: 0 0 0 1px purple;
  padding: 8px;
}
</style>
```

他是在md片段里写了这么一段html片段

我们再来看他的vitepress配置：

package.json (这里简化了与节点显示无关的东西)

```json
{
  "name": "@vue-flow/docs",
  "dependencies": {
    "@algolia/client-search": "^5.1.1",
    "@stackblitz/sdk": "^1.11.0",
    "@vercel/analytics": "^1.3.1",
    "@vercel/speed-insights": "^1.0.12",
    "@vue-flow/background": "workspace:*", // vue-flow这一堆应该都是，还是个monorepo
    "@vue-flow/controls": "workspace:*",
    "@vue-flow/core": "workspace:*",
    "@vue-flow/minimap": "workspace:*",    // `minimap` 感觉是我想要的
    "@vue-flow/node-resizer": "workspace:*",
    "@vue-flow/node-toolbar": "workspace:*",
    "@vue/repl": "3.4.0",
    "blobity": "^0.2.3",
    "vue": "^3.4.38",
    "web-vitals": "^4.2.3"
  },
  "devDependencies": {
    "@iconify/json": "^2.2.241",
    "@tooling/eslint-config": "workspace:*",
    "@tooling/tsconfig": "workspace:*",
    "@windicss/plugin-scrollbar": "^1.2.3",
    "dotenv": "^16.4.5",
    "ohmyfetch": "^0.4.21",
    "typedoc": "^0.26.6",
    "typedoc-plugin-markdown": "^4.2.6",
    "typedoc-plugin-merge-modules": "^6.0.0",
    "unplugin-auto-import": "^0.18.2",
    "unplugin-icons": "^0.19.2",
    "unplugin-vue-components": "^0.27.4",
    "vite-plugin-windicss": "^1.9.3",
    "vitepress": "^1.3.4",
    "windicss": "^3.5.6"
  }
}
```

config.mts

这个文件好像没有做什么相关的操作

```ts
import { useVueFlow } from '@vue-flow/core'

const { vueFlowVersion } = useVueFlow() // 仅用于展示版本
```

### 个人实战 - 构建package与文档 (失败)

然后我尝试去构建一下他的文档

Windows

```bash
PS H:\Git\Public\Group_FrontEnd> node -v
v20.10.0
PS H:\Git\Public\Group_FrontEnd> pnpm -v
9.12.2
PS H:\Git\Public\Group_FrontEnd> npm -v
10.2.3
PS H:\Git\Public\Group_FrontEnd> git clone https://github.com/bcakmakoglu/vue-flow.git
Cloning into 'vue-flow'...
remote: Enumerating objects: 34810, done.
remote: Counting objects: 100% (2550/2550), done.
remote: Compressing objects: 100% (1162/1162), done.
remote: Total 34810 (delta 1683), reused 1905 (delta 1339), pack-reused 32260 (from 1)
Receiving objects: 100% (34810/34810), 15.90 MiB | 12.82 MiB/s, done.
Resolving deltas: 100% (24538/24538), done.
PS H:\Git\Public\Group_FrontEnd> cd ./vue-flow
> pnpm i
Scope: all 16 workspace projects
Lockfile is up to date, resolution step is skipped
Packages: +1497
+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Progress: resolved 1497, reused 1481, downloaded 0, added 1497, done

devDependencies:
+ @changesets/changelog-github 0.5.0
+ @changesets/cli 2.27.5
+ shx 0.3.4
+ turbo 2.0.4

Done in 11.3s
> pnpm dev
!!!!!!!!!!!!!!!! error !!!!!!!!!!!!!!!!!!!!

> pnpm run build
@vue-flow/monorepo@0.0.0 build H:\Git\Public\Group_FrontEnd\vue-flow
turbo build --filter='./packages/*'
• Packages in scope: 
• Running build in 0 packages
• Remote caching disabled
```

虚拟机再试一次：

```bash
vagrant@ubuntu-jammy:/vagrant/Git$ node -v
v20.17.0
vagrant@ubuntu-jammy:/vagrant/Git$ pnpm -v
9.12.0
vagrant@ubuntu-jammy:/vagrant/Git$ npm -v
10.8.2
vagrant@ubuntu-jammy:/vagrant/Git$ git clone https://github.com/bcakmakoglu/vue-flow.git
Cloning into 'vue-flow'...
remote: Enumerating objects: 34810, done.
remote: Counting objects: 100% (2550/2550), done.
remote: Compressing objects: 100% (1162/1162), done.
remote: Total 34810 (delta 1683), reused 1905 (delta 1339), pack-reused 32260 (from 1)
Receiving objects: 100% (34810/34810), 15.90 MiB | 6.44 MiB/s, done.
Resolving deltas: 100% (24538/24538), done.
Updating files: 100% (630/630), done.
vagrant@ubuntu-jammy:/vagrant/Git$ cd vue-flow/
vagrant@ubuntu-jammy:/vagrant/Git/vue-flow$ pnpm i
Scope: all 16 workspace projects
Lockfile is up to date, resolution step is skipped
Packages: +1501
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
 WARN  GET https://registry.npmjs.org/picocolors/-/picocolors-1.0.1.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 ERR_PNPM_META_FETCH_FAIL  GET https://registry.npmjs.org/pnpm: request to https://registry.npmjs.org/pnpm failed, reason: read ECONNRESET
 WARN  GET https://registry.npmjs.org/@algolia/client-search/-/client-search-5.1.1.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/@stackblitz/sdk/-/sdk-1.11.0.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/@algolia/requester-node-http/-/requester-node-http-5.1.1.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/@vercel/analytics/-/analytics-1.3.1.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/@algolia/client-common/-/client-common-5.1.1.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/server-only/-/server-only-0.0.1.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/react/-/react-18.2.0.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/@babel/parser/-/parser-7.24.7.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/loose-envify/-/loose-envify-1.4.0.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/vue/-/vue-3.4.38.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/@babel/types/-/types-7.23.9.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/@vue/compiler-dom/-/compiler-dom-3.4.38.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/@vue/compiler-core/-/compiler-core-3.4.38.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/@vercel/speed-insights/-/speed-insights-1.0.12.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/@babel/helper-string-parser/-/helper-string-parser-7.23.4.tgz error (ECONNRESET). Will retry in 10 seconds. 2 retries left.
 WARN  GET https://registry.npmjs.org/@babel/parser/-/parser-7.24.7.tgz error (ETIMEDOUT). Will retry in 1 minute. 1 retries left.
 WARN  GET https://registry.npmjs.org/@babel/types/-/types-7.23.9.tgz error (ETIMEDOUT). Will retry in 1 minute. 1 retries left.
 WARN  GET https://registry.npmjs.org/@vue/compiler-dom/-/compiler-dom-3.4.38.tgz error (ETIMEDOUT). Will retry in 1 minute. 1 retries left.
 WARN  GET https://registry.npmjs.org/@vue/compiler-core/-/compiler-core-3.4.38.tgz error (ETIMEDOUT). Will retry in 1 minute. 1 retries left.
 WARN  GET https://registry.npmjs.org/@vercel/speed-insights/-/speed-insights-1.0.12.tgz error (ETIMEDOUT). Will retry in 1 minute. 1 retries left.
 WARN  GET https://registry.npmjs.org/@babel/helper-string-parser/-/helper-string-parser-7.23.4.tgz error (ETIMEDOUT). Will retry in 1 minute. 1 retries left.
 WARN  GET https://registry.npmjs.org/@algolia/client-search/-/client-search-5.1.1.tgz error (ECONNRESET). Will retry in 1 minute. 1 retries left.
 WARN  GET https://registry.npmjs.org/@vercel/analytics/-/analytics-1.3.1.tgz error (ECONNRESET). Will retry in 1 minute. 1 retries left.
 WARN  GET https://registry.npmjs.org/@algolia/requester-node-http/-/requester-node-http-5.1.1.tgz error (ECONNRESET). Will retry in 1 minute. 1 retries left.
 WARN  GET https://registry.npmjs.org/@stackblitz/sdk/-/sdk-1.11.0.tgz error (ECONNRESET). Will retry in 1 minute. 1 retries left.
 WARN  GET https://registry.npmjs.org/server-only/-/server-only-0.0.1.tgz error (ECONNRESET). Will retry in 1 minute. 1 retries left.
 WARN  GET https://registry.npmjs.org/react/-/react-18.2.0.tgz error (ECONNRESET). Will retry in 1 minute. 1 retries left.
 WARN  GET https://registry.npmjs.org/loose-envify/-/loose-envify-1.4.0.tgz error (ECONNRESET). Will retry in 1 minute. 1 retries left.
 WARN  GET https://registry.npmjs.org/@algolia/client-common/-/client-common-5.1.1.tgz error (ERR_SOCKET_TIMEOUT). Will retry in 1 minute. 1 retries left.
 ETIMEDOUT  request to https://registry.npmjs.org/@babel/parser/-/parser-7.24.7.tgz failed, reason:

FetchError: request to https://registry.npmjs.org/@babel/parser/-/parser-7.24.7.tgz failed, reason:
    at ClientRequest.<anonymous> (/usr/lib/node_modules/pnpm/dist/pnpm.cjs:68502:18)
    at ClientRequest.emit (node:events:519:28)
    at emitErrorEvent (node:_http_client:108:11)
    at TLSSocket.socketErrorListener (node:_http_client:511:5)
    at TLSSocket.emit (node:events:531:35)
    at emitErrorNT (node:internal/streams/destroy:169:8)
    at emitErrorCloseNT (node:internal/streams/destroy:128:3)
    at process.processTicksAndRejections (node:internal/process/task_queues:82:21)
Progress: resolved 1501, reused 469, downloaded 9, added 445
vagrant@ubuntu-jammy:/vagrant/Git/vue-flow$ pnpm i --registry https://registry.npmmirror.com
Scope: all 16 workspace projects
Lockfile is up to date, resolution step is skipped
Packages: +1501
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Downloading typescript@5.4.5: 5.83 MB/5.83 MB, done
Downloading @iconify/json@2.2.241: 72.94 MB/72.94 MB, done
Downloading @quasar/extras@1.16.7: 32.78 MB/32.78 MB, done
Downloading turbo-linux-64@2.0.4: 9.93 MB/9.93 MB, done
Progress: resolved 1501, reused 478, downloaded 1007, added 1054, done
node_modules/.pnpm/@vercel+speed-insights@1.0.12_react@18.2.0_vue-router@4.2.5_vue@3.4.38_typescript@5.4.5___vue@3.4.38_typescript@5.4.5_/node_modules/@vercel/speed-insights: Running postinstall script, done in 390ms
node_modules/.pnpm/esbuild@0.20.1/node_modules/esbuild: Running postinstall script, done in 1.3s
node_modules/.pnpm/esbuild@0.19.12/node_modules/esbuild: Running postinstall script, done in 1.3s
node_modules/.pnpm/vue-demi@0.14.10_vue@3.4.38_typescript@5.4.5_/node_modules/vue-demi: Running postinstall script, done in 4.3s
node_modules/.pnpm/esbuild@0.19.4/node_modules/esbuild: Running postinstall script, done in 1.4s
node_modules/.pnpm/esbuild@0.14.51/node_modules/esbuild: Running postinstall script, done in 1.6s
node_modules/.pnpm/vue-demi@0.14.6_vue@3.3.4/node_modules/vue-demi: Running postinstall script, done in 3.8s
node_modules/.pnpm/esbuild@0.18.20/node_modules/esbuild: Running postinstall script, done in 1.4s
node_modules/.pnpm/vue-demi@0.14.10_vue@3.3.4/node_modules/vue-demi: Running postinstall script, done in 3.5s
node_modules/.pnpm/cypress@12.17.4/node_modules/cypress: Running postinstall script, done in 2m 41.1s

devDependencies:
+ @changesets/changelog-github 0.5.0
+ @changesets/cli 2.27.5
+ shx 0.3.4
+ turbo 2.0.4

Done in 9m 10.1s
vagrant@ubuntu-jammy:/vagrant/Git/vue-flow$ pnpm dev
(Seem normal)
```

Linux一开始是正常的，但后来有问题，很卡，感觉是我虚拟机给的CPU

### ……