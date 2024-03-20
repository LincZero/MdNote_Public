参考：https://gist.github.com/laispace/666dd7b27e9116faece6

本地代理

```bash
git config --global https.proxy http://127.0.0.1:1080

git config --global https.proxy https://127.0.0.1:1080

git config --global --unset http.proxy

git config --global --unset https.proxy

npm config delete proxy
```

 Windows 10 clash (亲测有效)

```bash
git config --global http.proxy socks5://127.0.0.1:7890
git config --global https.proxy socks5://127.0.0.1:7890

# 如果只想对某个地址进行代理，比如对 github.com 代理，就这样：
git config --global http.https://github.com.proxy socks5://127.0.0.1:7890
```

方法二

```bash
clone: git clone -c http.proxy="127.0.0.1:xxxx" https://github.com/Gump8/xxxx.git
fetch upstream: git -c http.proxy="127.0.0.1:xxxx" fetch upstream
    *注意： fetch 后面不能 -c，clone 是可以的
```

