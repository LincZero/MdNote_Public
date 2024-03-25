---
last_time: 2020.03.20
tag: 有道云
---

# Android指令

## 一些写在监听器里的Android指令

```java
// 退出软件
finish();

// 动画
TranslateAnimation animation = new TranslateAnimation(0, 0, 0, 1000);
animation.setDuration(1000);
view.startAnimation(animation);

// 消息
Toast.makeText(this, "Wrond!", Toast.LENGTH_SHORT).show();
Toast.makeText(this, "Wrond!", Toast.LENGTH_Long).show();
    // 注意！类中的内部类或本类中引用了其他类的方法（或重写）的时候，this指内部类或者其他的类，而不是外部类！
    // this要变成所在外部类的this，如MainActivity.this！
```

