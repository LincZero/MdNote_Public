---
last_time: 2020.03.19
tag: 有道云
---

# AndroidManifest.XML

这个XML文件是App清单文件

```xml
<?xml version="1.0" encoding="utf-8"?>
<manifest xmlns:android="http://schemas.android.com/apk/res/android"
    package="com.aide.trainer.myapp"
    android:versionCode="1"
    android:versionName="1.0" >

    <uses-sdk 
        android:minSdkVersion="11" 
        android:targetSdkVersion="17" />

    <application
        android:icon="@drawable/ic_launcher"
        android:label="@string/app_name" >
        <activity
            android:label="@string/app_name"
            android:theme="@android:style/Theme.Holo.Light"
            android:name=".MainActivity" >                                                // MainActivity是该App的启动Activity
            <intent-filter >
                <action android:name="android.intent.action.MAIN" />

                <category android:name="android.intent.category.LAUNCHER" />
            </intent-filter>
        </activity>
    </application>

</manifest>
```

