# Uni-App

介绍：

`uni-app`是一个Vue.js开发所有前端应用框架，开发者编写一套代码，可发布到IOS、Android、H5、以及各种小程序（微信/支付宝/百度/头条/QQ/钉钉）等多个平台。

- 学习视频：https://www.bilibili.com/video/BV1BJ411W7pX?p=26
- 学习进度：`P0~P35-完成推荐商品结构`、`P54-完成小程序打包发布`

# 目录

[TOC]

# 基础部分

## [介绍]环境搭建

- HbuilderX

  编译器，[官网地址](https://www.dcloud.io/)，记住要下载`App开发版(283M)`而非`标准版(16.87M)`，其为Uni-App进行特别优化

- 微信开发者工具

  用作小程序开发预览以便调试，[官网地址](https://developers.weixin.qq.com/miniprogram/dev/devtools/download.html)

### 创建项目

![image-20200809135453145](Uni-App.assets/image-20200809135453145.png)

### 调试

菜单 > 运行 > 运行到浏览器 / 运行到小程序模拟器，后者需要先安装`微信开发者工具`

> 报错# HBuilderx浏览器运行尚不支持此种类型文件
>
> 解决方案：管理员打开HBuilderX

> 报错# 工具的服务端口已关闭。要使用命令行调用工具，请在下方输入 y 以确认开启，或手动打开工具 -> 设置 -> 安全设置，将服务端口开启
>
> 解决方案：如报错所示

### 项目结构

> - **pages** <!--页面相关-->
>   - **index**
>     - index.vue
> - **static** <!--静态资源-->
>   - logo.png
> - **unpackage** <!--打包相关-->
>   - **dist**
> - App.vue <!--根组件-->
> - main.js <!--入口脚本-->
> - manifest.json <!--发布相关配置(HBuilderX提供可视化操作)-->
> - pages.json <!--页面路径，窗口相关-->
> - uni.scss <!--常用样式变量-->

### 开发规则

- 页面文件遵循`Vue单文件组件（SFC）规范`
- 组件标签靠近`小程序规范`，详见`uni-app组件规范`
- 接口能力（JS API）靠近`小程序规范`，但需将前缀`wx`替换为`uni`，详见`uni-app接口规范`
- 数据绑定及事件处理同`Vue.js`规范，同时补充了App及页面的生命周期
- 为兼容多端运行，建议使用`flex布局`进行开发

## [框架]页面外观配置

详见[官网文档-框架](https://developers.weixin.qq.com/miniprogram/dev/reference/configuration/app.html) ，此处仅列举常用几种

### 全局配置

[官网文档内容](https://developers.weixin.qq.com/miniprogram/dev/reference/configuration/app.html)

`pages.json`中的`globalStyle`

| 属性                           | 类型       | 默认值       | 描述                                 |
| ---------------------------- | -------- | --------- | ---------------------------------- |
| navigationBarBackgroundColor | HexColor | `#F7F7F7` | 导航栏背景色                             |
| navigationBarTextStyle       | String   | white     | 导航栏标题色，仅支持black/white              |
| navigationBarTitleText       | String   |           | 导航栏标题内容                            |
| backgroundColor              | HexColor | `#ffffff` | 窗口背景色（下拉露出）                        |
| backgroundTextStyle          | String   | dark      | 下拉loading样式，仅支持dark/light          |
| enablePullDownRefresh        | Boolean  | false     | 是否开启下拉刷新，详见页面生命周期                  |
| onReachBottomDistance        | Number   | 50        | 页面上拉触底时间时距底部距离<br />仅支持px，详见页面生命周期 |

### 页面配置

[官网文档内容](https://developers.weixin.qq.com/miniprogram/dev/reference/configuration/page.html)

`pages.json`中的`pages`

| 属性  | 类型   | 默认值 | 描述             |
| ----- | ------ | ------ | ---------------- |
| path  | String |        | 配置页面路径     |
| style | Object |        | 配置页面窗口表现 |

### TabBar配置

| 属性            | 类型     | 必填 | 默认值 | 描述                            | 平台差异                    |
| :-------------- | :------- | ---- | ------ | ------------------------------- | --------------------------- |
| color           | HexColor | 是   |        | tab上文字默认颜色               |                             |
| selectedColor   | HexColor | 是   |        | tab上文字选中颜色               |                             |
| backgroundColor | HexColor | 是   |        | tab背景色                       |                             |
| borderStyle     | String   | 否   | black  | tabbar上边框颜色，仅black/white | App 2.3.4+ 支持其他颜色     |
| list            | Array    | 是   |        | tab列表，必须2~5                |                             |
| position        | String   | 否   | bottom | 可选值bottom、top               | TabBar位置，top值仅微信支持 |

### Condition启动模式配置
属性说明

| 属性     | 类型   | 是否必填 | 描述                             |
| :------- | :----- | -------- | -------------------------------- |
| current  | Number | 是       | 当前激活的模式，list节点的索引值 |
| list     | Array  | 是       | 启动模式列表                     |
| list说明 |        |          |                                  |
| 属性     | 类型   | 是否必填 | 描述                             |
| :----    | :----- | -------- | ------------                     |
| name     | String | 是       | 启动模式名称                     |
| path     | String | 是       | 启动页面路径                     |
| query    | String | 否       | 启动参数                         |

### 代码Demo

```javascript
{
"pages": [ //pages数组中第一项表示应用启动页，参考：https://uniapp.dcloud.io/collocation/pages
	{
        "path": "pages/index/index",
        "style": {
            "navigationBarTitleText": "uni-app"
        }
    },
    {
        "path": "pages/message/message",
        "style": {
            "navigationBarTitleText": "信息页",
            "navigationBarBackgroundColor": "#007AFF",
            "h5": { // 独有特性配置
                "pullToRefresh": {
                    "color": "#7D26CD"
                }
            }
        }
    }
],
"globalStyle": {
    // ...
},
"tabBar": {
    "color": "#A0522D",
    "selectedColor": "#B3EE3A",
    "list": [
        {
            "text": "首页",
            "pagePath": "pages/index/index",
            "iconPath": "static/tabs/home.png",
            "selectedIconPath": "static/tabs/home-active.png"
        },
        {
            // ...
        }
    ]
},
"condition": {
    "current": 0,
    "list": [
        {
            "name": "详情页",
            "path": "pages/detail/detail",
            "query": "id=80"
        }
    ]
}
} // 这里内部统一少一个缩进
```

## [框架]uni-app的组件通信

详见[官网文档-页面通讯](https://uniapp.dcloud.net.cn/collocation/frame/communication) 

### 父传子

用自定义属性`prop`

### 子传父

用自定义事件`$emit`

Vue的`this.$emit(eventName,Object)`

### 兄弟组件通信

`uni.$on(eventName,callback)`监听全局的自定义事件

`uni.$emit(eventName,Object)`触发全局的自定义事件

- 发送组件

```
uni.$emit('updataNum',10)
```

- 接受组件

```
created() {
    uni.$on('updataNum',(num)=>{
        this.num+=num
    })
}
```

## [组件]组件的使用

详见[官网文档-组件](https://developers.weixin.qq.com/miniprogram/dev/component/) ，此处仅列举常用几种

### 视图容器 - view

相当于div，[官网文档内容](https://developers.weixin.qq.com/miniprogram/dev/component/view.html)

| 属性                   | 类型    | 默认值 | 必填 | 说明                                   |
| ---------------------- | ------- | ------ | ---- | -------------------------------------- |
| hover-class            | String  | none   | 否   | 指定按下去的样式类                     |
| hover-stop-propagation | Boolean | false  | 否   | 指定是否阻止本节点的祖先节点出现点击态 |
| hover-start-time       | Number  | 50     | 否   | 按住后多久出现点击态度，单位ms         |
| hover-stay-time        | Number  | 400    | 否   | 手指松开后点击态保留时间，单位ms       |

### 基础内容 - text文本

相当于行内标签，[官网文档内容](https://developers.weixin.qq.com/miniprogram/dev/component/text.html)

| 属性       | 类型    | 默认值 | 必填 | 说明                                   |
| ---------- | ------- | ------ | ---- | -------------------------------------- |
| selectable | Boolean | false  | 否   | 文本是否可选                           |
| space      | String  |        | 否   | 显示连续空格，参数`ensp` `emsp` `nbsp` |
| decode     | Boolean | false  | 否   | 是否解码                               |

### 表单组件 - button按钮

按钮属性挺多的，详见[官网文档内容](https://developers.weixin.qq.com/miniprogram/dev/component/button.html)

| 属性     | 类型    | 默认值  | 必填 | 说明                                           |
| -------- | ------- | ------- | ---- | ---------------------------------------------- |
| size     | String  | defalut | 否   | 大小，参数：default、mini                      |
| type     | String  | defalut | 否   | 参数：primary视环境而定、default白色、warn红色 |
| plain    | Boolean | false   | 否   | 按钮是否镂空，背景色透明                       |
| disabled | Boolean | false   | 否   | 是否禁用                                       |
| loading  | Booean  | false   | 否   | 名称前是否带loading图标                        |

### 媒体组件 -image图像

[官网文档内容](https://developers.weixin.qq.com/miniprogram/dev/component/image.html)，注意：

- 该组件默认宽度300px、高度225px
- 组件中二维码/小程序码图片不支持长按识别。仅在wx.previewImage中支持长按识别

| 属性      | 类型    | 默认值      | 必填 | 说明                                                  |
| --------- | ------- | ----------- | ---- | ----------------------------------------------------- |
| src       | String  |             | 否   | 图片资源地址                                          |
| mode      | String  | scaleToFill | 否   | 图片裁剪、缩放的模式<br />常用：aspectFill、aspectFit |
| lazy-load | Boolean | false       | 否   | 图片懒加载，范围上下三屏                              |

## [组件]uni-app的UI库

详见[官网文档-扩展组件](https://uniapp.dcloud.net.cn/component/README?id=uniui)

`uni-ui`是DCloud提供的一个跨端ui库，基于vue组件的、flex布局的、无dom的跨端全端ui框架

不包含基础组件、是基础组件的扩充

使用方法：进入组件页 > 使用HBuilderX导入插件

## uni-app的样式

- rpx即响应式px，一种根据屏幕宽度自适应的动态单位。750rpx一横屏。

- 使用`@import`语句可以导入外联样式表

  ```vue
  <style>
  	@import url("./a.css");
  </style>
  ```

- 支持基本选择器class、id、element等，但不能使用`*`选择器

- page相当于body节点

- 定义在App.vue中的样式为全局样式，作用每一个页面。pages目录下的Vue文件定义的未局部样式

- 支持自体图标，注意：

  - 字体文件小于40kb会自动转成base64格式
  - 字体文件大于40kb需要自行转换
  - 字体文件的引用路径推荐使用以`~@`开头的绝对路径

  ```
  @font-face {
      font-family: test1-icon;
      src: url('~@/static/iconfont.ttf')
  }
  ```

- 如何使用scss或less：HBuilderX菜单 > 工具 > 插件安装 > scss/sass编译 > 安装后即可

## uni-app的数据绑定与事件

同Vue，略

## [Api]uni-app的生命周期

详见[官网文档-生命周期 ](https://uniapp.dcloud.net.cn/api/lifecycle)

生命周期概念：一个对象从创建、运行、销毁的整个过程被称为生命周期

生命周期函数：在生命周期的每个阶段会伴随每一个函数的触发，这些函数被称为生命周期函数

### 应用的生命周期

| 函数名   | 说明                               |
| -------- | ---------------------------------- |
| onLaunch | 初始化完成时触发（全局只触发一次） |
| onShow   | 启动，或从后台进入前台显示         |
| onHide   | 从前台进入后台                     |
| onError  | 报错时触发                         |

App.vue（初始项目本来就写着的）

```vue
<script>
	export default {
        onLaunch: function() {
            console.log('App Launch')
        },
        onShow: function() {
            console.log('App Show')
        },
        onHide: function() {
            console.log('App Hide')
        },
        onError: function(err) {
            console.log('[Err]',err)
        }
    }
</script>
```

### 页面的生命周期

页面通过TabBar切换默认不会销毁

| 函数名            | 说明                                                   |
| ----------------- | ------------------------------------------------------ |
| onLoad            | 监听页面加载，其参数为上个页面传递的数据，类型为Object |
| onReady           | 监听页面初次渲染完成                                   |
| onShow            | 监听页面显示                                           |
| onHide            | 监听页面隐藏                                           |
| onUnload          | 监听页面卸载                                           |
| onPullDownRefresh | 监听页面下拉刷新                                       |
| onReachBottom     | 页面滚动到底部的事件                                   |

### 组件的生命周期

同Vue

| 生命函数      | 说明                                      | 平台 |
| ------------- | ----------------------------------------- | ---- |
| beforeCreate  | 实例创建前调用（初始化后）                |      |
| created       | 实例创建后调用                            |      |
| beforeMount   | 挂载实例前调用（还没渲染）                |      |
| mounted       | 挂载实例后调用                            |      |
| beforeUpdate  | 数据更新时调用                            | 仅H5 |
| updated       | 数据更改导致虚拟DOM重新渲染和打补丁后调用 | 仅H5 |
| beforeDestroy | 实例销毁前调用（实例还在）                |      |
| destroyed     | 实例销毁后调用                            |      |

### 下拉刷新

1. 通过全局/页面配置`enablePullDownRefresh = true`来允许下拉刷新
2. 通过页面生命周期的`onPullDownRefresh`方法监听下拉刷新事件
3. 通过`uni.stopPullDownRefresh()`函数结束刷新，取消加载图标
4. 额外补充：除了下拉，也可以通过`uni.startPullDownrefresh（Object)`方法来触发刷新事件

### 上拉加载

1. 通过全局/页面配置`onReachBottomDistance = Number`可设置触底事件距离参数，来优化提前加载
2. 通过页面生命周期的`onReachBottom`方法监听触底事件事件
3. 额外补充：list追加数据es6新写法：`this.list = [...this.list,...['new1','new2']]`

## [Api]网络请求

[官网文档内容](https://uniapp.dcloud.net.cn/api/request/request)

发起请求：uni.request(Object)

> 需要注意：
>
> 小程序中网络相关的API在使用前需要配置域名白名单
>
> 本地调试：
>
> 使用`WeChatDevTools`时，如果请求失败
>
> 工具栏菜单 > 详情 > 本地设置 > 勾选不校验合法域名...

代码Demo

```javascript
uni.request({
    url: "https://uniapp.dcloud.net.cn/api/request/request",
    data: {}, // 可选，请求参数
    method: "GET", // 可选，默认值GET
    timeout: "30000", // 可选，超时时间，默认值30s
    dataType: "json", // 可选，默认json，会对返回数据做一次JSON.parse
    success (res) { // 请求成功的回调函数
        console.log(res)
    },
    fail (err) { //请求失败的回调函数
        console.log(err)
    }
})
```

## [Api]数据缓存

还有`uni.clearStorage`或`uni.clearStorageSync`，直接清除本地所有数据缓存

此处略，详见[官网文档内容](https://uniapp.dcloud.net.cn/api/storage/storage?id=setstorage)

### uni.setStorage

Object参数

| 参数名   | 类型     | 必填 | 说明                                                         |
| -------- | -------- | ---- | ------------------------------------------------------------ |
| key      | String   | 是   | 本地存储中指定的key                                          |
| data     | Any      | 是   | 需要存储的内容，只支持原生类型、及能JSON.stringify序列化的对象 |
| success  | Function | 否   | 成功回调函数                                                 |
| fail     | Function | 否   | 失败回调函数                                                 |
| complete | Function | 否   | 结束回调函数                                                 |

存储下来的数据

可到浏览器调试的中查看`存储/Application>Storage`

或小程序开发工具调试器的`Storage`中查看

代码Demo

```javascript
uni.setStorage({
    key: 'id',
    data: 80,
    success () {
        console.log('存储成功')
    }
})
```

### uni.setStorageSync

```javascript
uni.setStorageSync('id', 100)
```

### uni.getStorage

Object参数

| 参数名   | 类型     | 必填 | 说明                                  |
| -------- | -------- | ---- | ------------------------------------- |
| key      | String   | 是   | 本地存储中指定的key                   |
| success  | Function | 是   | 成功回调函数，res={data: key对应内容} |
| fail     | Function | 否   | 失败回调函数                          |
| complete | Function | 否   | 结束回调函数                          |

代码Demo

```javascript
uni.getStorage({
    key: 'id',
    suceess (res) {
        console.log('Success:', res.data)
    }
})
```

### uni.getStorageSync

```javascript
const res = uni.getStorageSync('id')
```

### uni.removeStorage

```javascript
uni.removeStorage({
	key: 'id',
	success () {
		console.log("删除成功")
	}
})
```

### uni.removeStorageSync

```javascript
uni.removeStorageSync('id')
```

## [Api]图片上传和预览

详见[官网文档内容](https://uniapp.dcloud.net.cn/api/media/image)

### uni.chooseImage(Obj)

作用为本地相册选择图片或使用相机拍照，参数：

| 参数名     | 类型          | 必填 | 说明                                                   | 平台差异说明                                      |
| ---------- | ------------- | ---- | ------------------------------------------------------ | ------------------------------------------------- |
| count      | Number        | 否   | 最多选择图片张数，默认9                                | H5只能限制单选/多选<br />手机少有能支持多选的     |
| sizeType   | Arr\<String\> | 否   | compressed压缩图，<br />original原图<br />默认两者都有 | 5+App、微信小程序、<br />支付宝小程序、百度小程序 |
| sourceType | Arr\<String\> | 否   | album相册选图<br />camera用相机<br />默认两者都有      |                                                   |
| success    | Function      | 是   | 成功返回图片本地文件路径列表                           |                                                   |
| fail       | Function      | 否   | 失败回调                                               | 小程序、5+App                                     |
| complete   | Function      | 否   | 结束回调                                               |                                                   |

代码Demo

```javascript
uni.chooseImage({
    count: 5,
    success:res => {
        this.imgArr = res.tempFilePaths
    }
})
```

### uni.previewImage(Obj)

预览图片，参数：

| 参数名   | 类型            | 必填 | 说明                   | 平台差异说明 |
| -------- | --------------- | ---- | ---------------------- | ------------ |
| current  | String/Number   | 不定 | 需要浏览的当前图片     | 不定         |
| urls     | Array\<String\> | 是   | 需要浏览的图片链接列表 |              |
| success  | Function        | 否   | 成功回调               |              |
| fail     | Function        | 否   | 失败回调               |              |
| complete | Function        | 否   | 结束回调               |              |

```javascript
uni.previewImage({
    current: current, // 该值由图片传进来
    urls: this.imgArr
})
```

## [介绍]条件注释实现跨端兼容

参数值

| 值         | 平台                           | 参考文档                                                     |
| ---------- | ------------------------------ | ------------------------------------------------------------ |
| App-PLUS   | 5+App                          | [HTML5+规范](http://www.html5plus.org/doc/zh_cn/geolocation.html) |
| H5         | H5                             |                                                              |
| MP-WEIXIN  | 微信小程序                     | [微信官方文档](https://developers.weixin.qq.com/miniprogram/dev/devtools/download.html) |
| MP_ALIPAY  | 支付宝小程序                   | [开放平台文档](https://opendocs.alipay.com/mini/component)   |
| MP-BAIDU   | 百度小程序                     | [百度小程序文档](https://smartprogram.baidu.com/docs/develop/component/component/) |
| MP-TOUTIAO | 头条小程序                     | [头条/字节跳动小程序文档](https://microapp.bytedance.com/docs/zh-CN/mini-app/develop/component/all) |
| MP-QQ      | QQ小程序                       | (目前仅cli版本支持)                                          |
| MP         | 微信/支付宝/百度/头条/QQ小程序 |                                                              |

代码Demo
```vue
<template>
    <!-- #ifdef H5 -->
    <view>只能在H5看见</view>
    <!-- #endif -->
    <!-- #ifdef MP-WEIXIN -->
    <view>只能在微信小程序看见</view>
    <!-- #endif -->
</template>
<script>
	export default {
        onLoad () {
            // #ifdef H5
            console.log('H5中打印')
            // #endif
            // #ifdef MP-WEIXIN
            console.log('微信小程序中打印')
            // #endif
        }
    }
</script>
<style>
    /* #ifdef H5 */
    view {
        color: hotpink;
    }
    /* #endif */
    /* #ifdef MP-WEIXIN */
    view {
        color: #0000FF;
    }
    /* #endif */
</style>
```

## 导航跳转[组件&APi]

### 声明式跳转 - navigator

详见[官网文档-navigation-bar ](https://uniapp.dcloud.net.cn/component/navigation-bar)

属性

| 属性名    | 类型   | 默认值   | 说明                                        | 平台差异 |
| --------- | ------ | -------- | ------------------------------------------- | -------- |
| url       | String |          | 相对或绝对路径                              |          |
| open-type | String | navigate | 跳转方式，参数详见表                        |          |
| delta     | Number |          | 回退的层数，当open-type为'navigateBack'有效 |          |

open-type属性

| 值           | 说明                                         | 平台差异                         |
| ------------ | -------------------------------------------- | -------------------------------- |
| navigate     | 对应uni.navigateTo，默认值，跳转后有返回键   |                                  |
| redirect     | 对应uni.redirectTo，卸载页面，跳转后无返回键 |                                  |
| switchTab    | 对应uni.switchTab，调转到TabBar下的页面      |                                  |
| uavigateBack | 对应uni.navigateBack，回退                   |                                  |
| exit         | 退出小程序，target="miniProgram"时生效       | 微信2.1.0+、百度2.5.2+、QQ1.4.7+ |

代码Demo

```vue
<template>
	<view>
    	<navigator url="/pages/detail/detail">
            跳转至详情页
    	</navigator>
        <navigator url="/pages/message/message" open-type="switchTab">
            跳转至信息页  <!--跳转到TabBar页面要加open-type-->
    	</navigator>
    </view>
</template>
```

### 编程式跳转

详见官网文档API，或open-type属性表

```javascript
uni.navigateTo({
    url: '/pages/detail/detail'
})
uni.redirectTo({
    url="/pages/message/message"
})
```

### 导航跳转传递参数

```vue
<template>
	<view>
    	<navigator url="/pages/detail/detail?id=80&age=19">跳转至详情页</navigator>
    </view>
</template>
<script>
    export default {
    	onLoad(options) {
        	console.log(options) // {id:'80', age:'19'}
    	}
    }
</script>
```

## 组件创建和通讯

# 开发过程补充

## [Api]交互反馈

- uni.showToast

  ```javascript
  uni.showToast({
      title: '网络资源请求失败'
  })
  ```

- uni.hideToast

- uni.showLoading

- uni.hideLoading

- uni.showModal

- uni.showActionSheet

## Promise封装网络请求

- /util/api.js

```javascript
const BASE_URL = 'http://localhost:8082/'
export const myRequest = (options)=> {
    return new Promise((resolve,reject)=>{
        uni.request({
            url: BASE_URL+options.url,
            method: options.method || 'GET',
            data: options.data || {},
            success: (res)=>{
                if(res.data.status !== 0) { // res.statusCode !== 200
                    return uni.showToast({
                        title:'获取数据失败'
                    })
                }
                resolve(res)
            }
            fail: (err)=>{
            	uni.showToast({
                    title:'请求接口失败'
                })
            	reject(err)
        	}
        })
    })
}
```

- /main.js

  挂载到Vue原型就可以全局访问了

```javascript
import Vue from 'vue'
import App from './App'
// 新增代码：
import { myRequest } from './util/api.js'
Vue.prototype.$myRequest = myRequest
```

- /pages/index/index.vue

```javascript
onLoad() {
    this.getSwipers()
}
methods: {
    async getSwipers() { // 这里用了ES7的async-await方法
        const res = await this.$myRequest({
            url: '/api/getlunbo'
        })
        this.swipers = res.data.message
    }
}
```

## 微信开发者工具调试器

调试器中`Storage`，相当于浏览器FireFox的`存储`或者Google的`Application>Storage`，可查看本地存储

调试器中`AppData`  ，相当于`VueDevTools`的功能可以看到Vue实例里的`Data`数据

可配合`Condition启动模式`使用，开发过程中快速跳转到某页

## 字体图标

配置好字体样式和CSS后，可以通过view指定的class名来让使其变成图标

注：icon-font可以使用font-class

## 踩坑 - 自定义组件

微信小程序不支持组件懒加载的写法

```javascript
// #ifdef MP
import index from "@/pages/index/index.vue"
// #endif
export default {
    components: {
		// #ifdef H5
    	index: ()=>import("@/pages/index/index.vue")
    	// #endif
		// #ifdef MP
        index
		// #endif
    }
}
```

# 项目部分

## 黑马商城项目
