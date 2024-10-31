# Svg

## 简单入门Svg

元素就那几个：画圆/矩形(circle/polygon)、画文字(title)、画线(path)。然后有时要一个容器(g)，就没了

然后大概了解下定位、宽高、填充等，和css有些类似的属性（不太用记，需要再查）

来个简单 svg demo：

<svg width="100" height="100">
  <g transform="translate(50,50)">
    <circle cx="0" cy="0" r="30" fill="blue" stroke="red"/>
    <text x="0" y="0" text-anchor="middle" dy=".3em" fill="white">Hello</text>
  </g>
</svg>

## 修改Svg

svg的从零开始绘制不一定要会，因为大多数情况下我们并不会自己画，更多地是从网上下载。

然后有时我们从网站下载时，他会让你选择颜色、透明度、尺寸等，比较友好。但有时我们会发现……svg直接就下载下来，我的编辑过程呢？

这时候就需要自己修改一下了

也比较简单，主要涉及：尺寸的定位、颜色的修改

常用标签：

- fill，颜色填充，类似css的 background-color
- stroke，描边，类似css的 border