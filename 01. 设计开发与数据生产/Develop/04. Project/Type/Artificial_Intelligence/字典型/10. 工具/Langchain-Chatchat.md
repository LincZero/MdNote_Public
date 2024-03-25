# Langchain-Chatchat

# 目录

项目文档目录

- FAQ.md
- [Install.md](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/docs/INSTALL.md)
- [在Anaconda中使用pip安装包的问题.md](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/docs/Issue-with-Installing-Packages-Using-pip-in-Anaconda.md)
- 向量库环境 docker.md
- 启动API服务.md
- [在Anaconda中使用pip安装包无效问题.md](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/docs/%E5%9C%A8Anaconda%E4%B8%AD%E4%BD%BF%E7%94%A8pip%E5%AE%89%E8%A3%85%E5%8C%85%E6%97%A0%E6%95%88%E9%97%AE%E9%A2%98.md)

# 项目README

参考：https://github.com/chatchat-space/Langchain-Chatchat

README 目录

- [介绍](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#介绍)
- [变更日志](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#变更日志)
- [模型支持](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#模型支持)
- [Docker 部署](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#Docker-部署)
- 开发部署
  - [软件需求](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#软件需求)
  - [1. 开发环境准备](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#1.-开发环境准备)
  - [2. 下载模型至本地](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#2.-下载模型至本地)
  - [3. 设置配置项](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#3.-设置配置项)
  - [4. 知识库初始化与迁移](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#4.-知识库初始化与迁移)
  - [5. 一键启动API服务或WebUI服务](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#6.-一键启动)
  - [6. 分步启动 API 服务或 Web UI](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#5.-启动-API-服务或-Web-UI)
- [常见问题](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#常见问题)
- [路线图](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#路线图)
- [项目交流群](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#项目交流群)

## 介绍

🤖️ 一种利用 [langchain](https://github.com/hwchase17/langchain) 思想实现的基于本地知识库的问答应用，目标期望建立一套对中文场景与开源模型支持友好、可离线运行的知识库问答解决方案。

💡 受 [GanymedeNil](https://github.com/GanymedeNil) 的项目 [document.ai](https://github.com/GanymedeNil/document.ai) 和 [AlexZhangji](https://github.com/AlexZhangji) 创建的 [ChatGLM-6B Pull Request](https://github.com/THUDM/ChatGLM-6B/pull/216) 启发，建立了全流程可使用开源模型实现的本地知识库问答应用。本项目的最新版本中通过使用 [FastChat](https://github.com/lm-sys/FastChat) 接入 Vicuna, Alpaca, LLaMA, Koala, RWKV 等模型，依托于 [langchain](https://github.com/langchain-ai/langchain) 框架支持通过基于 [FastAPI](https://github.com/tiangolo/fastapi) 提供的 API 调用服务，或使用基于 [Streamlit](https://github.com/streamlit/streamlit) 的 WebUI 进行操作。

✅ 依托于本项目支持的开源 **LLM** 与 **Embedding** 模型，本项目可实现全部使用**开源**模型**离线私有部署**。与此同时，本项目也支持 OpenAI GPT API 的调用，并将在后续持续扩充对各类模型及模型 API 的接入。
（术语：LLM 是大型语言模型，Embedding 是向量库映射）

⛓️ 本项目实现原理如下图所示，过程包括加载文件 -> 读取文本 -> 文本分割 -> 文本向量化 -> 问句向量化 -> 在文本向量中匹配出与问句向量最相似的 `top k`个 -> 匹配出的文本作为上下文和问题一起添加到 `prompt`中 -> 提交给 `LLM`生成回答。

📺 [原理介绍视频](https://www.bilibili.com/video/BV13M4y1e7cN/?share_source=copy_web&vd_source=e6c5aafe684f30fbe41925d61ca6d514)

![image-20230906094634937](Langchain-Chatchat.assets/image-20230906094634937.png)

从文档处理角度来看，实现流程如下：

![image-20230906094624349](Langchain-Chatchat.assets/image-20230906094624349.png)

🚩 本项目未涉及微调、训练过程，但可利用微调或训练对本项目效果进行优化。

🌐 [AutoDL 镜像](https://www.codewithgpu.com/i/imClumsyPanda/langchain-ChatGLM/Langchain-Chatchat) 中 `v7` 版本所使用代码已更新至本项目 `v0.2.3` 版本。

🐳 [Docker 镜像](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/registry.cn-beijing.aliyuncs.com/chatchat/chatchat:0.2.0)

💻 一行命令运行 Docker：

```shell
docker run -d --gpus all -p 80:8501 registry.cn-beijing.aliyuncs.com/chatchat/chatchat:0.2.0
```

### 模型支持

本项目中默认使用的 LLM 模型为 [THUDM/chatglm2-6b](https://huggingface.co/THUDM/chatglm2-6b)，默认使用的 Embedding 模型为 [moka-ai/m3e-base](https://huggingface.co/moka-ai/m3e-base) 为例。

#### LLM 模型支持

本项目最新版本中基于 [FastChat](https://github.com/lm-sys/FastChat) 进行本地 LLM 模型接入，支持模型如下：

- [meta-llama/Llama-2-7b-chat-hf](https://huggingface.co/meta-llama/Llama-2-7b-chat-hf)
- Vicuna, Alpaca, LLaMA, Koala
- [BlinkDL/RWKV-4-Raven](https://huggingface.co/BlinkDL/rwkv-4-raven)
- [camel-ai/CAMEL-13B-Combined-Data](https://huggingface.co/camel-ai/CAMEL-13B-Combined-Data)
- [databricks/dolly-v2-12b](https://huggingface.co/databricks/dolly-v2-12b)
- [FreedomIntelligence/phoenix-inst-chat-7b](https://huggingface.co/FreedomIntelligence/phoenix-inst-chat-7b)
- [h2oai/h2ogpt-gm-oasst1-en-2048-open-llama-7b](https://huggingface.co/h2oai/h2ogpt-gm-oasst1-en-2048-open-llama-7b)
- [lcw99/polyglot-ko-12.8b-chang-instruct-chat](https://huggingface.co/lcw99/polyglot-ko-12.8b-chang-instruct-chat)
- [lmsys/fastchat-t5-3b-v1.0](https://huggingface.co/lmsys/fastchat-t5)
- [mosaicml/mpt-7b-chat](https://huggingface.co/mosaicml/mpt-7b-chat)
- [Neutralzz/BiLLa-7B-SFT](https://huggingface.co/Neutralzz/BiLLa-7B-SFT)
- [nomic-ai/gpt4all-13b-snoozy](https://huggingface.co/nomic-ai/gpt4all-13b-snoozy)
- [NousResearch/Nous-Hermes-13b](https://huggingface.co/NousResearch/Nous-Hermes-13b)
- [openaccess-ai-collective/manticore-13b-chat-pyg](https://huggingface.co/openaccess-ai-collective/manticore-13b-chat-pyg)
- [OpenAssistant/oasst-sft-4-pythia-12b-epoch-3.5](https://huggingface.co/OpenAssistant/oasst-sft-4-pythia-12b-epoch-3.5)
- [project-baize/baize-v2-7b](https://huggingface.co/project-baize/baize-v2-7b)
- [Salesforce/codet5p-6b](https://huggingface.co/Salesforce/codet5p-6b)
- [StabilityAI/stablelm-tuned-alpha-7b](https://huggingface.co/stabilityai/stablelm-tuned-alpha-7b)
- [THUDM/chatglm-6b](https://huggingface.co/THUDM/chatglm-6b)
- [THUDM/chatglm2-6b](https://huggingface.co/THUDM/chatglm2-6b)
- [tiiuae/falcon-40b](https://huggingface.co/tiiuae/falcon-40b)
- [timdettmers/guanaco-33b-merged](https://huggingface.co/timdettmers/guanaco-33b-merged)
- [togethercomputer/RedPajama-INCITE-7B-Chat](https://huggingface.co/togethercomputer/RedPajama-INCITE-7B-Chat)
- [WizardLM/WizardLM-13B-V1.0](https://huggingface.co/WizardLM/WizardLM-13B-V1.0)
- [WizardLM/WizardCoder-15B-V1.0](https://huggingface.co/WizardLM/WizardCoder-15B-V1.0)
- [baichuan-inc/baichuan-7B](https://huggingface.co/baichuan-inc/baichuan-7B)
- [internlm/internlm-chat-7b](https://huggingface.co/internlm/internlm-chat-7b)
- [Qwen/Qwen-7B-Chat](https://huggingface.co/Qwen/Qwen-7B-Chat)
- [HuggingFaceH4/starchat-beta](https://huggingface.co/HuggingFaceH4/starchat-beta)
- 任何 [EleutherAI](https://huggingface.co/EleutherAI) 的 pythia 模型，如 [pythia-6.9b](https://huggingface.co/EleutherAI/pythia-6.9b)
- 在以上模型基础上训练的任何 [Peft](https://github.com/huggingface/peft) 适配器。为了激活，模型路径中必须有 `peft` 。注意：如果加载多个peft模型，你可以通过在任何模型工作器中设置环境变量 `PEFT_SHARE_BASE_WEIGHTS=true` 来使它们共享基础模型的权重。

以上模型支持列表可能随 [FastChat](https://github.com/lm-sys/FastChat) 更新而持续更新，可参考 [FastChat 已支持模型列表](https://github.com/lm-sys/FastChat/blob/main/docs/model_support.md)。

除本地模型外，本项目也支持直接接入 OpenAI API，具体设置可参考 `configs/model_configs.py.example` 中的 `llm_model_dict` 的 `openai-chatgpt-3.5` 配置信息。

#### Embedding 模型支持

本项目支持调用 [HuggingFace](https://huggingface.co/models?pipeline_tag=sentence-similarity) 中的 Embedding 模型，已支持的 Embedding 模型如下：

- [moka-ai/m3e-small](https://huggingface.co/moka-ai/m3e-small)
- [moka-ai/m3e-base](https://huggingface.co/moka-ai/m3e-base)
- [moka-ai/m3e-large](https://huggingface.co/moka-ai/m3e-large)
- [BAAI/bge-small-zh](https://huggingface.co/BAAI/bge-small-zh)
- [BAAI/bge-base-zh](https://huggingface.co/BAAI/bge-base-zh)
- [BAAI/bge-large-zh](https://huggingface.co/BAAI/bge-large-zh)
- [BAAI/bge-large-zh-noinstruct](https://huggingface.co/BAAI/bge-large-zh-noinstruct)
- [shibing624/text2vec-base-chinese-sentence](https://huggingface.co/shibing624/text2vec-base-chinese-sentence)
- [shibing624/text2vec-base-chinese-paraphrase](https://huggingface.co/shibing624/text2vec-base-chinese-paraphrase)
- [shibing624/text2vec-base-multilingual](https://huggingface.co/shibing624/text2vec-base-multilingual)
- [shibing624/text2vec-base-chinese](https://huggingface.co/shibing624/text2vec-base-chinese)
- [shibing624/text2vec-bge-large-chinese](https://huggingface.co/shibing624/text2vec-bge-large-chinese)
- [GanymedeNil/text2vec-large-chinese](https://huggingface.co/GanymedeNil/text2vec-large-chinese)
- [nghuyong/ernie-3.0-nano-zh](https://huggingface.co/nghuyong/ernie-3.0-nano-zh)
- [nghuyong/ernie-3.0-base-zh](https://huggingface.co/nghuyong/ernie-3.0-base-zh)
- [OpenAI/text-embedding-ada-002](https://platform.openai.com/docs/guides/embeddings)

## Docker 部署

🐳 Docker 镜像地址: `registry.cn-beijing.aliyuncs.com/chatchat/chatchat:0.2.0)`

```bash
docker run -d --gpus all -p 80:8501 registry.cn-beijing.aliyuncs.com/chatchat/chatchat:0.2.0
```

- 该版本镜像大小 `33.9GB`，使用 `v0.2.0`，以 `nvidia/cuda:12.1.1-cudnn8-devel-ubuntu22.04` 为基础镜像
- 该版本内置一个 `embedding` 模型：`m3e-large`，内置 `chatglm2-6b-32k`
- 该版本目标为方便一键部署使用，请确保您已经在Linux发行版上安装了NVIDIA驱动程序
- 请注意，您不需要在主机系统上安装CUDA工具包，但需要安装 `NVIDIA Driver` 以及 `NVIDIA Container Toolkit`，请参考[安装指南](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html)
- 首次拉取和启动均需要一定时间，首次启动时请参照下图使用 `docker logs -f <container id>` 查看日志
- 如遇到启动过程卡在 `Waiting..` 步骤，建议使用 `docker exec -it <container id> bash` 进入 `/logs/` 目录查看对应阶段日志

## 开发部署

### 环境准备

开发环境准备

本项目已在 Python 3.8.1 - 3.10，CUDA 11.7 环境下完成测试。已在 Windows、ARM 架构的 macOS、Linux 系统中完成测试。

参见 [开发环境准备](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/docs/INSTALL.md)。

**请注意：** `0.2.0` 及更新版本的依赖包与 `0.1.x` 版本依赖包可能发生冲突，强烈建议新建环境后重新安装依赖包。

#### 环境检查

```bash
# 首先，确信你的机器安装了 Python 3.8 - 3.10 版本
$ python --version
Python 3.8.13

# 如果低于这个版本，可使用conda安装环境
$ conda create -p /your_path/env_name python=3.8

# 激活环境
$ source activate /your_path/env_name

# 或，conda安装，不指定路径, 注意以下，都将/your_path/env_name替换为env_name
$ conda create -n env_name python=3.8
$ conda activate env_name # Activate the environment

# 更新py库
$ pip3 install --upgrade pip

# 关闭环境
$ source deactivate /your_path/env_name

# 删除环境
$ conda env remove -p  /your_path/env_name
```

#### 项目依赖

```bash
# 拉取仓库
$ git clone https://github.com/chatchat-space/Langchain-Chatchat.git

# 进入目录
$ cd Langchain-Chatchat

# 安装依赖 (三选一，为方便用户 API 与 webui 分离运行，可单独根据运行需求安装依赖包)
$ pip install -r requirements.txt # 安装全部依赖
# $ pip install -r requirements_api.txt # 如果只需运行 API
# $ pip install -r requirements_webui.txt # 如果只需运行 WebUI

# 默认依赖包括基本运行环境（FAISS向量库）。如果要使用 milvus/pg_vector 等向量库，请将 requirements.txt 中相应依赖取消注释再安装。
```

注：使用 `langchain.document_loaders.UnstructuredFileLoader` 进行 `.docx` 等格式非结构化文件接入时，可能需要依据文档进行其他依赖包的安装，请参考 [langchain 文档](https://python.langchain.com/en/latest/modules/indexes/document_loaders/examples/unstructured_file.html)。

### 模型下载 (LLM & Embedding)

下载模型至本地

如需在本地或离线环境下运行本项目，需要首先将项目所需的模型下载至本地，通常开源 LLM 与 Embedding 模型可以从 [HuggingFace](https://huggingface.co/models) 下载。

以本项目中默认使用的 LLM 模型 [THUDM/chatglm2-6b](https://huggingface.co/THUDM/chatglm2-6b) 与 Embedding 模型 [moka-ai/m3e-base](https://huggingface.co/moka-ai/m3e-base) 为例：

下载模型需要先[安装Git LFS](https://docs.github.com/zh/repositories/working-with-files/managing-large-files/installing-git-large-file-storage)，然后运行

```bash
$ git clone https://huggingface.co/THUDM/chatglm2-6b
$ git clone https://huggingface.co/moka-ai/m3e-base
```

### 配置选项

设置配置项

复制模型相关参数配置模板文件 [configs/model_config.py.example](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/configs/model_config.py.example) 存储至项目路径下 `./configs` 路径下，并重命名为 `model_config.py`。

复制服务相关参数配置模板文件 [configs/server_config.py.example](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/configs/server_config.py.example) 存储至项目路径下 `./configs` 路径下，并重命名为 `server_config.py`。

在开始执行 Web UI 或命令行交互前，请先检查 `configs/model_config.py` 和 `configs/server_config.py` 中的各项模型参数设计是否符合需求：

- 请确认已下载至本地的 LLM 模型本地存储路径写在 `llm_model_dict` 对应模型的 `local_model_path` 属性中，如:

  ```python
  llm_model_dict={
      "chatglm2-6b": {
          "local_model_path": "/Users/xxx/Downloads/chatglm2-6b",
          "api_base_url": "http://localhost:8888/v1",  # "name"修改为 FastChat 服务中的"api_base_url"
          "api_key": "EMPTY"
      },
  }
  ```

- 请确认已下载至本地的 Embedding 模型本地存储路径写在 `embedding_model_dict` 对应模型位置，如：

  ```python
  embedding_model_dict = {
      "m3e-base": "/Users/xxx/Downloads/m3e-base",
  }
  ```

如果你选择使用OpenAI的Embedding模型，请将模型的 `key`写入 `embedding_model_dict`中。使用该模型，你需要能够访问OpenAI官的API，或设置代理。

### 知识库初始化与迁移

当前项目的知识库信息存储在数据库中，在正式运行项目之前请先初始化数据库（我们强烈建议您在执行操作前备份您的知识文件）。

- 如果您是从 `0.1.x` 版本升级过来的用户，针对已建立的知识库，请确认知识库的向量库类型、Embedding 模型与 `configs/model_config.py` 中默认设置一致，如无变化只需以下命令将现有知识库信息添加到数据库即可：

  ```bash
  $ python init_database.py
  ```

- 如果您是第一次运行本项目，知识库尚未建立，或者配置文件中的知识库类型、嵌入模型发生变化，或者之前的向量库没有开启 `normalize_L2`，需要以下命令初始化或重建知识库：

  ```bash
  $ python init_database.py --recreate-vs
  ```

### 一键启动API 服务或 Web UI

#### 启动命令

一键启动脚本 startup.py,一键启动所有 Fastchat 服务、API 服务、WebUI 服务，示例代码：

```
$ python startup.py -a
```

并可使用 `Ctrl + C` 直接关闭所有运行服务。如果一次结束不了，可以多按几次。

可选参数包括 `-a (或--all-webui)`, `--all-api`, `--llm-api`, `-c (或--controller)`, `--openai-api`, `-m (或--model-worker)`, `--api`, `--webui`，其中：

- `--all-webui` 为一键启动 WebUI 所有依赖服务；
- `--all-api` 为一键启动 API 所有依赖服务；
- `--llm-api` 为一键启动 Fastchat 所有依赖的 LLM 服务；
- `--openai-api` 为仅启动 FastChat 的 controller 和 openai-api-server 服务；
- 其他为单独服务启动选项。

#### 启动非默认模型

若想指定非默认模型，需要用 `--model-name` 选项，示例：

```
$ python startup.py --all-webui --model-name Qwen-7B-Chat
```

更多信息可通过 `python startup.py -h`查看。

#### 多卡加载

项目支持多卡加载，需在 startup.py 中的 create_model_worker_app 函数中，修改如下三个参数:

```
gpus=None, 
num_gpus=1, 
max_gpu_memory="20GiB"
```

其中，`gpus` 控制使用的显卡的ID，例如 "0,1";

`num_gpus` 控制使用的卡数;

`max_gpu_memory` 控制每个卡使用的显存容量。

注1：server_config.py的FSCHAT_MODEL_WORKERS字典中也增加了相关配置，如有需要也可通过修改FSCHAT_MODEL_WORKERS字典中对应参数实现多卡加载。

注2：少数情况下，gpus参数会不生效，此时需要通过设置环境变量CUDA_VISIBLE_DEVICES来指定torch可见的gpu,示例代码：

```
CUDA_VISIBLE_DEVICES=0,1 python startup.py 
```

#### PEFT 加载(包括lora,p-tuning,prefix tuning, prompt tuning,ia3等)

本项目基于 FastChat 加载 LLM 服务，故需以 FastChat 加载 PEFT  路径，即保证路径名称里必须有 peft 这个词，配置文件的名字为 adapter_config.json，peft 路径下包含.bin 格式的  PEFT  权重，peft路径在startup.py中create_model_worker_app函数的args.model_names中指定，并开启环境变量PEFT_SHARE_BASE_WEIGHTS=true参数。

注：如果上述方式启动失败，则需要以标准的fastchat服务启动方式分步启动，分步启动步骤参考第六节，PEFT加载详细步骤参考[加载lora微调后模型失效](https://github.com/chatchat-space/Langchain-Chatchat/issues/1130#issuecomment-1685291822)，

#### **注意事项**

**1. startup 脚本用多进程方式启动各模块的服务，可能会导致打印顺序问题，请等待全部服务发起后再调用，并根据默认或指定端口调用服务（默认 LLM API 服务端口：`127.0.0.1:8888`,默认 API 服务端口：`127.0.0.1:7861`,默认 WebUI 服务端口：`本机IP：8501`)**

**2.服务启动时间示设备不同而不同，约 3-10 分钟，如长时间没有启动请前往 `./logs`目录下监控日志，定位问题。**

**3. 在Linux上使用ctrl+C退出可能会由于linux的多进程机制导致multiprocessing遗留孤儿进程，可通过shutdown_all.sh进行退出**

#### 启动界面示例

1. FastAPI docs 界面

![image-20230906095433786](Langchain-Chatchat.assets/image-20230906095433786.png)

2. webui启动界面示例：

- Web UI 对话界面： [![img](https://github.com/chatchat-space/Langchain-Chatchat/raw/master/img/webui_0813_0.png)](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/img/webui_0813_0.png)
- Web UI 知识库管理页面： [![img](Langchain-Chatchat.assets/webui_0813_1.png)](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/img/webui_0813_1.png)

### 分步启动 API 服务或 Web UI（一键启动忽略本节）

注意：如使用了一键启动方式，可忽略本节。

#### 启动 LLM 服务 (三种方式)

如需使用开源模型进行本地部署，需首先启动 LLM 服务，启动方式分为三种：

- [基于多进程脚本 llm_api.py 启动 LLM 服务](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#5.1.1-基于多进程脚本-llm_api.py-启动-LLM-服务)
- [基于命令行脚本 llm_api_stale.py 启动 LLM 服务](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#5.1.2-基于命令行脚本-llm_api_stale.py-启动-LLM-服务)
- [PEFT 加载](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#5.1.3-PEFT-加载)

三种方式只需选择一个即可，具体操作方式详见 5.1.1 - 5.1.3。

如果启动在线的API服务（如 OPENAI 的 API 接口），则无需启动 LLM 服务，即 5.1 小节的任何命令均无需启动。

##### 基于多进程脚本 llm_api.py 启动 LLM 服务

在项目根目录下，执行 [server/llm_api.py](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/server/llm_api.py) 脚本启动 **LLM 模型**服务：

```
$ python server/llm_api.py
```

项目支持多卡加载，需在 llm_api.py 中的 create_model_worker_app 函数中，修改如下三个参数:

```
gpus=None, 
num_gpus=1, 
max_gpu_memory="20GiB"
```

其中，`gpus` 控制使用的显卡的ID，如果 "0,1";

`num_gpus` 控制使用的卡数;

`max_gpu_memory` 控制每个卡使用的显存容量。

##### 基于命令行脚本 llm_api_stale.py 启动 LLM 服务

⚠️ **注意:**

**1.llm_api_stale.py脚本原生仅适用于linux。mac设备需要安装对应的linux命令，win平台请使用wsl;**

**2.加载非默认模型需要用命令行参数--model-path-address指定模型，不会读取model_config.py配置;**

在项目根目录下，执行 [server/llm_api_stale.py](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/server/llm_api_stale.py) 脚本启动 **LLM 模型**服务：

```bash
$ python server/llm_api_stale.py
```

该方式支持启动多个worker，示例启动方式：

```bash
$ python server/llm_api_stale.py --model-path-address model1@host1@port1 model2@host2@port2
```

如果出现server端口占用情况，需手动指定server端口,并同步修改model_config.py下对应模型的base_api_url为指定端口:

```bash
$ python server/llm_api_stale.py --server-port 8887
```

如果要启动多卡加载，示例命令如下：

```bash
$ python server/llm_api_stale.py --gpus 0,1 --num-gpus 2 --max-gpu-memory 10GiB
```

注：以如上方式启动LLM服务会以nohup命令在后台运行 FastChat 服务，如需停止服务，可以运行如下命令：

```bash
$ python server/llm_api_shutdown.py --serve all 
```

亦可单独停止一个 FastChat 服务模块，可选 [`all`, `controller`, `model_worker`, `openai_api_server`]

##### PEFT 加载(包括lora,p-tuning,prefix tuning, prompt tuning,ia3等)

本项目基于 FastChat 加载 LLM 服务，故需以 FastChat 加载 PEFT  路径，即保证路径名称里必须有 peft 这个词，配置文件的名字为 adapter_config.json，peft 路径下包含  model.bin 格式的 PEFT 权重。 详细步骤参考[加载lora微调后模型失效](https://github.com/chatchat-space/Langchain-Chatchat/issues/1130#issuecomment-1685291822)

![image-20230906100313064](Langchain-Chatchat.assets/image-20230906100313064.png)

#### 启动 API 服务

本地部署情况下，按照 [5.1 节](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#5.1-启动-LLM-服务)**启动 LLM 服务后**，再执行 [server/api.py](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/server/api.py) 脚本启动 **API** 服务；

在线调用API服务的情况下，直接执执行 [server/api.py](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/server/api.py) 脚本启动 **API** 服务；

调用命令示例：

```bash
$ python server/api.py
```

启动 API 服务后，可访问 `localhost:7861` 或 `{API 所在服务器 IP}:7861` FastAPI 自动生成的 docs 进行接口查看与测试。

- FastAPI docs 界面
  ![image-20230906100403529](Langchain-Chatchat.assets/image-20230906100403529.png)

#### 启动 Web UI 服务

按照 [5.2 节](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/README.md#5.2-启动-API-服务)**启动 API 服务后**，执行 [webui.py](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/webui.py) 启动 **Web UI** 服务（默认使用端口 `8501`）

```bash
$ streamlit run webui.py
```

使用 Langchain-Chatchat 主题色启动 **Web UI** 服务（默认使用端口 `8501`）

```bash
$ streamlit run webui.py --theme.base "light" --theme.primaryColor "#165dff" --theme.secondaryBackgroundColor "#f5f5f5" --theme.textColor "#000000"
```

或使用以下命令指定启动 **Web UI** 服务并指定端口号

```bash
$ streamlit run webui.py --server.port 666
```

- Web UI 对话界面：

  [![img](https://github.com/chatchat-space/Langchain-Chatchat/raw/master/img/webui_0813_0.png)](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/img/webui_0813_0.png)

- Web UI 知识库管理页面：

  [![img](https://github.com/chatchat-space/Langchain-Chatchat/raw/master/img/webui_0813_1.png)](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/img/webui_0813_1.png)

## 常见问题

参见 [常见问题](https://github.com/chatchat-space/Langchain-Chatchat/blob/master/docs/FAQ.md)。

## 路线图

-  Langchain 应用
  -  本地数据接入
    -  接入非结构化文档
      -  .md
      -  .txt
      -  .docx
    -  结构化数据接入
      -  .csv
      -  .xlsx
    -  分词及召回
      -  接入不同类型 TextSplitter
      -  优化依据中文标点符号设计的 ChineseTextSplitter
      -  重新实现上下文拼接召回
    -  本地网页接入
    -  SQL 接入
    -  知识图谱/图数据库接入
  -  搜索引擎接入
    -  Bing 搜索
    -  DuckDuckGo 搜索
  -  Agent 实现
-  LLM 模型接入
  -  支持通过调用 [FastChat](https://github.com/lm-sys/fastchat) api 调用 llm
  -  支持 ChatGLM API 等 LLM API 的接入
-  Embedding 模型接入
  -  支持调用 HuggingFace 中各开源 Emebdding 模型
  -  支持 OpenAI Embedding API 等 Embedding API 的接入
-  基于 FastAPI 的 API 方式调用
-  Web UI
  -  基于 Streamlit 的 Web UI

## 项目交流群

<img src="./Langchain-Chatchat.assets/image-20230906101805804.png" alt="image-20230906101805804" style="zoom:25%;" />

# 个人环境备注

## LLM模型替换问题

### 换用更大参数量的模型

他这里默认是6b，可以给7G的显卡用。但公司电脑是24G显存的3090Ti，可以换用更强的本地模型。
这里大概算一下，b就是billion 十亿。 $7G=7*10^{3*3}=7B$，由于其他损耗就大概是7G显卡的样子。
但这也不一定，像 https://zhuanlan.zhihu.com/p/618690572 这里说这个130B缩放特性可以量化到100B级别，然后可以由 4x24G 来运行

参考：

- GPT-3 175B
- OPT-175B
- BLOOM-176B

### 同参数量的模型、量化or高参数量

另外，参数量相同的模型也会有差异。如新的优化方案导致性能不同，或者训练集不同，调参差异，导致的侧重点不同。以及双语的支持等，都是要考虑的重点。

参考：[中文羊驼大模型Alpaca-Plus-13B、Alpaca-33B效果大比拼](https://blog.csdn.net/nlpstarter/article/details/131129240)

模型比较

- Alpaca-Plus-13B：120G预训练，400万指令精调。
  - 特点：高训练数据，Q8量化
- Alpaca-33B：20G预训练，400万指令精调
  - 特点：模型量级大，Q4量化

测试

- 温室效应问题：33B的回答比较简练，内容长度上不占优
- 数学问题：骑7个猴。**33B的完胜**Plus-13B，可能模型量级对于这种数值计算和推理类的有较大优势吧
- 如何制作宫保鸡丁？：差不多
- 写一封信：Plus-13B占优一些，内容详实。可能33B吃了训练数据少的亏，写的内容不是特别生动
- 代码方面：**33B显著胜出**
- 角色扮演：差不多，13回复长，略优

总结

> Plus-13B相比之前的7B/13B已经有显著性能提升了，尤其是在生成类的任务上内容更加详实。33B的优缺点比较明显，优点是代码能力和数值计算方面确实比之前高出一截，但是在文本生成类的任务上效果略低于plus-13B。不过33B是基础版，这么比可能有点不讲武德，哈哈。这样其实就比较期待后续plus-33b的效果了，生成类任务的效果应该会有一个提升。

### 羊驼系模型

参考：

- [Guanaco, Llama, Vicuña, Alpaca该怎么区别](https://zhuanlan.zhihu.com/p/106262896)
- [大模型入门（一）—— LLaMa/Alpaca/Vicuna](https://www.cnblogs.com/jiangxinyang/p/17310398.html)
- https://blog.csdn.net/v_JULY_v/article/details/129709105

Vicuna是在LLaMa-13B的基础上使用监督数据微调得到的模型，数据集来自于ShareGPT.com 产生的用户对话数据，共70K条。使用Pytorch FSDP在8张A100上训练了一天。相较于Alpaca，Vicuna在训练中将序列长度由512扩展到了2048，并且通过梯度检测和flash  attention来解决内存问题；调整训练损失考虑多轮对话，并仅根据模型的输出进行微调。通过GPT4来打分评测，Vicuna可以达到ChatGPT 90%的效果。并且还提供了可调用的分布式聊天服务[FastChat](https://github.com/lm-sys/FastChat)。　　

一些模型图标的区分：https://kaiyuan.blog.csdn.net/article/details/131467606



















## bug1 无法找到显卡驱动

```bash
(base) root@msy-System-Product-Name:~# docker run -d --gpus all -p 80:8501 registry.cn-beijing.aliyuncs.com/chatchat/chatchat:0.2.0
4bcc140c4c5b24e21da7ba6bf863d372f899ddd20e141469959b08ac45b5cf5a
docker: Error response from daemon: could not select device driver "" with capabilities: [[gpu]].
```

解决该bug

---

这个错误通常发生在 Docker 无法在你的机器上找到正确的驱动程序来使用 GPU 的情况下。以下是一些可以解决这个问题的步骤：

1. **检查Docker版本是否支持 --gpus 选项**

   Docker从19.03版本开始支持原生使用GPU。用命令 `docker --version` 检查Docker版本，如果你使用的是更旧的版本，考虑更新Docker至最新版本。 

2. **检查是否安装了 NVIDIA 容器工具箱**

   如果你在docker中使用GPU，你需要安装nvidia-docker2，并在你的docker配置中添加NVIDIA运行时。如果没有安装，按照以下步骤进行安装 



a. **移除旧版本**

旧版本的 Docker 由名为 `nvidia-docker2` 的包支持。新的 Docker 版本由 NVIDIA 容器工具箱支持。如果你已经安装了旧的 `nvidia-docker2` 包，请移除它：

```bash
sudo apt-get purge -y nvidia-docker
```

b. **安装 NVIDIA 容器工具箱** - 添加包存储库：

```bash
curl -s -L https://nvidia.github.io/nvidia-docker/gpgkey | sudo apt-key add -
distribution=$(. /etc/os-release;echo $ID$VERSION_ID)
curl -s -L https://nvidia.github.io/nvidia-docker/$distribution/nvidia-docker.list | sudo tee /etc/apt/sources.list.d/nvidia-docker.list
sudo apt-get update
sudo apt-get install -y nvidia-docker2
sudo systemctl restart docker
```

c. **测试 NVIDIA Docker 安装** - 通过运行一个示例来测试 NVIDIA Docker 的安装是否成功：

```bash
docker run --rm --gpus all nvidia/cuda:11.0-base nvidia-smi
```



1. 如果仍然存在相同的错误，那么你应该检查Docker是否可以访问GPU。你可以通过运行命令 `nvidia-smi` 来检查。如果你可以看到你的GPU列表，Docker也应该能够使用它们。 
2. 确保您的机器上正确安装了 NVIDIA 驱动程序。您可以使用命令 `nvidia-smi` 来验证。 

如果问题仍然存在，请提供更多信息，以便我能更深入地帮助你。

## bug2 回答为空

群里另一个用 docker 方式的，也遇到了相同的问题。决定放弃docker方案，转手动部署。但我不想重新下这些模型包了，就在原docker的基础上重新部署吧

原

```bash
docker run -d --gpus all -p 80:8501 registry.cn-beijing.aliyuncs.com/chatchat/chatchat:0.2.0
```

现

```bash
# 可选，删掉旧的docker
docker stop xxx
dcker rm xxx

docker run -d --name=chatchat2 --restart=always -p 80:8501 f224e85162da

docker exec -it chatchat2 /bin/bash
```

## bug3 git问题

```bash
(base) root@msy-System-Product-Name:~/chatchat# git clone https://huggingface.co/moka-ai/m3e-base
正克隆到 'm3e-base'...
remote: Enumerating objects: 108, done.
remote: Counting objects: 100% (16/16), done.
remote: Compressing objects: 100% (15/15), done.
remote: Total 108 (delta 6), reused 0 (delta 0), pack-reused 92
接收对象中: 100% (108/108), 194.12 KiB | 2.55 MiB/s, 完成.
处理 delta 中: 100% (57/57), 完成.
```

git clone卡在这一步

尝试用安装 Git LFS 解决该问题。

在 Ubuntu 上安装 Git LFS 可以使用以下命令：

旧：

```bash
# 安装必要的软件包
$ sudo apt-get install git

# 下载并安装git-lfs
$ curl -s https://packagecloud.io/install/repositories/github/git-lfs/script.deb.sh | sudo bash
$ sudo apt-get install git-lfs

# 初始化git-lfs
$ git lfs install
```

新：

见官网链接

但看起来没成功

```bash
(base) root@msy-System-Product-Name:~/chatchat# git lfs install
Error: Failed to call git rev-parse --git-dir: exit status 128
Git LFS initialized.
```

后来直接复制黏贴了，不git了。其实就是10G的git时间太慢了而已。耐心等也可以，我选择先用有线下载再用wifi传过去

## bug4 找不到存在的路径

```bash
FileNotFoundError: [Errno 2] No usable temporary directory found in ['/tmp', '/var/tmp', '/usr/tmp', '/root/chatchat/Langchain-Chatchat']
```

但路径都是真实存在的

后来发现应该是我硬盘空间满了的原因

## bug5 一直卡在 wait controller running

分步运行中，用 ` python server/llm_api_stale.py` 则一直卡在wait controller running

换用回一键启动的命令，群友说那个分步启用的可能官方要不维护了

## bug6 爆显存

重启电脑解决













































