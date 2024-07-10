# WindowsDebugginTools分析dmp蓝屏文件

# 目录

# dmp蓝屏文件

## Windows事件查看器

这个好像也能看一点，但不是很详细，不能分析dmp蓝屏文件

但比如强制关机这种事件还是可以看的

## WindowsDebugginTools分析

### 软件下载

#### 官网下载途径（仅UWP）

https://www.microsoft.com/zh-cn/p/windbg/9pgjgd53tn86?rtc=1&activetab=pivot:overviewtab

从这个链接跳转到Microsoft Store，或者直接在Microsoft Store中搜索WinDbg Preview

我也不太清楚为什么官网中只能提供UWP下载而没有exe安装方式

#### 其他途径（exe）

使用参考：https://tieba.baidu.com/p/3648007851

软件下载链接：http://www.beihaiting.com/a/ZSK/CYRJXZ/2014/0119/3863.html

然后输入如下的微软调试符号集网址：http://msdl.microsoft.com/download/symbols

### 软件操作

#### dmp位置、与设置生成

一般位置在：C:\Windows\LiveKernelReports

也可以通过 系统 > 高级系统设置 > 高级 > 启动和故障恢复 > 高级 > 转储文件 处查看dmp文件生成/修改的路径（emmm好像不是）

可以在注册表中设置是否生成dmp蓝屏文件，方法此处略，参见https://www.cnblogs.com/yudongdong/p/9687320.html

默认是自动生成的

#### dmp生成分析报告

把dmp文件拖拽进去或软件打开dmp文件，稍等一会完成加载

然后主窗口的txt中有这么一行：For analysis of this file, run [!analyze -v]()。点这个链接即可

第二种方法是直接在主窗口后面输入命令行`> !analyze -v`并运行

点完以后再主窗口的文本后面会生成新的文本，这个文本的开头是：

```
*******************************************************************************
*                                                                             *
*                        Bugcheck Analysis                                    *
*                                                                             *
*******************************************************************************
```

这个就是分析报告了

### bug报告分析

下面这个是我的一次电脑崩溃的dmp文件分析

崩溃体现

> 首先是一个软件卡死无响应（这个软件可以是任意软件），关闭窗口也无响应，任务管理器也无法关闭
>
> 一段时间后，提示 “Microsoft Winodws 无响应”，问你是否关闭进程
>
> 接着软件相序变卡并崩溃，一个接着一个用不了（这个时间段较长）
>
> 在完全崩溃之前，我电脑的一个盘显示不出容量大小，任务管理器的性能中，该盘的活动也是一直满载的
>
> 初步判断是磁盘满了造成的问题，这个磁盘目前的占用情况：（157GB可用/7.27GB），按道理不应该满

bug报告

