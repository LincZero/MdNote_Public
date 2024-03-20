# JNI

# 目录

# JNI (Java Native Interface，Java原生接口)

是NDK (Native Develop Kit，原生开发组件) 里的一个接口

参考文档：

- https://developer.android.com/training/articles/perf-jni?hl=zh-cn

## 介绍

JNI 是指 Java 原生接口。它定义了 Android 从受管理代码（使用 Java 或 Kotlin  编程语言编写）编译的字节码与原生代码（使用 C/C++ 编写）互动的方式。JNI  不依赖于供应商，支持从动态共享库加载代码，虽然有时较为繁琐，但效率尚可。

















## 参数通信

参考：[C/C++ 和Java 相互传递参数通信](https://blog.csdn.net/hj_key/article/details/106102841)

### C 调用 Java 方法

参考：[C/C++ 和Java 相互传递参数通信](https://blog.csdn.net/hj_key/article/details/106102841)

大体分两种：

1. 反射找方法

   先在 Activity 中调用 JNI 方法，然后通过C 中[反射](https://so.csdn.net/so/search?q=反射&spm=1001.2101.3001.7020)，找到activity的类以及方法，进行调用。

   该方法有个弊端，只能在当前线程中使用，项目中用处实用性太小。

2. 全局变量存Java方法（本文主推方法）

   在activity 中先启动一个JNI 调用，将 activity 当前类 保存到C中存为 **全局变量**。
   然后在需要使用的 C 文件中，使用这个全局变量找到activity的类，和方法，然后进行调用。

```java
// activity 中声明本地方法   
public static native String listenOrientation();
 
// C 中需要调用的Java 方法
// 要注意静态变量,C 中调用处是静态的，这里必须要静态
public static int changeScreen(int width, int height) {
     // do  someing
     return 0;
}
 
 
// 在适宜的时机调用，以便C中保存数据，(我是在onCreate 中调用，JNI加载完后调用)
String str = listenOrientation();
 
// CPP 文件中创建 JNI 方法
 
JavaVM *g_jvm = NULL;
jobject g_obj = NULL;
 
 
extern "C" JNIEXPORT jstring JNICALL
Java_org_libsdl_app_SDLActivity_listenOrientation(
        JNIEnv *env, jclass thiz) {
    std::string hello = "zhj Hello from C++";
    hello += avcodec_configuration();
 
    env->GetJavaVM(&g_jvm);
 
    // Attach主线程
    if (g_jvm->AttachCurrentThread(&env, NULL) != JNI_OK) {
        LOGE("%s: zhj AttachCurrentThread() failed", __FUNCTION__);
        return NULL;
    }
    g_obj = env->NewGlobalRef(thiz); // 重点在这里保存全局变量
 
 
    return env->NewStringUTF(hello.c_str());
}
```

#### 签名相关

https://blog.csdn.net/qq_21358401/article/details/79265357

Java方法是带有签名的,而C/C++ native方法要调用Java方法 需要知道Java方法的签名.
在terminal下:
首先编译出class文件

#### 单独编译java版本

单独编译java版本，https://blog.csdn.net/u011304970/article/details/75713209

### Java 向 C 传递数据

参考：[C/C++ 和Java 相互传递参数通信](https://blog.csdn.net/hj_key/article/details/106102841)





































# 系统教程

参考：

- https://www.bilibili.com/video/BV188411V7Yq（1h快速入门版，选）
- https://www.bilibili.com/video/BV1qW411L7oY（10h详细版）

详见另一挂笔记























# 案例

## C 获取Android ip/mac

失败版本：

```c
    // JNI环境
    JNIEnv* env = g_jniEnv;
    if (!env) {
        LOGE("获取Java环境失败");
        return;
    }

    // Java虚拟环境 (在其他线程上调用JNI函数，需要使用AttachCurrentThread方法)
    JavaVM* jvm;
    env->GetJavaVM(&jvm);
    if (!jvm) {
        LOGE("获取Java VM环境失败");
        return;
    }
    int getEnvStat = jvm->GetEnv((void**)&env, JNI_VERSION_1_6);
    if (getEnvStat == JNI_EDETACHED) {
        if (jvm->AttachCurrentThread(&env, NULL) != 0) {
            LOGE("Java未能连接当前线程");
            return;
        }
    } else if (getEnvStat == JNI_EVERSION) {
        LOGE("获取Java环境状态失败，不支持版本");
        return;
    } else if (getEnvStat == JNI_OK) {
        //
    }

    // Java类
    jclass cls = env->FindClass(JAVA_CLASS_PATH);
    if (!cls) {
        LOGE("获取 java class 失败");
        if(getEnvStat == JNI_EDETACHED) jvm->DetachCurrentThread();
        return;
    }

    // Java方法
    jmethodID ipMethodId = env->GetMethodID(cls, "getLocalIpAddress", "()Ljava/lang/String;");
    jmethodID macMethodId = env->GetMethodID(cls, "getLocalMacAddress", "()Ljava/lang/String;");
    if(ipMethodId == NULL || macMethodId == NULL) {
        LOGE("获取 java method 失败");
        if(getEnvStat == JNI_EDETACHED) jvm->DetachCurrentThread();
        return;
    }

    // 调用Java方法获取返回值
    jobject object = env->AllocObject(cls);
    jstring ip = (jstring)env->CallObjectMethod(object, ipMethodId);
    jstring mac = (jstring)env->CallObjectMethod(object, macMethodId);
    const char *ipStr = env->GetStringUTFChars(ip ,NULL);
    const char *macStr = env->GetStringUTFChars(mac, NULL);
    m_local_ip = ipStr;
    m_local_mac = macStr;

    // 不要忘记释放
    env->ReleaseStringUTFChars(ip, ipStr);
    env->ReleaseStringUTFChars(mac, macStr);

    if(getEnvStat == JNI_EDETACHED) jvm->DetachCurrentThread();
```

## C 获取Android硬件信息和系统信息 (__system_property_get)

参考：[【CSDN】纯C代码获取android硬件信息和系统信息，不依赖JNI](https://blog.csdn.net/u011393891/article/details/113407057)

> 获取android无非有三种方式：
>
> 1.  通过java代码获取
> 2. 通过jni获取(本质是通过C++调用android接口获取)
> 3. 直接通过C代码获取编译成动态库
>
> 每种方式都有其优点和缺点。
>
> - 比如通过android接口获取mac地址时，获取到的是当前在使用的网卡的mac地址
> - 比如当有线切换到无线时，获取到的mac地址会发生变化
> - 而通过C代码因为本身不依赖于android，所以有些接口无法调用，或者有些命令无法执行，导致获取失败，比如获取imei时，通过android接口可以获取到imei，但是在C代码中却不能获取到。
>
> 在通过NDK编译代码成为andorid的动态库时，NDK本身提供了一些接口来获取系统硬件信息：

缺点：

> __system_property_get 是 Android 系统中的一个函数，用于获取 Android 系统中的一些属性信息。但是该函数并**不能直接获取到 IP 和 MAC 地址**。
>
> 获取 IP 和 MAC 地址通常需要使用 Android 中的网络接口，例如 WifiManager 和 NetworkInterface 类，从而获取到设备所在网络的相关信息。
>
> 由此，如果你想要获取这些信息，你需要在 Android 应用中请求相关的网络权限，然后使用相关 API 来获取这些信息，而不是直接使用 __system_property_get 函数。

参考：https://blog.csdn.net/zymill/article/details/126693092

```cpp
#include <sys/system_properties.h>

typedef struct SDeviceInfo
{
    char szId[128];
    char szPlatform[128];
    char szHardware[128];

    char szBrand[128]; // 品牌客户名称
    char szManufacturer[128]; // 产品/硬件的制造商名称
    char szCpuAbi[128];
    char szCpuAbiList[256];
    char szModel[128]; // 终端用户可见的产品名称，可以有空格
    char szDevice[128]; // 采用的设备，作用范围：adb shell进去时显示的名称客户项目代号，不要有空格
    char szBoard[128]; // 采用的底板/处理器客户项目代号
} SDeviceInfo;

static SDeviceInfo g_devInfo;
__system_property_get("ro.build.id",             g_devInfo.szId);
__system_property_get("ro.hardware",             g_devInfo.szHardware);
__system_property_get("ro.board.platform",       g_devInfo.szPlatform);
__system_property_get("ro.product.brand",        g_devInfo.szBrand);
__system_property_get("ro.product.manufacturer", g_devInfo.szManufacturer);
__system_property_get("ro.product.cpu.abi",      g_devInfo.szCpuAbi);
__system_property_get("ro.product.cpu.abilist",  g_devInfo.szCpuAbiList);
__system_property_get("ro.product.model",        g_devInfo.szModel);
__system_property_get("ro.product.device",       g_devInfo.szDevice);
__system_property_get("ro.product.board",        g_devInfo.szBoard);

```

华为电视查询结果

```c
[device_info_init] ro.build.id       : HUAWEIKANT-350S
[device_info_init] ro.board.platform : honghu818
[device_info_init] ro.hardware       : honghu8xx
[device_info_init] ro.product.brand  : HUAWEI
[device_info_init] ro.product.manufacturer: HUAWEI
[device_info_init] ro.product.cpu.abi: arm64-v8a
[device_info_init] ro.product.cpu.abilist: arm64-v8a,armeabi-v7a,armeabi
[device_info_init] ro.product.model  : KANT-350S
[device_info_init] ro.product.device : HWKANT-350S
[device_info_init] ro.product.board : KANT
```

ro.product 属性

```c
* ro.product.brand	// 品牌客户名称
* ro.product.model	// 终端用户可见的产品名称，可以有空格
* ro.product.manufacturer	// 产品/硬件的制造商名称
* ro.product.name	// 手机正式名称客户项目代号，不要有空格，如果包含空格，会导致Google账号无法登陆
* ro.product.board	// 采用的底板/处理器客户项目代号
* ro.product.device	// 采用的设备，作用范围：adb shell进去时显示的名称客户项目代号，不要有空格
* ro.build.product	// 已经过时，现在使用“ro.product.device”，等同于“ro.product.device”
```

Android 系统属性详情（创维电视案例）

```c
# begin build properties
# autogenerated by buildinfo.sh
ro.build.id=LMY47V
ro.build.display.id=LMY47V.20181229 test-keys
ro.build.version.incremental=20181229
ro.build.version.sdk=22
ro.build.version.codename=REL
ro.build.version.all_codenames=REL
ro.build.version.release=5.1.1
ro.build.version.security_patch=2015-11-01
ro.build.version.base_os=
ro.build.date=Sat Dec 29 15:13:24 CST 2018
ro.build.date.utc=1546067604
ro.build.type=user
ro.build.user=www-data
ro.build.host=rjyby07
ro.build.tags=test-keys
ro.build.flavor=p351-user
ro.product.model=8A20 V8E
ro.product.brand=Skyworth
ro.product.name=p351
ro.product.device=p351
ro.product.board=p351
# ro.product.cpu.abi and ro.product.cpu.abi2 are obsolete,
# use ro.product.cpu.abilist instead.
ro.product.cpu.abi=armeabi-v7a
ro.product.cpu.abi2=armeabi
ro.product.cpu.abilist=armeabi-v7a,armeabi
ro.product.cpu.abilist32=armeabi-v7a,armeabi
ro.product.cpu.abilist64=
ro.product.manufacturer=Skyworth
ro.product.locale.language=zh
ro.product.locale.region=CN
ro.wifi.channels=11
ro.board.platform=gxbaby
# ro.build.product is obsolete; use ro.product.device
ro.build.product=p351
# Do not try to parse description, fingerprint, or thumbprint
ro.build.description=p351-user 5.1.1 LMY47V 20181229 test-keys
ro.build.fingerprint=Skyworth/p351/p351:5.1.1/LMY47V/20181229:user/test-keys
ro.build.characteristics=mbx,nosdcard
# end build properties
#
# from device/customer/p351/system.prop
#
#add for Coocaa5.x by liyang
init.svc.adbd=stopping
persist.sys.usb.config=mtp
ro.build.dev_owner=system
ro.build.3Dflag=0
ro.sf.lcd_density=240
ro.product.model=8A20 V8E
ro.product.brand=Skyworth
ro.product.manufacturer=Skyworth
ro.build.ccos.type=mix
ro.build.skymodel=8A20
ro.build.skytype=V8E
ro.build.skymid=T968
ro.build.skyversion.svn=default
ro.build.skyversion.tianci=default
persist.service.homepage.pkg=com.coocaa.homeshell
persist.service.homepage.cls=com.coocaa.homeshell.Activity
third.get.4k=1
third.get.h265=1
#SystemService set
third.get.mac=0
third.get.barcode=0
third.get.launcher.start=0
third.get.factory=0
third.get.facSingleKeyEnable=false
#add by liyang end

#add by sunsikai for new start flow start
persist.get.facSingleKeyEnable=0
#add by sunsikai for new start flow end

# Set display related config
ro.platform.has.mbxuimode=true
ro.platform.has.tvuimode=true
ro.platform.has.realoutputmode=true

debug.hwui.render_dirty_regions=false
#camera max to 720p
ro.camera.preview.MaxSize=1280x720
ro.camera.preview.LimitedRate=1280x720x30,640x480x30,320x240x28
ro.camera.preview.UseMJPEG=1

persist.sys.fastboot=false
persist.sys.strictmode.disable=true

#if wifi Only
ro.radio.noril=false

#if need pppoe
ro.net.pppoe=true

#Dolby DD+ decoder option
#for TV/IPTV need set RF drc mode by default
#if defined this prop,will overwrite the value of
#/sys/class/audiodsp/ac3_drc_control
#"CUSTOM_0","CUSTOM_1","LINE","RF"
ro.dolby.drcmode=3
#this prop to for videoplayer display the DD+/DD icon when playback
ro.platform.support.dolby=true
#DTS decoder option
#display dts icon when playback
ro.platform.support.dts=true
#DTS-HD support prop
#ro.platform.support.dtstrans=true
#ro.platform.support.dtsmulasset=true
#DTS-HD prop end
# Enable player buildin
media.amplayer.seekkeyframe=true
media.amsuperplayer.enable=true
media.amplayer.enable-acodecs=ac3,eac3,rm,dts
media.amplayer.enable=true
media.amsuperplayer.m4aplayer=STAGEFRIGHT_PLAYER
media.amsuperplayer.defplayer=PV_PLAYER
media.amplayer.thumbnail=true
media.amplayer.widevineenable=false
media.amplayer.dsource4local=1
media.amplayer.startmode=true
media.arm.audio.decoder=ape,flac,dts,ac3,eac3,wma,wmapro,mp3,aac,vorbis,raac,cook,amr,pcm,adpcm,aac_latm,rm
media.wfd.use-pcm-audio=false
media.wfd.videoresolution-type=1
media.wfd.videoresolution-group=0
media.wfd.videoframerate=24
media.wfd.video-bitrate=2000000
media.html5videowin.enable=1
media.decoder.vfm.defmap=decoder ppmgr deinterlace amvideo
media.dtv.running=1
const.bootanim.delay=2500
#add for not seek chinese track automaticly
audio.track.default.chinese=false
#add for video boot, 1 means use video boot, others not .
service.bootvideo=1
# default boot video volume
sys.bootvideo.vol=5

# Define drm for this device
drm.service.enabled=1

#used forward seek for libplayer
media.libplayer.seek.fwdsearch=1

#fix dd test av sync
media.libplayer.fillzerothrsh=27000

#disable slowsync
libplayer.slowsync.disable=true

#fix hls sync
libplayer.livets.softdemux=1
libplayer.netts.recalcpts=1

#map volume
ro.audio.mapvalue=0,0,0,0

#add livhls,libcurl as default hls
media.libplayer.curlenable=true
media.libplayer.modules=vhls_mod,dash_mod,curl_mod,prhls_mod,vm_mod

#add for chezhenwu
media.libplayer.show_firstframe=0

#Hdmi In
ro.sys.hdmiin.enable=true
mbx.hdmiin.switchfull=false
mbx.hdmiin.videolayer=false

#adb
service.adb.tcp.port=5555

#switch different remote control
persist.sys.remoteid=0e

#hdcp22_key control
persist.sys.hdcp22key=false

#blutooth volume
persist.sys.T868.bluth.val=30
######## UBOOTENV VARIBLES - r/w as system properties ##########
#
#  Now we can load ubootenv varibles to system properties.
#  We use a special prefix ("ubootenv.var" as default) to indicate that the 'property'
#  actually is an ubootenv varible.
#
#  A ubootenv 'property' will be initialized during system booting. And when user set
#  a different value, it will be written back to ubootenv device immediately.
#

## prefix of ubootenv varibles - should less than 16 chars.
#UBOOTENV MTD NAME
#ubootenv.var.bootcmd=
#ubootenv.var.cpuclock=
#ubootenv.var.gpuclock=
#ubootenv.var.memsize=
#ubootenv.var.ethaddr=
#ubootenv.var.ipaddr=
#ubootenv.var.gatewayip=
ubootenv.var.outputmode=
#ubootenv.var.screenratio=
#ubootenv.var.oobeflag=
ubootenv.var.480p_x=
ubootenv.var.480p_y=
ubootenv.var.480p_w=
ubootenv.var.480p_h=
ubootenv.var.480i_x=
ubootenv.var.480i_y=
ubootenv.var.480i_w=
ubootenv.var.480i_h=
ubootenv.var.576p_x=
ubootenv.var.576p_y=
ubootenv.var.576p_w=
ubootenv.var.576p_h=
ubootenv.var.576i_x=
ubootenv.var.576i_y=
ubootenv.var.576i_w=
ubootenv.var.576i_h=
ubootenv.var.720p_x=
ubootenv.var.720p_y=
ubootenv.var.720p_w=
ubootenv.var.720p_h=
ubootenv.var.1080p_x=
ubootenv.var.1080p_y=
ubootenv.var.1080p_w=
ubootenv.var.1080p_h=
ubootenv.var.1080i_x=
ubootenv.var.1080i_y=
ubootenv.var.1080i_w=
ubootenv.var.1080i_h=
ubootenv.var.4k2k24hz_x=
ubootenv.var.4k2k24hz_y=
ubootenv.var.4k2k24hz_w=
ubootenv.var.4k2k24hz_h=
ubootenv.var.4k2k25hz_x=
ubootenv.var.4k2k25hz_y=
ubootenv.var.4k2k25hz_w=
ubootenv.var.4k2k25hz_h=
ubootenv.var.4k2k30hz_x=
ubootenv.var.4k2k30hz_y=
ubootenv.var.4k2k30hz_w=
ubootenv.var.4k2k30hz_h=
ubootenv.var.4k2k50hz_x=
ubootenv.var.4k2k50hz_y=
ubootenv.var.4k2k50hz_w=
ubootenv.var.4k2k50hz_h=
ubootenv.var.4k2k60hz_x=
ubootenv.var.4k2k60hz_y=
ubootenv.var.4k2k60hz_w=
ubootenv.var.4k2k60hz_h=
ubootenv.var.4k2ksmpte_x=
ubootenv.var.4k2ksmpte_y=
ubootenv.var.4k2ksmpte_w=
ubootenv.var.4k2ksmpte_h=
ubootenv.var.digitaudiooutput=
ubootenv.var.defaulttvfrequency=
ubootenv.var.has.accelerometer=
ubootenv.var.cecconfig=
ubootenv.var.cvbsmode=
ubootenv.var.hdmimode=
ubootenv.var.is.bestmode=
ubootenv.var.disp.fromleft=
ubootenv.var.edid.crcvalue=

## p351 control uboot env
ubootenv.var.firstboot=
ubootenv.var.ipaddr=
ubootenv.var.gatewayip=
ubootenv.var.suspend=
ubootenv.var.ubootversion=
ubootenv.var.usbboot=
#disable panel rotate
ubootenv.var.has.accelerometer=
ubootenv.var.upgradefbc=
ubootenv.var.outputmode=
ubootenv.var.lcd_reverse=
ubootenv.var.console_bug=
ubootenv.var.panel_id=
ubootenv.var.panel_type=
ubootenv.var.bootfusb=
ubootenv.var.reboot_mode=
ubootenv.var.bootonetime=

tv.need.preview_window=true
#TV project,set omx to video layer,or PQ hasn't effect
media.omx.display_mode=1

#
# ADDITIONAL_BUILD_PROPERTIES
#
ro.config.wallpaper=/system/etc/default_wallpaper.png
ro.build.skyversion=018.012.290
ro.com.android.dateformat=MM-dd-yyyy
ro.config.ringtone=Ring_Synth_04.ogg
ro.config.notification_sound=pixiedust.ogg
ro.carrier=unknown
ro.config.alarm_alert=Alarm_Classic.ogg
ro.opengles.version=131072
camera.disable_zsl_mode=1
ro.app.optimization=true
ro.product.firmware=00502001
ro.product.otaupdateurl=http://10.28.11.53:8080/otaupdate/update
persist.sys.timezone=Asia/Shanghai
dalvik.vm.heapstartsize=16m
dalvik.vm.heapgrowthlimit=192m
dalvik.vm.heapsize=512m
dalvik.vm.heaptargetutilization=0.75
dalvik.vm.heapminfree=512k
dalvik.vm.heapmaxfree=8m
sys.fb.bits=32
ro.hdmi.device_type=0
wifi.interface=wlan0
config.disable_bluetooth=false
ro.config.media_vol_steps=100
ro.product.support.tvaudio=true
drm.service.enable=true
ro.platform.has.pppoe=true
config.disable_instaboot=false
persist.sys.dalvik.vm.lib.2=libart.so
dalvik.vm.isa.arm.features=default
dalvik.vm.dexopt-flags=m=y
net.bt.name=Android
```

## Recorder 案例 - java调用cpp

< MainActivity.java

```java
package com.holowan.recorder;
import com.holowan.recorder.databinding.ActivityMainBinding;

public class MainActivity extends AppCompatActivity {

    // Used to load the 'recorder' library on application startup.
    static {
        System.loadLibrary("recorder");
    }
    
    ...
        
    /** 创建事件 */
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        binding = ActivityMainBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        File file = new File("web");
        deleteDirWihtFile(file);
        copyAssetsDir2Phone(this, "web");

        // 步骤1：采用匿名类，直接 创建 线程类的实例
        new Thread("native-main") {
            // 步骤2：复写run（），内容 = 定义线程行为
            @Override
            public void run() {
                // 步骤3：通过 线程对象 控制线程的状态，如 运行、睡眠、挂起  / 停止
                recorder();
            }
        }.start();

        setContentView(R.layout.activity_main);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON); // 保持亮屏 (防止熄屏导致连接断开，关屏保持连接以后再修)
        bindViews();
    }
    
    ...
        
    /** 入口函数 (多语言交互，cpp实现给java调用) */
    public native int recorder();
    
    ...
        
}
```

< main.cpp

```cpp
#if defined(ANDROID) || defined(__ANDROID__)
	#include <jni.h>
#endif

// 进入程序
#if defined(ANDROID) || defined(__ANDROID__)
extern "C" JNIEXPORT jint JNICALL
Java_com_holowan_recorder_MainActivity_recorder(JNIEnv *env, jobject) {
    g_ctrl.java_env = env;
#else
int main(int argc, char **argv) {
#endif
    ...
}
```

## Recorder 案例 - js调用java (其实这个不属于JNI部分)

< MainActivity.java

```java
/**
 * web前端剪切板 (多语言交互，java实现暴露给js调用)
 * 注意：这里看起来没有被调用，但其实不然。是注入到js接口里让前端来调用这个代码的
 */
public class WebAppInterface {
    Context mContext;

    /** 实例化接口并设置上下文 */
    WebAppInterface(Context c) {
        mContext = c;
    }

    /** 显示网页上的toast */
    @JavascriptInterface
    public void copyToClipboard(String text) {
        ClipboardManager clipboard = (ClipboardManager) mContext.getSystemService(Context.CLIPBOARD_SERVICE);
        ClipData clip = ClipData.newPlainText("label", text);
        clipboard.setPrimaryClip(clip);
    }
}
```

demo.js

```html
<button onclick="Android.copyToClipboard('复制的文本')">复制到剪切板</button>
```























