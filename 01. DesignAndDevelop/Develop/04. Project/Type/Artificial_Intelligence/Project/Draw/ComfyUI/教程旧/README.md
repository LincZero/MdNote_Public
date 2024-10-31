# README

在我开发NodeFlow之前的一些内容，后来使用NodeFlow语法替换之

## 按工作流

### 默认文生图工作流

[card|addClass(ab-col2)]

#### Load Checkpoint

中文：Checkpoint加载器(简易)
作用：加载扩散模型

- Checkpoint名称: 加载大模型
- (O) 模型
- (O) CLIP
- (O) VAE

#### CLIP Text Encode (Prompt)

中文：CLIP文本编码器 (提示词) (正面)
作用：CLIP (ContrastiveLanguageImagePretraining) 理解输入文字的意思

- (I) CLIO
- 文本
- (O) 条件

#### CLIP Text Encode (Prompt)

中文：CLIP文本编码器 (提示词) (负面)

- (I) CLIO
- 文本
- (O) 条件

#### Empty Latent Image

中文：空Laten
作用：潜空间，内部流程中的图像格式 (例如图生图时，先VAE编码转化为Laten数据，然后处理完再解码回图像)，可以用于设置图片大小

- 宽度
- 高度
- 批次大小

#### KSampler

中文：K采样器

[dir]

- (O) Latent
- (I) model   | 模型
- (I) positive| 正面条件
- (I) negative| 负面条件
- (I) Latent_image | 潜空间
- seed        | 种子
- control_after_generate | 运行后操作
  - fixed     | 固定
  - increment | 生成后自增
  - decrement | 生成后自减
  - randomize | 随机
- steps       | 步数
- CFG
- sampler_name| 采样器,采样方法
- scheduler   | 调度器
- denoise     | 降噪

#### VAE Decode

中文：VAE (变分自编码器) 解码器，用于将 Latent 格式转 Images 格式

- I samples
- I vae
- O Image

#### Save Image

中文：图片保存

- I images
- filename_prefix

### 简易图生图工作流

[card|addClass(ab-col2)]

#### Load Image

中文：加载图片

- O Image
- O Mask
- image，choose file to upload | 选择图片

#### VAE Encode

中文：VAE编码器

- I pixels
- I vae
- O Latent

#### Load VAE

中文：加载自定义的VAE (用于代替默认的)

- vae_name

#### Upscale Latent

中文：缩放 Latent
使用：图生图中，先VAE Encode，再走这里缩放，再给K采样

- I samples
- O Lantent
- upscale_method
- width
- height
- crop
  - disabled/abled

### Default

[card|addClass(ab-col2)]

#### Load LoRA

中文：加载LoRA
使用：可以根据IO类型判断出在哪个环节使用。这里是在 Checkpoint 后面加的

- I model
- I clio
- O model
- O clip
- lora_name
- strength_model
- strength_chip