```js
0: kd> !analyze -v
*******************************************************************************
*                                                                             *
*                        Bugcheck Analysis                                    *
*                                                                             *
*******************************************************************************

EXRESOURCE_TIMEOUT_LIVEDUMP (1cc)							// ex资源超时_live/.dmp
A kernel ERESOURCE has timed out. This can indicate a deadlock condition or	// 内核资源超时
heavy contention which can cause performance issues.		// 这可能表明存在死锁条件或严重的争用，这会导致性能问题。
Arguments:													// 参数
Arg1: ffffb3016dbe2bd0, The ERESOURCE that has timed out	// 资源超时，已超时的 ERESOURCE
Arg2: ffffb301814c7080, The thread that detected the timeout// 检测到超时的线程
Arg3: 00000000000000fa, The ERESOURCE contention count		// 资源争用计数，计267次
Arg4: 0000000000000096, The configured timeout in seconds	// 配置的超时时间(秒)，计1min36s

Debugging Details:											// 调试细节
------------------


KEY_VALUES_STRING: 1										// 键值的字符串

    Key  : Analysis.CPU.mSec
    Value: 3328

    Key  : Analysis.DebugAnalysisManager
    Value: Create

    Key  : Analysis.Elapsed.mSec
    Value: 57874

    Key  : Analysis.Init.CPU.mSec
    Value: 1718

    Key  : Analysis.Init.Elapsed.mSec
    Value: 280223

    Key  : Analysis.Memory.CommitPeak.Mb
    Value: 82

    Key  : WER.OS.Branch
    Value: 19h1_release

    Key  : WER.OS.Timestamp
    Value: 2019-03-18T12:02:00Z

    Key  : WER.OS.Version
    Value: 10.0.18362.1


DUMP_FILE_ATTRIBUTES: 0x10									// 转储文件属性
  Live Generated Dump

BUGCHECK_CODE:  1cc											// BUGCHECK代码

BUGCHECK_P1: ffffb3016dbe2bd0

BUGCHECK_P2: ffffb301814c7080

BUGCHECK_P3: fa

BUGCHECK_P4: 96

FAULTING_THREAD:  ffffb301867e1040

PROCESS_NAME:  System

STACK_TEXT:  													// 堆栈调用
fffff08b`45785b50 fffff804`3d83b7e2     : ffffc900`b6f5e180 000000f9`ffffffff ffffc900`b6f5e101 ffffb301`867e1040 : nt!KiSwapContext+0x76
fffff08b`45785c90 fffff804`3d83ae74     : ffffb301`00000009 00000000`00000000 ffffb301`00000000 00000000`00000000 : nt!KiSwapThread+0x3f2
fffff08b`45785d30 fffff804`3d83a615     : fffff08b`45785e90 fffff804`00000000 00000000`00000000 00000000`00000000 : nt!KiCommitThreadWait+0x144
fffff08b`45785dd0 fffff804`3ff7e113     : fffff08b`45786388 ffffb301`00000000 00000000`00f02000 00000000`00eff000 : nt!KeWaitForSingleObject+0x255
fffff08b`45785eb0 fffff804`3ff797a0     : ffffb301`867e1360 fffff804`3d83960d ffffb301`867e1040 ffffb301`6d68ad78 : Ntfs!NtfsNonCachedIo+0x4d3
fffff08b`45786160 fffff804`3ff7b017     : ffffb301`80b4e528 ffffb301`7b4db710 ffffb301`6d68ad30 00000000`00eff000 : Ntfs!NtfsNonCachedUsaWrite+0x10c
fffff08b`45786220 fffff804`3ff7a248     : ffffb301`80b4e528 00000000`00000001 fffff08b`45787890 00000000`00000000 : Ntfs!NtfsCommonWrite+0xb27
fffff08b`45786450 fffff804`3d831cc9     : ffffb301`7f2c7ba0 ffffb301`7b4db710 ffffb301`7b4dbaf8 ffffb301`6da96d80 : Ntfs!NtfsFsdWrite+0x1e8
fffff08b`45786520 fffff804`3f4e55de     : 00000000`00000000 fffff08b`45786600 ffffb301`7b4db710 fffff08b`45786610 : nt!IofCallDriver+0x59
fffff08b`45786560 fffff804`3f4e3f16     : fffff08b`45786600 00000000`00000000 00000000`00000001 00000000`00000000 : FLTMGR!FltpLegacyProcessingAfterPreCallbacksCompleted+0x15e
fffff08b`457865e0 fffff804`3d831cc9     : ffffb301`7b4db710 fffff804`3d831d07 00000000`0000000d 00000000`00000004 : FLTMGR!FltpDispatch+0xb6
fffff08b`45786640 fffff804`3d853dc3     : fffff08b`45786870 ffffb301`7b4db710 ffffb301`6dd936d0 ffffb301`6da96d80 : nt!IofCallDriver+0x59
fffff08b`45786680 fffff804`3d91ae8c     : 00000000`00000000 fffff08b`45786720 ffffb301`6dd936d0 ffffb301`6dd936d0 : nt!IoSynchronousPageWriteEx+0x137
fffff08b`457866c0 fffff804`3d8bc8b8     : 00000000`00000011 ffffa007`bea837f8 00000000`00eff000 ffff9c00`0caaea70 : nt!MiIssueSynchronousFlush+0x70
fffff08b`45786740 fffff804`3d80932e     : fffff08b`45786a80 fffff08b`45786c70 ffffb301`6dd936d0 fffff08b`45786ad8 : nt!MiFlushSectionInternal+0x868
fffff08b`45786a10 fffff804`3d807abd     : 00000000`00000000 ffffb301`867e1040 00000000`00003000 00000000`00eff000 : nt!MmFlushSection+0x166
fffff08b`45786ac0 fffff804`3d929436     : ffffb301`6d91f8b0 fffff08b`45786cb8 ffffb301`00003000 00000000`00000000 : nt!CcFlushCachePriv+0x6cd
fffff08b`45786c10 fffff804`3ff948d2     : 00000002`5e1e025f fffff804`00000000 00000002`00000000 00000002`5e1e0484 : nt!CcFlushCache+0x16
fffff08b`45786c50 fffff804`3ff74c8f     : 00000002`5e1e0483 00000000`00eff000 00000002`5e1e025f 00000002`00001000 : Ntfs!LfsFlushLfcbPriv+0xce
fffff08b`45786cb0 fffff804`3ff73ed5     : ffffa007`c1055d30 00000002`5e1e0484 fffff804`3ff73e01 fffff08b`45786f00 : Ntfs!LfsFlushLfcb+0xd9f
fffff08b`45786ed0 fffff804`3d871a28     : fffff08b`45786fe0 ffffa007`c1096001 00000000`00000001 00000000`00000010 : Ntfs!LfsFlushLfcbCallout+0x25
fffff08b`45786f00 fffff804`3d87199d     : fffff804`3ff73eb0 fffff08b`45786fe0 00000000`00000000 ffffc900`b7000180 : nt!KeExpandKernelStackAndCalloutInternal+0x78
fffff08b`45786f70 fffff804`3ff756ac     : 00000000`00000000 ffffa007`c1492301 ffffa007`c1492301 ffffa007`c1096001 : nt!KeExpandKernelStackAndCalloutEx+0x1d
fffff08b`45786fb0 fffff804`4003496b     : 00000002`00000000 00000000`45787940 ffffa007`c1055d30 00000000`00000000 : Ntfs!LfsFlushLfcbOnNewStack+0x58
fffff08b`45787010 fffff804`40075ad9     : ffffa007`c1055d30 fffff08b`45787940 fffff08b`45787940 ffffa007`c12e3528 : Ntfs!LfsFlushToLsnPriv+0x183
fffff08b`457870b0 fffff804`40074f0a     : ffffa007`c1055d30 ffffa007`c1055d30 00000000`00000000 ffffb301`6dda44a8 : Ntfs!LfsWriteLfsRestart+0x13d
fffff08b`45787110 fffff804`40089c9d     : ffffa007`bedb5780 00000002`00000070 fffff08b`457875d0 ffffb301`00000000 : Ntfs!LfsWriteRestartArea+0x19e
fffff08b`45787260 fffff804`4008c60a     : 00000000`00000001 fffff804`3d8362bf 00000000`00000000 ffffb301`867e1000 : Ntfs!NtfsCheckpointVolume+0xe11
fffff08b`45787720 fffff804`4003bc03     : fffff08b`457878d0 ffffb301`6dda4180 fffff08b`45787880 01d72eba`bf86fee1 : Ntfs!NtfsCheckpointAllVolumesWorker+0xda
fffff08b`45787790 fffff804`4003b45e     : fffff08b`457878d0 00000000`00000000 00000000`00000000 fffff804`4008c530 : Ntfs!NtfsForEachVcb+0x207
fffff08b`45787840 fffff804`3d8c4855     : ffffb301`65886010 ffffb301`867e1040 ffffb301`65886010 fffff804`3ffff1b0 : Ntfs!NtfsCheckpointAllVolumes+0x1de
fffff08b`45787b70 fffff804`3d92f725     : ffffb301`867e1040 00000000`00000080 ffffb301`658a82c0 00000000`00000001 : nt!ExpWorkerThread+0x105
fffff08b`45787c10 fffff804`3d9c3dfa     : ffffc900`b7000180 ffffb301`867e1040 fffff804`3d92f6d0 00000000`00000000 : nt!PspSystemThreadStartup+0x55
fffff08b`45787c60 00000000`00000000     : fffff08b`45788000 fffff08b`45782000 00000000`00000000 00000000`00000000 : nt!KiStartSystemThread+0x2a


STACK_COMMAND:  .thread 0xffffb301867e1040 ; kb

SYMBOL_NAME:  nt!KiSwapContext+76

MODULE_NAME: nt

IMAGE_NAME:  ntkrnlmp.exe

BUCKET_ID_FUNC_OFFSET:  76

FAILURE_BUCKET_ID:  LKD_0x1cc_EXRESOURCE_TIMEOUT_OWNERTHREAD_nt!KiSwapContext

OS_VERSION:  10.0.18362.1

BUILDLAB_STR:  19h1_release

OSPLATFORM_TYPE:  x64

OSNAME:  Windows 10

FAILURE_ID_HASH:  {ba09c374-1e32-1908-d12a-b95209a3dc5b}

Followup:     MachineOwner
---------

```

## 用其他软件打开（VS）

VS也是能打开的，但VS只能打开4G大小的文件（可以改大，但改大以后虽然能打开了，但加载不出内容）

如果只是简单使用则还是推荐用WindowsDebugginTools



































