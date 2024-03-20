# BT宝塔

# 搭建

看宝塔官网，记得挺方便的

# 后续

查看入口：

```
# bt default
```

![img](BT宝塔.assets/clipboard.png)

# 注意事项

# 坑一：访问BT的SQL数据库

## BT宝塔一样内置安全组

使用SQL数据库时务必设置可访问ip（默认为本地）与`安全>放行端口`（默认无3306，也无Nodejs端口）

然后重启一下MySQL，不然访问不了

