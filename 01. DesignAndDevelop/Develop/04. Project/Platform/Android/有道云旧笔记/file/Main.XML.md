---
last_time: 2020.03.20
tag: 有道云
---

# Main.XML

## Main.XML

```xml
<?xml version="1.0" encoding="utf-8"?>
<LinearLayout
    xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="fill_parent"
    android:layout_height="fill_parent"
    android:gravity="center"
    andeoid:orientation="vertical" >
    
    <TextView
        android:layout_width="wrap_content"  // 宽度
        android:layout_height="wrap_content"  // 高度
        android:textSize="30sp"  // 字号
        android:text="Hello World" />  // 文本

</LinearLayout>
```

## 组件（可视化开发，不用记）

```xml
LinearLayout 线性布局、嵌套布局
<LinearLayout
    xmlns:android="http://schemas.android.com/apk/res/android"
    android:layout_width="fill_parent"                 
    android:layout_height="fill_parent"
    android:gravity="center"                   // center，bottom
    andeoid:orientation="vertical" >           // vertical垂直，horizontal水平
    android:background="@drawable/my_bg"       // 背景图
</LinearLayout>



<TextView/>
    android:layout_width="wrap_content"       // 宽度 // wrap_content，match_parent最大填充但会挤压其他组件出去
    android:layout_height="wrap_content"      // 高度
    android:layout_weight="1.0"               // 类似于match_parent，但不会挤压其他组件出界
    android:layout_margin="20dp"              // 外间距
    android:padding="20dp"                    // 内边距
    android:text="Hello World"                // 文本
    android:textSize="30sp"                   // 文本字号
    android:textColor="#FFFFFF"               // 文本颜色
    android:textStyle="bold"                  // 文本样式
        
<ImageView/>
    android:src="@drawable/my_android_robot"  // 图片资源

<button/>
    android:onClick="onExitButtonClick"       // 单击事件onClick

<EditText/>
    android:hint="Subject"                    // 提示
    android:inputType="textEmailSubject"      // 输入类型 // textEmailSubject邮箱主题，textEmailAddress邮箱地址，textMultiLine多行
    android:ems="10"


    android:id="@+id/mainTextView1"
```

