---
last_time: 2020.03.19
tag: 有道云
---

# Strings.XML

## Strings.XML

```xml
<?xml version="1.0" encodeing="utf-8"?>
<resources>
    <string name="app_name">My Android App</string>
    <string name="hi_text">Hi World</string>
</resources>
```

## XML中使用

```xml
android:text="@string/hi_text"
```

**在应用程序中，总是对说有文本使用字符串资源，以便翻译时直接添加另一个资源文件和翻译即可**
