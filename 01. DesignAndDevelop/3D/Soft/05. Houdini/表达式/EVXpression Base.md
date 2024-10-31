---
last_time: 2020.05.14
tag: 有道云
---

# EVXpression Base

**Wrangle**

**Attribute Wrangle（Detail，Point，Primitive，Vertex，Numbers）**

**Deformation Wrangle**

**Volume Wrangle**

Alt+E编辑面板，能开写字板

## 1. 模块、导包

```
无     
```

## 2. 类型、变量

```js
【属性变量】Attribute Name，属性以@开头
@P 点位置          @P.x，@P.y，@P.z（每个SOP都有）
@pscale 点缩放     @xscale，@yscale，@zscale
点、面、元素序号    @ptnum，@primnum，@elemnum
粒子序号           @id 粒子序号
点、面、元素数量    @numpt，@numprim，@numelem
@Cd 颜色           @Cd.r，@Cd.g，@Cd.b            注：给Cd一个Rand很神奇，系统会自动Rand成Color而非Float
@v 方向、速度，比随机旋转好用
@N 法线
@uv uv属性
@numvtx 几边面（实质是面上VTX（Vertices）点的数量）$NVTX 亦可
@width 线的渲染宽度

【系统变量？】
$OS 用节点名字作为变量
时间相关：
$FF，时间 - 帧
$T，时间 - 秒
$RFSTART，第一帧
$RFEND，最后一帧
$SF，开始解算的第一帧

【滑竿变量】
ch('参数1')  // 自定义一个滑竿调参

【临时变量】
int i += id，number
float f = rand(seed)
vector v = set(,,)，{,,}
string s = "" ''

【属性变量】和临时变量相比，好处是可在detail中看到变量，但占用多
i@i = id/number
f@f = pscale/width
v@v = P/Cd/N/v
s@s = class/name/material/path
```

## 3. 类

```
无              
```

## 4. 语法

```js
【逻辑符号】
>,<,==
&&,||,
*通配符，^通配后排除

【语法】
if () {} else {}
()?x:y

【取值】—— 取属性变量
属性位置('节点地址，通常是:../节点名/','属性',0)  // 取值
point('节点地址，通常是:../节点名/','属性',0)  // 取点属性
detail('../foreach_count1/','iteration',0)  // 如果去当前物体的detail
sample("../copy1/","定义的属性名",0)  // 从copytosample取值

【地址相关】
这里的节点地址：
通常是'../节点名/'  // ../表示当前层级的地址，而非上一层
有多个输入源时，第'n'个输入源的地址为'n-1'
也可添加“Add Spare Input”，用来存储节点地址，引用时地址为'-1'
```

## 5. 函数

```
无
```

## 6. 特色

```
无   
```

## 7. 常用方法

```js
自带函数：
【数学类】
floor()  // 向下取整
fit，fit01，fit10，fit11  // 映射

relbbox(@P)  // 求相对距离，把绝对距离变为0-1
getbbox_max(0)  // 求绝对绝对坐标的最大值，返回vector
getbbox_max(0)  // 求绝对绝对坐标的最小值，返回vector
```

## 一些实例

```js
@uv = relbbox(@P);  // 根据P属性创建uv属性，对应Relative to Bounding Box节点
@Cd = texture('default.pic',@uv[0],-@uv[2]);  // 根据uv给贴图，对应texture节点
```



```js
int i = 1;
@P.y += i; 或 @P += set(0, i, 0);
```

取属性值

```js
【实战】
选择类：
rand(@elemnum) < 0.3  // 选择随机
@P.x < 0  // 选择指定区域
length(@P) < 0.7  // 选择球形区域
@numvtx == 4  // 四边面
操作：
@P.y += rand(@ptnum)  // 变换
@group_name1 = @P.y>0.3  // 打组
```

## 脚印实例

```js
float sdf = volumesample(1,0,@P);
if (sdf<0) @P -= set(0,-1*sdf*ch('scale'),0);
```

## 迷宫映射实例

```js
@P = point(1,'P',@origpt);
```

