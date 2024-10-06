# StableDiffusion实战

B站的AI教父：[秋葉aaaki](https://space.bilibili.com/12566101)

-   [【AI绘画】完美控制画面！告别抽卡时代 人物动作控制/景深/线稿上色 Controlnet安装使用教程](https://www.bilibili.com/video/BV1Wo4y1i77v)

## 黑话杂项

余弦退火学习率倒是第一次听到

epoch



## 下载

这里有两个包，下载第一个

-   https://github.com/AUTOMATIC1111/stable-diffusion-webui
    第一个。提供了用户界面，而且更新比较频繁，commits数较多

-   https://github.com/CompVis/stable-diffusion
    第二个。这个也很多星，但是现在已经不维护了



秋叶大佬给了一个整合包，那个比较适合直接用。不仅有快速运行的.bat脚本，还附带有模型。
但我为了方便更新，也为了更熟悉这个库，直接从github里clone了，也就**30多MB**，clone速度很快



## 使用

github下面有安装和运行的方法（如果用秋叶大佬的整合包的话就不需要这么麻烦）



[title(Automatic Installation on Windows)]

1.  Install [Python 3.10.6](https://www.python.org/downloads/windows/), checking "Add Python to PATH"
2.  Install [git](https://git-scm.com/download/win).
3.  Download the stable-diffusion-webui repository, for example by running `git clone https://github.com/AUTOMATIC1111/stable-diffusion-webui.git`.
4.  Place stable diffusion checkpoint (`model.ckpt`) in the `models/Stable-diffusion` directory (see [dependencies](https://github.com/AUTOMATIC1111/stable-diffusion-webui/wiki/Dependencies) for where to get it).
    翻译：将稳定的扩散检查点 ( `model.ckpt`)放在`models/Stable-diffusion`目录中（请参阅[依赖项](https://github.com/AUTOMATIC1111/stable-diffusion-webui/wiki/Dependencies)了解从哪里获取它）。
5.  Run `webui-user.bat` from Windows Explorer as normal, non-administrator, user.
    翻译： `webui-user.bat`以普通非管理员用户身份从 Windows 资源管理器运行。


补充：

第四步：依赖会给你两个东西：

[title(Download the weights)]

-   [sd-v1-4.ckpt](https://huggingface.co/CompVis/stable-diffusion-v-1-4-original/resolve/main/sd-v1-4.ckpt)（4GB）
-   [sd-v1-4-full-ema.ckpt](https://huggingface.co/CompVis/stable-diffusion-v-1-4-original/resolve/main/sd-v1-4-full-ema.ckpt)（7.2GB）

第五步： 会下载一个PyTorch，这个是Python的一个机器学习工具和环境
Downloading https://download.pytorch.org/whl/cu117/torch-1.13.1%2Bcu117-cp37-cp37m-win_amd64.whl（2255.6MB）
然后还会下载一些杂七杂八的
估计要科学上网才能下？耗时10分钟到一天都有可能



## 秋叶大佬的启动器

https://pan.baidu.com/s/1XHOx7zgO0IQVL-01opwXjA?pwd=uvdy（10MB）



## Lora

civitai.com

明日方舟-德州奥默托萨：https://civitai.com/models/6779/arknights-texas-the-omertosa



## 底模（ckpt）

https://civitai.com/models/6424/chilloutmix（7.17GB）







## 扩展

Extensions下有三个选项：

-   Installed| 已安装
-   Available| 官方途径安装
-   Install from URL| 从url里安装

其实大部分都能通过选项二进行安装了



文件夹有两个

-   extensions| 后期安装的都在这
-   extensions-builtin| 内置的，有5个插件



### 中文

简体中文语言包：github stable-diffusion-webui-localization-zh_CN

安装后：Setting > User interface > Localization



### Controlnet

下载：

可以下秋叶的整合包，从官方途径 (或github) 下，还需要下载和放置模型，详见github文档
（话说完整模型还挺大的，每个模型都有5.71GB。）
下载完放在 `sd-webui-controlnet/models` 文件夹



启用，然后选参数：

-   none
-   canny| 描图
-   depth| 景深，适合生成相同布局的
-   hed| 上色/重上色
-   mlsd| 线段图（设计大体不变变材质，可以用来做家装）
-   normal_map| 法线图，比深度图更细节
-   openpose| 姿势
-   openpose_hand| 姿势
-   scribble| 手绘图（和上面相似）
-   fake_scribble
-   segmentation



-   ：canny预处理 + control_canny 模型
-   ：depth(midas) 预处理 + control_depth 模型
-   ：hed预处理 + control_hed 模型
-   MLSD：
-   Scribble：





## 踩坑

报错

运行webui-user.bat遇到的错误：

```
ERROR: Could not find a version that satisfies the requirement blendmodes==2022 (from -r requirements_versions.txt (line 1)) (from versions: 2020, 2020.1, 2020.2, 2020.2.1, 2020.2.2, 2020.3.0, 2021, 2021.1, 2021.2, 2021.3, 2021.3.1, 2021.3.2, 2021.3.3)
ERROR: No matching distribution found for blendmodes==2022 (from -r requirements_versions.txt (line 1))
WARNING: You are using pip version 19.2.3, however version 23.0 is available.
```

然后我把python从3.7换成了测试环境的3.10.9，然后发现他用的虚拟环境，然后我又把venv文件夹删了，重新运行webui-user.bat，让他用python3.10.9重新创建一个虚拟环境

比较尴尬的是他又重新要下载 torch 的 whl 了（2255.6MB），又要漫长的等待



## 参数 - 抄

nahida的

```
side ponytail, ((nahida \(genshin impact\))),<lora:nahidaGenshinImpact_nahidaGenshinImpact:1>, (((Kpop idol))),aegyo sal,multicolored hair,((hair between eyes)),white hair,green hair,green eyes,((pointy ears)),((flat chest)),(photorealistic:1.4),(masterpiece:1.4),(best quality:1.4),1girl, solo,ultra high res,((detailed facial features)),upper body, small hands,

paintings, sketches, (worst quality:2), (low quality:2), (normal quality:2), lowres, normal quality, ((monochrome)), ((grayscale)), skin spots, acnes, skin blemishes, age spot, (outdoor:1.6), manboobs, backlight,(ugly:1.331), (duplicate:1.331), (morbid:1.21), (mutilated:1.21), (tranny:1.331), mutated hands, (poorly drawn hands:1.331), blurry, (bad anatomy:1.21), (bad proportions:1.331), extra limbs, (disfigured:1.331), (more than 2 nipples:1.331), (missing arms:1.331), (extra legs:1.331), (fused fingers:1.61051), (too many fingers:1.61051), (unclear eyes:1.331), bad hands, missing fingers, extra digit, (futa:1.1), bad body, NG_DeepNegative_V1_75T,pubic hair, glans,(nipples:1.41),nsfw,

DPM++ 2M Karras
7 20
4160172761
```

chill的

```
<lora:koreanDollLikeness_v10:0.2>, (RAW photo, best quality, masterpiece:1.2), (realistic, photo-realistic:1.37), ultra-detailed, ultra high res, (aegyo sal:1), 1 girl, Kpop idol, busty, PureErosFace, (short hair:1.2), posing, (nose blush), (smile:1.1), (closed mouth), medium breasts, beautiful detailed eyes, floating hair, professional lighting, photon mapping, radiosity, physically-based rendering, silver dress, elf ears
Negative prompt: EasyNegative, paintings, sketches, (worst quality:2), (low quality:2), (normal quality:2), lowres, normal quality, ((monochrome)), ((grayscale)), skin spots, acnes, skin blemishes, age spot, glans,extra fingers,fewer fingers,((watermark:2)),((white letters:1))
Size: 512x768, Seed: 135854668, Steps: 22, Sampler: DPM++ 2M Karras, CFG scale: 8, Clip skip: 2, Model hash: 3a17d0deff, Hires steps: 20, Hires upscale: 1.75, Hires upscaler: Latent (bicubic antialiased), Denoising strength: 0.5
```



## 习惯经验 —— 分段魔法

**越往下，就越不固定，越能随便调整**

-   画面
-   内容
-   调整



```js
// 画面质量
,(masterpiece:1.4),(best quality:1.4),ultra high res,
// 人物质量
,((detailed facial features))
// 画风、真实度
,(photorealistic:0)

// 人物数量
a girl,
// 人物设定（lora）
,<lora:nahidaGenshinImpact_nahidaGenshinImpact:1>, ((nahida \(genshin impact\)))
// 人物五官、必要特征
, multicolored hair,side ponytail, white hair,green hair, green eyes, ((hair between eyes)), ((pointy ears))
// 人物的非必须特征
, medium breasts,((flat chest)), upper body, small hands


// 自己xp - 人物特征
,medium breast, ((white broken stocking, white gloves, naked))
// 自己xp - 人物环境
,((nsfw, rape, tear, humiliation, disgrace, torn clothes:1.6,big break:0.4, broken clothes:1.4, binding, rope binding)),
// 自己xp - 人物姿势

```

负面

```js
// 画面质量
(worst quality:2), (low quality:2), (normal quality:2), lowres, normal quality, ((monochrome)), ((grayscale)), blurry,
(ugly:1.331), (duplicate:1.331), (morbid:1.21),

// 人物质量
(mutilated:1.21), (tranny:1.331), mutated hands, (poorly drawn hands:1.331), (bad anatomy:1.21), (bad proportions:1.331), extra limbs, (disfigured:1.331), (more than 2 nipples:1.331), (missing arms:1.331), (extra legs:1.331), (fused fingers:1.61051), (too many fingers:1.61051), (unclear eyes:1.331), bad hands, missing fingers, extra digit, bad body,
// 画风
// 人物三次元磨皮（会使画面变灰）
,skin spots, acnes, skin blemishes, age spot, manboobs, backlight

// 不良xp
(futa:1.1), glans, manboobs

```

案例

```js
(masterpiece:1.4),(best quality:1.4),ultra high res
,((detailed facial features))

,a girl
,<lora:nahidaGenshinImpact_nahidaGenshinImpact:1>, ((nahida \(genshin impact\)))
, multicolored hair,side ponytail, white hair,green hair, green eyes, ((hair between eyes)), ((pointy ears))

,((nsfw, rape, tear, humiliation, disgrace, torn clothes:1.6,big break:0.4, broken clothes:1.4, binding, rope binding, medium breast)),
((white broken stocking, white gloves, naked))
Negative prompt: (worst quality:2), (low quality:2), (normal quality:2), lowres, normal quality, ((monochrome)), ((grayscale)), blurry,
(ugly:1.331), (duplicate:1.331), (morbid:1.21),

(mutilated:1.21), (tranny:1.331), mutated hands, (poorly drawn hands:1.331), (bad anatomy:1.21), (bad proportions:1.331), extra limbs, (disfigured:1.331), (more than 2 nipples:1.331), (missing arms:1.331), (extra legs:1.331), (fused fingers:1.61051), (too many fingers:1.61051), (unclear eyes:1.331), bad hands, missing fingers, extra digit, bad body,

(futa:1.1), glans, manboobs
Steps: 20, Sampler: DDIM, CFG scale: 7, Seed: 4241588520, Size: 512x820, Model hash: 37a86dca58, Model: grapefruitHentaiModel_grapefruitv4, Denoising strength: 0.5, Clip skip: 2, ENSD: 31337, Hires upscale: 1.75, Hires steps: 15, Hires upscaler: Latent
```

案例

```js
(masterpiece:1.4),(best quality:1.4),ultra high res
,((detailed facial features))
,(photorealistic:1)

,a girl
,<lora:nahidaGenshinImpact_nahidaGenshinImpact:1>, ((nahida \(genshin impact\)))
, multicolored hair,side ponytail, white hair,green hair, green eyes, ((hair between eyes))

,((medium breast)), ((white broken stocking)), white see-through blouses
,eight years old, youth, petite body, upper body,
,nsfw, naked, nude, vagina, stand,
forest pool,

Negative prompt: (worst quality:2), (low quality:2), (normal quality:2), lowres, normal quality, ((monochrome)), ((grayscale)), blurry,
(ugly:1.331), (duplicate:1.331), (morbid:1.21),

(mutilated:1.21), (tranny:1.331), mutated hands, (poorly drawn hands:1.331), (bad anatomy:1.21), (bad proportions:1.331), extra limbs, (disfigured:1.331), (more than 2 nipples:1.331), (missing arms:1.331), (extra legs:1.331), (fused fingers:1.61051), (too many fingers:1.61051), (unclear eyes:1.331), bad hands, missing fingers, extra digit, bad body,

(futa:1.1), glans, manboobs
Steps: 20, Sampler: DDIM, CFG scale: 7, Seed: 1539826123, Size: 512x880, Model hash: 3a17d0deff, Model: chilloutmix_NiCkpt, Denoising strength: 0.5, Clip skip: 2, ENSD: 31337, Hires upscale: 1.75, Hires steps: 15, Hires upscaler: Latent
```

露出位置

```js
naked, nude, vagina, rape:2,
```

很棒

```js
(masterpiece:1.4),(best quality:1.4),ultra high res
,((detailed facial features))
,(photorealistic:1)

,<lora:nahidaGenshinImpact_nahidaGenshinImpact:0.85>, ((nahida \(genshin impact\)))
,((multicolored hair,side ponytail, white hair,green hair, green eyes)), ((hair between eyes))

,((medium breast)), ((white broken stocking)), ((white see-through blouses)),
,nsfw,

photorealistic, (hyperrealistic:1.2), (extremely detailed CG unity 8k wallpaper), (ultra-detailed), (mature female:1.2),1girl,(1boy), boy from back, nsfw, (sex), (((corneo_side_doggy))), muscular man, masterpiece, best quality, breasts, shirt lift, halo, choker,
medium breasts, looking down,
collared shirt, detailed background, button gap,messy hair,bedroom, on bed,myhands,uncensored, navel, clothed female nude male,(perfect anatomy:1.4),wet skin,wet pussy,

Negative prompt: (worst quality:2), (low quality:2), (normal quality:2), lowres, normal quality, ((monochrome)), ((grayscale)), blurry,
(ugly:1.331), (duplicate:1.331), (morbid:1.21),

(mutilated:1.21), (tranny:1.331), mutated hands, (poorly drawn hands:1.331), (bad anatomy:1.21), (bad proportions:1.331), extra limbs, (disfigured:1.331), (more than 2 nipples:1.331), (missing arms:1.331), (extra legs:1.331), (fused fingers:1.61051), (too many fingers:1.61051), (unclear eyes:1.331), bad hands, missing fingers, extra digit, bad body,

(futa:1.1),
Steps: 20, Sampler: DDIM, CFG scale: 7, Seed: 2001310353, Size: 552x832, Model hash: 37a86dca58, Model: grapefruitHentaiModel_grapefruitv4, Denoising strength: 0.5, Clip skip: 2, ENSD: 31337, Hires upscale: 1.75, Hires steps: 15, Hires upscaler: Latent
```











