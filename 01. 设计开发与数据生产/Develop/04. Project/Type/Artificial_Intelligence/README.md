# Artificial_Intelligence

## 参考资料

### 学习路线

- 基础
  - 高等数学、线性代数、概率论

- 学习路线
  - "啥都生"的AI学习路线：https://www.bilibili.com/video/BV16341177c1
  - 然后结合我自己的经验：
    下面的课程中，吴恩达的最适合零基础，虽然反而是有点说得太清楚过头了的感觉
    我刚开始试过直接看 CS231n 和 李宏毅 的课，较难看懂，都是看了前几p弃了
- 个人学习进度笔记
  - 已看完
    - Deeplearning.ai - 2022机器学习
    - Deeplearning.ai - 2021深度学习（跳过了RNN和选修部分）
    
  - 正在看
    - 无


### 视频课程

#### 斯坦福系列

- CS131 / 李飞飞，也是李飞飞负责的，接触计算机视觉（默认学CS231n之前学过这门课了，与CS231n有些知识点是重叠的）
- CS224n，深度学习、自然语言处理
- CS231a，**更全面**的计算机视觉课程，专注于3D的重建、匹配和机器人视觉等方面
- ==CS231n / 李飞飞==，计算机视觉课程，专注于一类特定的算法，**从机器学习的角度**，围绕神经网络、特别是卷积神经网络，并应用于各种视觉识别任务
  - 视频：https://www.bilibili.com/video/BV1nJ411z7fe，这个2017版的可能有点旧
  - 官方笔记：https://cs231n.github.io/
    评论区笔记：https://github.com/zhuole1025/cs231n（英）

#### 吴恩达系列

这人出了好几门课，然后每门课的版本又很多。我刚开始区分时不开也有点懵圈



==吴恩达==，在网易课堂和B站有，说的是英文但是会有中文字幕（但基本是机翻）

- ~~CS229版~~（斯坦福版，不推荐）

- 网易云版（旧版，不推荐）

  - 视频：https://www.bilibili.com/video/BV1LE411h7P4（网易云版）

