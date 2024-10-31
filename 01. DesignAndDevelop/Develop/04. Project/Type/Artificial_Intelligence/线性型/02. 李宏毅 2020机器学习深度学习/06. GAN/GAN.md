# 李宏毅机器学习深度学习

# 目录

# GAN（Generative Adversarial Networks，生成对抗网络）

对应视频：P58 ~ P61

对应pdf：`14_GAN_P1.pdf` ~ `17_GAN_P4.pdf`

## 生成网络（Network as Generator）

generator定义：

> 把network当做一个generator来用,，他特别的地方是现在network的输入，会加上一个random的 variable
> x->y的基础上加上一个Z
> 它不是只看一个固定的X得到输出，它是同时看X跟Z得到输出
> network输出，不再是单一一个固定的东西，而变成了一个复杂的distribution
>
> 那这种可以输出一个**distribution**（**分布**）的network，我们就叫它**generator**



Why distribution



应用举例

- 绘画
- 机器人



GAN的类型



## 鉴别器（Discriminator）



对抗（Adversarial）





内插（interpolation），做过度，做数据增强，做生成陌生人，做AI换脸







## “损失函数”

divergence 差异，越小越好
$$
G^*=\arg \min_G Div(P_G, P_{data})
$$



# P59，有点看不懂了





























