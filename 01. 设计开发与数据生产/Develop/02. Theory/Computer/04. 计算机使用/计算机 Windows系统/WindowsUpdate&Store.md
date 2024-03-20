# WindowsUpdata&Store

# 目录

## WindowsUpdata&Store

适用于18362.175以上，19041.0可能有问题？

### Windows Update服务

Windows Update > 禁用/启用

注意的是Windows Update除了影响Windows10自动，也影响这Microsoft Store是否能正常使用

Microsoft Store出错：https://tieba.baidu.com/p/6048767862#124300413197l，解决方法：启用Windows Update服务

### 出错解决——无法编辑服务

上述操作可能出错，**黄色感叹号：拒绝访问**

解决方案参考：https://blog.frytea.com/archives/49/，亲测文章+评论有用

注册表

> #### （1）

（这个好像不太紧要）

计算机\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\WaaSMedicSvc

右侧找到 “Start”，改为x（原3）

- 1→自动（延迟启动）
- 2→自动
- 3→手动
- 4→禁用

> #### （2）

（主要是这个配置）

计算机\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\wuauserv

右侧找到 “Start”，改为x（原3），该成和上面一样的

### 出错解决——无法编辑注册表

上述操作可能出错：**红色叉：无法编辑器Start：写该值的新内容时出错**

解决方法：单击菜单栏编辑→权限。为当前用户添加`完全控制`权限即可

### 出错解决——无法修改注册表权限

上述操作可能出错：**红色叉：无法保存对wuauserv权限所作的更改。拒绝访问**

解决方案参考：https://jingyan.baidu.com/article/3aed632ec4b9257010809183.html

编辑权限时 > 高级 > 审核 > 将所有者从SYSTEM更改为Admin管理员(Administrator) > 不退出窗口切到权限 > 双击管理员 > 在这个窗口里设置完全控制
不能在外面的窗口设置，要在高级设置窗口里设置才行

（注意，每个注册表项都要设置一次权限）

### 总结——精简方法

Windows恢复商店访问，需要开启自动更新
-> 开启自动更新，需要修改服务
-> 拒绝修改服务，需要修改注册表解除
-> 拒绝修改注册表，需要修改注册表权限
-> 拒绝修改注册表权限，需要修改注册表所有权
-> 修改注册表所有权
当恢复商店干完活后，还得原路恢复配置



前面是踩坑一步一步试的

最关键的一步是

计算机\HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\wuauserv

权限 > 高级 > 审核，换成管理员，并使用完全控制

## Windows 安全中心

略

## FF广告根治

### 服务

将启动类型改为禁用

可能出错：**黄色警告：拒绝访问**

那就先停止服务（防止后台占用）

![01](WindowsUpdate&Store.assets/01.png)

### 文件

搜索C:\Windows\SysWOW64\Macromed\Flash\FlashHelperService.exe，并关闭软件

可能出错：**操作无法完成，因为文件已在 Flash Helper Service 中打开**

可以尝试先停止服务，如果还是不行可以尝试在 Windows 安全模式下去关闭这个文件

![02](WindowsUpdate&Store.assets/02.png)





















