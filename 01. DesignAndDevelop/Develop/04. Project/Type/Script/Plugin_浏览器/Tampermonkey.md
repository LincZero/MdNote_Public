# Tampermonkey

# 目录

# Tampermonkey

## 优秀脚本推荐



























# 插件开发

## 资料

参考：

- 书签用法
- 利用tampermonkey向页面注入自定义Javascript，https://blog.csdn.net/xue251248603/article/details/76419309
- 使用Tampermonkey动态修改网页的js，https://blog.csdn.net/sndayYU/article/details/98752373
- https://blog.csdn.net/iteye_15008/article/details/82580393
- https://www.jianshu.com/p/1bf123b3c8bf

## 修改js

### 一些失败尝试

```js
// ==UserScript==
// @name         Allegro部分限制解除
// @namespace    https://demo.allegro-packets.com/
// @version      0.1
// @description  Allegro部分限制解除
// @author       LincZero
// @match        *://demo.allegro-packets.com/*
// @icon         https://www.google.com/s2/favicons?sz=64&domain=allegro-packets.com
// @grant        none
// ==/UserScript==

// 拦截目标http脚本并修改（try3 失败，不是XMLHttpRequest请求，只是一个 <script defer="defer" src="main.ed1868.js"></script>）
/*document.documentElement.appendChild(Object.assign(document.createElement('script'), {
  textContent: `(${(() => {
    const originalOpen = XMLHttpRequest.prototype.open;

    XMLHttpRequest.prototype.open = function () {
      if (arguments[1].includes('http://localhost:8050/main.ed1868.js')) {
        arguments[1] = 'https://demo.allegro-packets.com/main.ed1868.js';
        console.log("替换成功");
      }
      return originalOpen.apply(this, arguments);
    };
  }).toString()})()`,
}));*/

(function() {
    // 原型修改，让dbCapable()的返回值恒为true（try2 失败，被webpack打包后闭包了）
    /*DatabaseModeSettingsCtrl.prototype.dbCapable = function() {
      return true;
   };*/

    /**
     * 移除原来的js然后添加一个新的js（try4）
     * 最接近成功的一次，然后前端显示：
     * The Allegro Network Multimeter interface relies on a HTML 5 capable browser with scripts enabled.
     * Your browser is either still loading the additional files, or scripts have been disabled.
     * If this message does not disappear after some short amount of time (depending on the speed of your network connection), check if scripts are enabled.
     */
    /*window.addEventListener('beforescriptexecute', function(e) {
        if (e.target.src.includes('main.ed1868.js')) {
            // Prevent the original script from loading
            e.preventDefault();
            e.stopPropagation();
            e.target.remove(); // Remove the original script
            var new_script = document.createElement('script'); // Create a new script element
            new_script.src = 'http://localhost:8050/main.ed1868.js'; // Point the source of the script to your desired location
            document.head.appendChild(new_script); // Append the new script to the head
            console.log("Script replaced successfully");
        }
    }, true);*/

    // try5。使用服务工作者（Service Workers）拦截和修改网络请求
    /*if ('serviceWorker' in navigator) {
        navigator.serviceWorker.register('sw.js').then(function(registration) {
            console.log('Service Worker registered with scope:', registration.scope);
        }).catch(function(error) {
            console.log('Service Worker registration failed:', error);
        });

        navigator.serviceWorker.ready.then(function(registration) {
            fetch('main.ed1868.js').then(function(response) {
                if (!response.ok) {
                    throw new Error("HTTP error, status = " + response.status);
                }
                return response.text();
            }).then(function(text) {
                let contentToAppend = `http://localhost:8050/main.ed1868.js`;
                text = text.replace("https://demo.allegro-packets.com/main.ed1868.js", contentToAppend);
                let blob = new Blob([text], {type: 'application/javascript'});
                let url = URL.createObjectURL(blob);
                registration.unregister().then(function() {
                    return navigator.serviceWorker.register(url);
                }).catch(function(error) {
                    console.log('Service Worker registration failed:', error);
                });
            }).catch(function(error) {
                console.log('Fetch Error:', error);
            });
        });
    } else {
        console.log("不支持serviceWorker");
    }*/

    // try5.2 （失败，报错：Uncaught (in promise) DOMException: ServiceWorkerContainer.register: Scope URL is not same-origin with Client）
    // 应用程式外挂无法注入非同源的 Service Worker，这是 Service Worker 的安全限制。
    /*navigator.serviceWorker.getRegistration().then(function(registration) {
        if (!!registration) {
            console.log("Unregistering a service worker.");
            registration.unregister();
        }
        navigator.serviceWorker.register("http://localhost:8050/sw.js").then(function() {
            console.log("Service worker has been registered.");
        });
    });*/

    // 显示隐藏字段
    document.head.appendChild(Object.assign(document.createElement('style'), { textContent: '.metismenu li.ng-hide {display: block !important;}' }));

    // 设置db-mode为true（try1 失败）
    /*var targetElement = document.getElementById('db-mode');
    if (targetElement) {
        // 设置 ng-if 值为 true
        targetElement.setAttribute('ng-if', 'true');
    }*/
})();
```

### 成功

成功，但是需要额外操作：

1. 本地提供的http服务，提供修改过的js

2. 如果是本地替换或非https网站不需要这步，否则要手动将浏览器解除限制：

   ```
   使用脚本后浏览器可能报错：已阻止加载混合活动内容“http://192.168.1.208:8050/main.ed1868.js”。
   那么在火狐浏览器地址栏输入：“about:config”，然后找到并更改“security.mixed_content.block_active_content”的设置为Flase
   ```

脚本内容：

```js
// ==UserScript==
// @name         Allegro部分限制解除2
// @namespace    https://demo.allegro-packets.com/
// @version      0.1
// @description  Allegro部分限制解除
// @author       LincZero
// @match        *://demo.allegro-packets.com/*
// @resource remoteJS http://localhost:8050/main.ed1868.js
// @run-at       document-start
// @icon         https://www.google.com/s2/favicons?sz=64&domain=allegro-packets.com
// @grant        none
// ==/UserScript==

var targScript = 'https://demo.allegro-packets.com/main.ed1868.js';
var newScript = 'http://localhost:8050/main.ed1868.js';

window.addEventListener('beforescriptexecute', function(e) {
    let src = e.target.src;
    if (src.search(targScript) > -1) {
        e.preventDefault();
        e.stopPropagation();
        loadScript(newScript);
    }
});

function loadScript(url) {
    var script = document.createElement('script');
    script.type = 'text/javascript';
    script.src = url;
    document.head.appendChild(script);
}

(function() {
    // 显示隐藏字段
    document.head.appendChild(Object.assign(document.createElement('style'), { textContent: '.metismenu li.ng-hide {display: block !important;}' }));
})();
```

### 配套的启动方式

下面这个失败，因为返回js的方式方式不对

```bash
python -m http.server 8050
```

后来使用了这个：

```python
import http.server
import socketserver

PORT = 8050

Handler = http.server.SimpleHTTPRequestHandler
Handler.extensions_map.update({
    '.js':  'application/javascript',
})

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print("serving at port", PORT)
    httpd.serve_forever()
```

本地替换能成功，但如果给其他人用的话，这里没有开http。需要对方手动关闭浏览器的限制











