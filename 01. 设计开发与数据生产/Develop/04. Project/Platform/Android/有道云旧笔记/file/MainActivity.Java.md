---
last_time: 2020.03.19
tag: 有道云
---

# MainActivity.Java

```java
package com.aide.trainer.myapp;

import android.app.*;
import android.os.*;

public class MainActivity extends Activity            // 启动Activity
{
    /** Called when the activity is first created. */
    @Override
    public void onCreate(Bundle savedInstanceState) // Acitvity创建时调用
    {
        super.onCreate(savedInstanceState);
        // Set main.xml as user interface layout
        setContentView(R.layout.main);               // 关联布局文件
    }
}
```