- Deeplearning.ai 机器学习

  - 视频（搬运）：https://www.bilibili.com/video/BV1Pa411X76s（Deeplearning.ai 版）
    视频（外网）：[Coursera-Machine Learning 官方讲义链接](https://www.coursera.org/learn/machine-learning/resources/JXWWS)

    - 都看一半时，突然发现有个人译版本：https://www.bilibili.com/video/BV1Zt4y1H78P（上面的是机翻这个人翻，不过视频很糊，还是算了）

  - 半官方笔记/资料：https://github.com/kaieye/2022-Machine-Learning-Specialization（全英，很杂，有pdf ppt **ipynb**）
    ~~网上搜的别人的笔记：https://blog.csdn.net/euffylee/article/details/113783758~~（但这人居然只写了一章）

  - 课件中程序常见报错与解决

    > python画图报错：Unknown projection ‘3d’
    >
    > 加入`from mpl_toolkits.mplot3d import Axes3D`即可

- Deeplearning.ai 深度学习（学完机器学习再学深度学习）

  - 视频：[吴恩达《深度学习》视频课程全集_哔哩哔哩_bilibili](https://www.bilibili.com/video/BV16r4y1Y7jv)（黄海广版）
    [(强推|双字)2021版吴恩达深度学习课程Deeplearning.ai](https://www.bilibili.com/video/BV12E411a7Xn)（啥都生版）
    这两视频内容一样的，后者可能补充一点其他章节。
    至于字幕后者的 个人感觉前者会好一点，不过黄海广用的是B站字幕可以爬来做笔记，又不过笔记也有现成的所以也没必要
  - pdf笔记（github）：https://github.com/fengdu78/deeplearning_ai_books（黄海广博士和同学整理，包含799页可打印pdf，优点是中文）
    pdf笔记（百度云）：https://pan.baidu.com/s/1EIu04R_Pn7shXk1DGo4QyQ?pwd=43s2pdf

- NLP序列模型（专题，第五门课程）

  - 视频：https://www.bilibili.com/video/BV1Co4y1279R

- 不同版本之间比较

  - 注意有旧版和新版，新版是在 Deeplearning.ai 上的，当然其他网站也有搬运，弥补老版知识点老旧的缺陷，而且新版本用的Python老版本不是
    新版本好的是用了 “Python”，坏的是依然用了 “Google开摆了的tensorflow”（因为tf一点点被Pytorch吃份额，现在都是推荐用Pytorch入门，国内高校基本用的也是Pytorch）

  - | 版本                               | B站分p    | 时长     | 怎么认？                                               |
    | ---------------------------------- | --------- | -------- | ------------------------------------------------------ |
    | CS229版 - 2018秋季                 | 20        | 26:33:15 | 讲台式教学，每p一节2h的课                              |
    | CS229版 - 2019夏季                 | 23        | 41:57:24 | 讲台式教学，每p一节2h的课                              |
    | 网易云版                           | 112/113集 | 19:31:16 | 可以看得出相机质量不是很好、拍摄背景偏黄               |
    | **Deeplearning.ai - 2022机器学习** | 142集     | 19:37:02 | 有Deeplearning.ai 的 较小logo                          |
    | **Deeplearning.ai - 2021深度学习** | 181集/192 | 27:19:55 | 有Deeplearning.ai 的 超大logo，有黄海广和同学整理的pdf |

#### 国语系列

- ==李宏毅==，相比于斯坦福机器学习系列。优点是讲的是普通话而不是英语，虽然有点台湾腔
  
  - 他的大部分视频都在油管：https://www.youtube.com/c/HungyiLeeNTU，国内搬运的只有一部分，还是得去ytb看！
    
  - 相关视频：https://www.bilibili.com/video/BV1Wv411h7kN（2021+2022补丁）
    相关视频：https://www.bilibili.com/video/BV1J94y1f7u5（2022）
    
  - 2022课程与2021课程基本相同，李老师只做小补充，UP会标识2022，会根据22课程大纲将内容进行相应更新
    关于两版本的区别的CSDN补充：https://blog.csdn.net/zzh516451964zzh/article/details/123212671
    
  - **网友的笔记**：https://github.com/unclestrong/DeepLearning_LHY21_Notes
    （注意：由于他存在gitee的图片不能显示，要下载下来的pdf才能正常看图）
    （注意：他的笔记主要是用自动生成字幕的拼接，会有比较多的错别字）
    （由于这个笔记有图，所有我自己的笔记里就懒得重复配图了，仅作一些思绪的整理，**必须结合使用**）
    
  - 课件和资料Github版：https://github.com/Fafa-DL/Lhy_Machine_Learning
    课件和资料Gitee版：https://gitee.com/zzhzwh/Lhy_Machine_Learning
    
  - Noter补充：
    
    > 和吴恩达机器深度学习和cs231n的课比起来，更全
    > 比如有讲生成对抗性网络（GAN）、自监督式模型、模型攻击、机器终身学习、元学习等。
    > 其他机器学习课程少有讲这些的
    >
    > 然后就是，可能是少有的中文机器学习课程的缘故吧，这播放量和弹幕是真的多
  
- 浙大胡浩基老师机器学习课程

- 跟李沐学AI，动手学深度学习系列

### 大佬账号类

- B站
  - [啥都会一点的研究生](https://space.bilibili.com/46880349)，搬运。了比较多大佬的课
  - [跟李沐学AI]()，原创，大佬。有教课，也有读论文
  - [霹雳吧啦Wz](https://space.bilibili.com/18161609)，原创。比较多动手的内容，全部视频看完就很大佬了
  - [同济子豪兄](https://space.bilibili.com/1900783)，原创
- Youtube
  - [李宏毅](https://www.youtube.com/c/HungyiLeeNTU)，原创，大佬。虽然国内也有搬运课程，但不够油管里的全

### 书类

- 《机器学习》周志华
  - 大名鼎鼎的 **“西瓜书”** ，书本封面底部有一堆西瓜，并且作者喜欢使用西瓜来作比喻而得名，很好辨认
  - 书是入门书，较简单，需搭配其他课程或者参考书。
    另外往往搭配南瓜书作为 “公式字典” 使用（西瓜书里的公式没有推导）

- 《机器学习公式详解》**开源**，谢文睿 秦州
  - 有 “西瓜书”，自然也有 **“南瓜书”**，南瓜在封面的顶部而非底部。南瓜书是开源免费的，当然你也可以去买纸质版
  - 西瓜书作者给的建议：“以西瓜书为主线，遇到自己推导不出来或看不懂的公式时再来查阅南瓜书”

- 略，蘑菇书
- 《深度学习 Deep Learning》
  - 也叫 **“花书”**，因为封面照片是一丛粉紫色的花
  - 被誉为 **“深度学习圣经”**

- 《统计学习方法》李航
  - 更枯燥一点

- 《神经网络与深度学习 Neural Networds and Deep Learning》MichaelNielsen著

- 《动手学深度学习 v2》李沐，电子书**开源**，B站有账号


### 论文类

- B站：跟李沐学AI
- 本地资源那堆

### 视觉方向

- 《OpenCV3 编程入门》
- 北大 黄琳琳 MOOC
- 唐宇迪 OpenCV
- CS231n

### 实用网站

- [Scikit-learn](scikit-learn.org/stable/) 是一个非常广泛使用的开源机器学习库。比如提供了一些模块可以可以给python使用，以训练模型



















