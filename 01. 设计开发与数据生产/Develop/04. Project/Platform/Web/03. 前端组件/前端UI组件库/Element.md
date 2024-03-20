# Element - 饿了么组件

## 官方使用文档【zh】

https://element.eleme.cn/#/zh-CN/component/installation

## 简易教程

## Vue准备

```shell
node -v
npm install -g cnpm --registry=https://registry.npm.taobao.org
cnpm install -g [@vue/cli] # +2:+@vue/cli-init # 2:vue-cli
vue create project1 # vue init webpack project1
```

## 使用

```shell
npm i element-ui -S
创建test.vue并复制一段elementUI官方文档的代码，进行测试
在App.vue中引入test.vue
```

## 在App.vue中引入test.vue

```vue
<template>
	<div id="app">
    	<Test></Test>
	</div>
</template>
<script>
    import Test from './components/test.vue'
    export default {
        name: 'App',
        components:{
            Test
        }
    }
</script>
```

## 打开main.js,加入element-ui的js和css

```javascript
import ElementUI from 'element-ui' //element-ui的全部组件-js
import 'element-ui/lib/theme-chalk/index.css'//element-ui的css
Vue.use(ElementUI) //使用elementUIja
```

## 再次运行，成功