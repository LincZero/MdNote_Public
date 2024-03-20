# Python

# 目录

# Excel库 - Pandas

参考：

- 官方网站：https://pandas.pydata.org/
- 中文网站：https://www.pypandas.cn/
- 官方文档：https://pandas.pydata.org/pandas-docs/stable/
  - 入门教程：https://pandas.pydata.org/pandas-docs/stable/user_guide/index.html
  - 进阶教程：https://pandas.pydata.org/pandas-docs/stable/getting_started/index.html
  - API手册：https://pandas.pydata.org/pandas-docs/stable/reference/index.html

## Pandas简概

### 特点：开箱即用（out-of-the-box feature，也称OOTB或off the shelf）



> WIKI
>
> **开箱即用功能（out-of-the-box feature，也称OOTB或off the shelf）**在软件上指产品在安装后，无需配置或修改，即可使用的功能或特性。
> 也指默认即对所有用户可用，不需支付额外费用或进行另外的配置。



我们常说的spring-boot或者vue组件等可以开箱即用，就是可以无需配置就可以实现大部分功能，但是他们依旧是可以配置的。**（强调约定优于配置）**



> 算了，这人回答得怪怪的，不参考了
>
> ~~参考：[【知乎】怎样理解spring中的开箱即用，可插拔等抽象概念？](https://www.zhihu.com/question/66883424/answer/346153201)~~
>
> 1. “Out of box” & “In the box”
>
>    1. **“Out of box”**  用于描述某种不确定的事件
>
>       常常作为副词来形容某种观点的不确定性
>
>       > 来源：据说这个词同20世纪早期的英国数学家亨利?恩斯特?杜德耐解答一个著名数学谜语的思路相关
>       > 题目要求用四条直线连接平面上三乘三分布的九个点，要求一笔连成,也就是在画线的时候笔不能离开纸面
>       > 解决这个数学问题的关键在于要克服传统的在三乘三边界内画点的思想，如果将线连接到边界之外，那么问题可以迎刃而解。
>       >
>       > 这样就产生了 **“Out of box”** 这个词。相应的，将思维受限这种情况称 **“boxed－in”**
>
>       在IT领域,节奏变化很快，因此每个人都在寻找 “Out of box” 的思维方式，尝试创新.
>
>    2. **“In the box”**  用于表示某种确定的事情
>
>       比如：最近有一篇文章讨论了MP3以及盗版音乐的关系，其中引用了一位业内人士的话表示：
>       “主流唱片公司很少关心互联网上的发展，他们的思维就是 **"Inside the box"**
>
> 2. **"Out of the box" (开箱即用)** 也用作 **"off the shelf"（现货供应**）的同义词
>
>    其含义是指能够满足一定需求的、已经作好了的软件、硬件或两者的结合形式。如不采用，就需要投入专门的人力物力来开发

### 包概述

> pandas 是一个 Python 包，提供快速、  灵活且富有表现力的数据结构，旨在使  “关系” 或 “标记” 数据既简单又直观。 它旨在成为  的基本高级构建块 实际 数据  Python中的分析。 成为 即  最强大、最灵活的开源数据分析/操作工具  提供任何语言版本 。 它已经在朝着这个目标迈进。 

## 安装

強烈建議使用 `conda`，用於快速安裝以及包和依賴項更新

- 使用 Anaconda 安裝

- 使用 Miniconda 安裝

- 使用 ActivePython 安裝

- 从 PyPI 安裝

- 使用 Linux 发行版的包管理器进行安装

  - 處理 ImportErrors：如果遇到 ImportError，通常意味著 Python 在可用列表中找不到 pandas 圖書館。  Python 內部有一個它搜索的目錄列表，用於查找包。  你可以 獲取這些目錄

    ```python
    import sys
    sys.path
    ```

- 從源代碼安裝

### 運行測試套件

pandas 配備了一套詳盡的單元測試，覆蓋了大約 97%  撰寫本文時的代碼庫。 在你的機器上運行它來驗證  一切正常

```shell
>>> pd.test()
running: pytest --skip-slow --skip-network C:\Users\TP\Anaconda3\envs\py36\lib\site-packages\pandas
============================= test session starts =============================
platform win32 -- Python 3.6.2, pytest-3.6.0, py-1.4.34, pluggy-0.4.0
rootdir: C:\Users\TP\Documents\Python\pandasdev\pandas, inifile: setup.cfg
collected 12145 items / 3 skipped

..................................................................S......
........S................................................................
.........................................................................

==================== 12130 passed, 12 skipped in 368.339 seconds =====================
```

### 依赖

| Package                                                      | Minimum supported version |
| ------------------------------------------------------------ | ------------------------- |
| [NumPy](https://numpy.org)                                   | 1.18.5                    |
| [python-dateutil](https://dateutil.readthedocs.io/en/stable/) | 2.8.1                     |
| [pytz](https://pypi.org/project/pytz/)                       | 2020.1                    |

#### 依赖推荐

- [numexpr](https://github.com/pydata/numexpr): 用於加速某些數值運算。 `numexpr`使用多個核心以及智能分塊和緩存來實現大幅加速。 如果已安裝，則必須是 2.7.1 或更高版本
- [bottleneck](https://github.com/pydata/bottleneck): 用於加速某些類型的 `nan` 評價。 `bottleneck`使用專門的 cython 例程來實現大幅加速。  如果安裝， 必須是 1.3.1 或更高版本

#### 可选依赖项

pandas 有许多可选依赖项，它们仅用于特定方法

 例如

- pandas.read_hdf() 需要 pytables包
- DataFrame.to_markdown() 需要 tabulate包

 如果 未安装可选依赖项，pandas 将引发 ImportError什么时候 调用需要该依赖项的方法

> ##### Visualization

| 依赖       | 最低版本 | 笔记                                                         |
| ---------- | -------- | ------------------------------------------------------------ |
| matplotlib | 3.3.2    | Plotting library                                             |
| Jinja2     | 2.11     | Conditional formatting with DataFrame.style                  |
| tabulate   | 0.8.7    | Printing in Markdown-friendly format (see [tabulate](https://github.com/astanin/python-tabulate)) |

> ##### Computation

| 依赖   | 最低版本 | 笔记                                                         |
| ------ | -------- | ------------------------------------------------------------ |
| SciPy  | 1.4.1    | Miscellaneous statistical functions                          |
| numba  | 0.50.1   | Alternative execution engine for rolling operations (see [Enhancing Performance](https://pandas.pydata.org/pandas-docs/stable/user_guide/enhancingperf.html#enhancingperf-numba)) |
| xarray | 0.15.1   | pandas-like API for N-dimensional data                       |

> ##### Excel files

| 依赖       | 最低版本 | 笔记                             | 依赖操作  |
| ---------- | -------- | -------------------------------- | --------- |
| xlrd       | 2.0.1    | Reading Excel                    |           |
| xlwt       | 1.3.0    | Writing Excel                    |           |
| xlsxwriter | 1.2.2    | Writing Excel                    |           |
| openpyxl   | 3.0.3    | Reading / writing for xlsx files | .to_excel |
| pyxlsb     | 1.0.6    | Reading for xlsb files           |           |

> ##### HTML

| 依赖           | 最低版本 | 笔记                      |
| -------------- | -------- | ------------------------- |
| BeautifulSoup4 | 4.8.2    | HTML parser for read_html |
| html5lib       | 1.1      | HTML parser for read_html |
| lxml           | 4.5.0    | HTML parser for read_html |

> ##### XML

| 依赖 | 最低版本 | 笔记                                                |
| ---- | -------- | --------------------------------------------------- |
| lxml | 4.5.0    | XML parser for read_xml and tree builder for to_xml |

> ##### SQL databases

| 依赖       | 最低版本 | 笔记                                        |
| ---------- | -------- | ------------------------------------------- |
| SQLAlchemy | 1.4.0    | SQL support for databases other than sqlite |
| psycopg2   | 2.8.4    | PostgreSQL engine for sqlalchemy            |
| pymysql    | 0.10.1   | MySQL engine for sqlalchemy                 |

> ##### Other data sources

| 依赖        | 最低版本 | 笔记                                        |
| ----------- | -------- | ------------------------------------------- |
| PyTables    | 3.6.1    | HDF5-based reading / writing                |
| blosc       | 1.20.1   | Compression for HDF5                        |
| zlib        |          | Compression for HDF5                        |
| fastparquet | 0.4.0    | Parquet reading / writing                   |
| pyarrow     | 1.0.1    | Parquet, ORC, and feather reading / writing |
| pyreadstat  | 1.1.0    | SPSS files (.sav) reading                   |

> ##### Access data in the cloud

| 依赖       | 最低版本 | 笔记                                            |
| ---------- | -------- | ----------------------------------------------- |
| fsspec     | 0.7.4    | Handling files aside from simple local and HTTP |
| gcsfs      | 0.6.0    | Google Cloud Storage access                     |
| pandas-gbq | 0.14.0   | Google Big Query access                         |
| s3fs       | 0.4.0    | Amazon S3 access                                |

> ##### Clipboard

| 依赖        | 最低版本 | 笔记                   |
| ----------- | -------- | ---------------------- |
| PyQt4/PyQt5 |          | Clipboard I/O          |
| qtpy        |          | Clipboard I/O          |
| xclip       |          | Clipboard I/O on linux |
| xsel        |          | Clipboard I/O on linux |

> ##### Compression

| 依赖          | 最低版本 | 笔记                  |
| ------------- | -------- | --------------------- |
| brotli        | 0.7.0    | Brotli compression    |
| python-snappy | 0.6.0    | Snappy compression    |
| Zstandard     | 0.15.2   | Zstandard compression |

# 入门教程

## 基本数据

核心概念：DateFrame 、row 行、column 竖

### 导入

```python
import pandas as pd
```

### 数据结构

| 方面 | 姓名      | 描述                                                 |
| ---- | --------- | ---------------------------------------------------- |
| 1    | Series    | 一维标记的同质类型数组                               |
| 2    | DataFrame | 具有潜在异构类型列的通用 2D 标记、大小可变的表格结构 |

所有 pandas 数据结构都是值可变的（它们包含的值可以是  改变）但并不总是大小可变的

#### DataFrame

要在表中手动存储数据，请创建一个 `DataFrame`

一个 DateFram 是一种二维数据结构，可以存储 不同的类型（包括字符、整数、浮点值、 分类数据等）在列中。 
 它类似于电子表格， SQL 表或 `data.frame`在 R。 

用DataFrame存储一些数据

```python
df = pd.DataFrame(
    {
        "Name": [
            "Braund, Mr. Owen Harris",
            "Allen, Mr. William Henry",
            "Bonnell, Miss. Elizabeth",
        ],
        "Age": [22, 35, 58],
        "Sex": ["male", "male", "female"],
    }
)

df
"""
                       Name  Age     Sex
0   Braund, Mr. Owen Harris   22    male
1  Allen, Mr. William Henry   35    male
2  Bonnell, Miss. Elizabeth   58  female
"""

type(df[["Age", "Sex"]])	# 类型
""" pandas.core.frame.DataFrame """

dp[["Age", "Sex"]].shape	# 返回行列数
""" (891, 2) """
```

#### Series

每一列 `DataFrame`是一个 `Series`

比如我只是对使用列中的数据感兴趣 `Age`：

```python
df["Age"]

"""
0    22
1    35
2    58
Name: Age, dtype: int64
"""

type(df["Age"])				# 类型
""" pandas.core.series.Series """

df["Age"].shape  			# 返回行列数
""" (3,) """
```

直接创建一个 `Series`

```python
ages = pd.Series([22, 35, 58], name="Age")

ages
"""
0    22
1    35
2    58
Name: Age, dtype: int64
"""
```

## 读写表格数据

### read_*  读取文件

pandas 支持许多不同的文件 开箱即用的格式或数据源（csv、excel、sql、json、parquet、 …)，每个都带有前缀 `read_*`

```python
titanic = pd.read_csv("data/titanic.csv")	# 读取存储为 csv 的数据的函数并归档成 DataFrame
```

### to_*  存储到文件

`read_*`函数用于向 pandas 读取数据， `to_*`方法用于存储数据。  这 [`to_excel()`](https://pandas.pydata.org/pandas-docs/stable/reference/api/pandas.DataFrame.to_excel.html#pandas.DataFrame.to_excel)方法存储 数据作为excel文件

==注意：默认为utf-8编码，而Excel打开utd-8编码的csv文件时，中文部分会乱码==

```python
# excel, 需要openpyxl的依赖
titanic.to_excel("titanic.xlsx", sheet_name="passengers", index=False)	# 向Excel写入
titanic = pd.read_excel("titanic.xlsx", sheet_name="passengers")		# 读取

# csv, 不需要openpyxl的依赖
data_frame.to_csv("汉字.csv", encoding="gbk")
data_frame =pd.read_csv("汉字.csv", encoding="gbk")						# 不加编码会抛出报编码错误
"""																		 # 如果存储时不加index=False，则再次取回时会多出一列
																		 # 按理说应该能有一个选项可以把这列给去掉，或者用该列作为序列
       Unnamed: 0 word oldword  strokes pinyin radicals
0               0    嗄       嗄       13      á        口
1               1    吖       吖        6      ā        口
2               2    阿       阿        7      ā        阝
3               3    啊       啊       10      ā        口
4               4    锕       録       12      ā        钅
...           ...  ...     ...      ...    ...      ...
16137       16137    酢       酢       12    zuò        酉
16138       16138    阝       阝       14    zuǒ      NaN
16139       16139    左       左        5    zuǒ        工
16140       16140    佐       佐        7    zuǒ        亻
16141       16141    繓       繓       10    zuǒ      NaN
"""
```

### 常见报错

```python
# 常见报错
# 编码错误：encoding Permission Error
# 没有权限（文件被其他软件打开了）：Permission denied
```

### 方法原型

```python
def to_csv(
    self,
    path_or_buf: FilePathOrBuffer[AnyStr] | None = None,
    sep: str = ",",
    na_rep: str = "",
    float_format: str | None = None,
    columns: Sequence[Hashable] | None = None,
    header: bool_t | list[str] = True,
    index: bool_t = True,
    index_label: IndexLabel | None = None,
    mode: str = "w",
    encoding: str | None = None,
    compression: CompressionOptions = "infer",
    quoting: int | None = None,
    quotechar: str = '"',
    line_terminator: str | None = None,
    chunksize: int | None = None,
    date_format: str | None = None,
    doublequote: bool_t = True,
    escapechar: str | None = None,
    decimal: str = ".",
    errors: str = "strict",
    storage_options: StorageOptions = None,
) -> str | None:
    
def read_csv(
    filepath_or_buffer: FilePathOrBuffer,
    sep=lib.no_default,
    delimiter=None,
    # Column and Index Locations and Names
    header="infer",
    names=lib.no_default,
    index_col=None,
    usecols=None,
    squeeze=False,
    prefix=lib.no_default,
    mangle_dupe_cols=True,
    # General Parsing Configuration
    dtype: DtypeArg | None = None,
    engine=None,
    converters=None,
    true_values=None,
    false_values=None,
    skipinitialspace=False,
    skiprows=None,
    skipfooter=0,
    nrows=None,
    # NA and Missing Data Handling
    na_values=None,
    keep_default_na=True,
    na_filter=True,
    verbose=False,
    skip_blank_lines=True,
    # Datetime Handling
    parse_dates=False,
    infer_datetime_format=False,
    keep_date_col=False,
    date_parser=None,
    dayfirst=False,
    cache_dates=True,
    # Iteration
    iterator=False,
    chunksize=None,
    # Quoting, Compression, and File Format
    compression="infer",
    thousands=None,
    decimal: str = ".",
    lineterminator=None,
    quotechar='"',
    quoting=csv.QUOTE_MINIMAL,
    doublequote=True,
    escapechar=None,
    comment=None,
    encoding=None,
    encoding_errors: str | None = "strict",
    dialect=None,
    # Error Handling
    error_bad_lines=None,
    warn_bad_lines=None,
    # TODO (2.0): set on_bad_lines to "error".
    # See _refine_defaults_read comment for why we do this.
    on_bad_lines=None,
    # Internal
    delim_whitespace=False,
    low_memory=_c_parser_defaults["low_memory"],
    memory_map=False,
    float_precision=None,
    storage_options: StorageOptions = None,
):
```

## 显示方法

### 数据显示

#### 默认仅显示前后5行数据

```python
titanic				# 默认仅显示前后5行数据
"""
     PassengerId  Survived  Pclass                         Name  ...            Ticket     Fare  Cabin  Embarked
0              1         0       3      Braund, Mr. Owen Harris  ...         A/5 21171   7.2500    NaN         S
1              2         1       1       Cumings, Mrs. John ...  ...          PC 17599  71.2833    C85         C
2              3         1       3       Heikkinen, Miss. Laina  ...  STON/O2. 3101282   7.9250    NaN         S
3              4         1       1    Futrelle, Mrs. Jacques...  ...            113803  53.1000   C123         S
4              5         0       3     Allen, Mr. William Henry  ...            373450   8.0500    NaN         S
..           ...       ...     ...                          ...  ...               ...      ...    ...       ...
886          887         0       2        Montvila, Rev. Juozas  ...            211536  13.0000    NaN         S
887          888         1       1   Graham, Miss. Margaret ...  ...            112053  30.0000    B42         S
888          889         0       3          Johnston, Miss. ...  ...        W./C. 6607  23.4500    NaN         S
889          890         1       1        Behr, Mr. Karl Howell  ...            111369  30.0000   C148         C
890          891         0       3          Dooley, Mr. Patrick  ...            370376   7.7500    NaN         Q

[891 rows x 12 columns]
"""
```

#### head()  查看前面几行

```python
titanic.head()		# 无参数则默认查看前5行
titanic.head(8)		# 查看前8行
"""
     PassengerId  Survived  Pclass                         Name  ...            Ticket     Fare  Cabin  Embarked
0              1         0       3      Braund, Mr. Owen Harris  ...         A/5 21171   7.2500    NaN         S
1              2         1       1       Cumings, Mrs. John ...  ...          PC 17599  71.2833    C85         C
2              3         1       3       Heikkinen, Miss. Laina  ...  STON/O2. 3101282   7.9250    NaN         S
3              4         1       1    Futrelle, Mrs. Jacques...  ...            113803  53.1000   C123         S
4              5         0       3     Allen, Mr. William Henry  ...            373450   8.0500    NaN         S
5              6         0       3     Moran, Mr. James    male  ...             330877   8.4583   NaN         Q
6              7         0       1    McCarthy, Mr. Timothy ...  ...              17463  51.8625   E46         S
7              8         0       3   Palsson, Master. Gosta ...  ...             349909  21.0750   NaN         S

[8 rows x 12 columns]
"""
```

#### tail()  查看最后5行

```python
titanic.tail(10)	# 查看最后10行
""" 略 """
```

### 信息显示

#### shape  显示行列数

```python
dp[["Age", "Sex"]].shape	# 返回行列数
""" (891, 2) """

df["Age"].shape  			# 返回行列数
""" (3,) """
```

#### describe()  快速统计

```python
# 許多 pandas 操作返回一個 DataFrame或一個 Series

df["Age"].max()		# 获取最大值
""" 58 """
ages.max()			# 获取最大值
""" 58 """

df.describe()		# 快速生成基本统计
"""
             Age
count   3.000000
mean   38.333333
std    18.230012
min    22.000000
25%    28.500000
50%    35.000000
75%    46.500000
max    58.000000
"""
```

#### dtypes  解释每种列数据类型

```python
titanic.dtypes		# 解释每种列数据类型
"""
PassengerId      int64
Survived         int64
Pclass           int64
Name            object
Sex             object
Age            float64
SibSp            int64
Parch            int64
Ticket          object
Fare           float64
Cabin           object
Embarked        object
dtype: object
"""
```

#### info()  查看DataFrame总结信息

该输出也是一个DateFrame

```python
titanic.info()
"""
<class 'pandas.core.frame.DataFrame'>
RangeIndex: 891 entries, 0 to 890
Data columns (total 12 columns):
 #   Column       Non-Null Count  Dtype  
---  ------       --------------  -----  
 0   PassengerId  891 non-null    int64  
 1   Survived     891 non-null    int64  
 2   Pclass       891 non-null    int64  
 3   Name         891 non-null    object 
 4   Sex          891 non-null    object 
 5   Age          714 non-null    float64
 6   SibSp        891 non-null    int64  
 7   Parch        891 non-null    int64  
 8   Ticket       891 non-null    object 
 9   Fare         891 non-null    float64
 10  Cabin        204 non-null    object 
 11  Embarked     889 non-null    object 
dtypes: float64(2), int64(5), object(5)
memory usage: 83.7+ KB
"""
```

## 创建DateFrame子集的方法

准备工作

```python
titanic = pd.read_csv("data/titanic.csv")
ages = titanic["Age"]		# 单列
titanic["Age"].shape		# 输出：(891,)
```

### [ ]

#### [ ] 的三种参数

接受三种参数

- 字符串：返回的是Series
- 字符串列表：返回DateFrame
- Series：返回DateFrame

#### 字符串参数 - 筛选列

```python
df["Age"]

"""
0    22
1    35
2    58
Name: Age, dtype: int64
"""
```

#### 字符串列表参数 - 筛选多列

```python
age_sex = titanic[["Age", "Sex"]]		# 创建子表 - 按列
age_sex.head()
"""
    Age     Sex
0  22.0    male
1  38.0  female
2  26.0  female
3  35.0  female
4  35.0    male
"""
```

#### Series参数 - 筛选行/条件筛选行

##### 原理（条件筛选原理：Series做逻辑运算）

```python
# 原理如下
print(type(titanic["Age"]), (titanic["Age"]))			# 返回的都是Series类型
""" pandas.core.series.Series  pandas.core.series.Series """

titanic["Age"] > 35
"""
0      False
1       True
2      False
3      False
4      False
       ...  
886    False
887    False
888    False
889    False
890    False
Name: Age, Length: 891, dtype: bool
"""
```

##### 比较

```python
above_35 = titanic[titanic["Age"] > 35]					# 年龄大于35
"""
    PassengerId  Survived  Pclass                                               Name     Sex  ...  Parch    Ticket     Fare
1             2         1       1  Cumings, Mrs. John Bradley (Florence Briggs Th...  female  ...      0  PC 17599  71.2833
6             7         0       1                            McCarthy, Mr. Timothy J    male  ...      0     17463  51.8625
11           12         1       1                           Bonnell, Miss. Elizabeth  female  ...      0    113783  26.5500
13           14         0       3                        Andersson, Mr. Anders Johan    male  ...      5    347082  31.2750
15           16         1       2                   Hewlett, Mrs. (Mary D Kingcome)   female  ...      0    248706  16.0000

[5 rows x 12 columns]
"""
```

##### 包含

```python
class_23 = titanic[titanic["Pclass"].isin([2, 3])]		# 2 和 3 舱的泰坦尼克号乘客
class_23.head()
"""
   PassengerId  Survived  Pclass                            Name     Sex   Age  SibSp  Parch            Ticket     Fare
0            1         0       3         Braund, Mr. Owen Harris    male  22.0      1      0         A/5 21171   7.2500
2            3         1       3          Heikkinen, Miss. Laina  female  26.0      0      0  STON/O2. 3101282   7.9250
4            5         0       3        Allen, Mr. William Henry    male  35.0      0      0            373450   8.0500
5            6         0       3                Moran, Mr. James    male   NaN      0      0            330877   8.4583
7            8         0       3  Palsson, Master. Gosta Leonard    male   2.0      3      1            349909  21.0750
"""
```

#####  逻辑运算

```python
class_23 = titanic[(titanic["Pclass"] == 2) | (titanic["Pclass"] == 3)]		# 即：Series类型可以做逻辑运算
class_23.head()
"""
Out[19]: 
   PassengerId  Survived  Pclass                            Name     Sex   Age  SibSp  Parch            Ticket     Fare
0            1         0       3         Braund, Mr. Owen Harris    male  22.0      1      0         A/5 21171   7.2500
2            3         1       3          Heikkinen, Miss. Laina  female  26.0      0      0  STON/O2. 3101282   7.9250
4            5         0       3        Allen, Mr. William Henry    male  35.0      0      0            373450   8.0500
5            6         0       3                Moran, Mr. James    male   NaN      0      0            330877   8.4583
7            8         0       3  Palsson, Master. Gosta Leonard    male   2.0      3      1            349909  21.0750
"""
```

##### 非空

```python
age_no_na = titanic[titanic["Age"].notna()]					# 已知年龄的乘客数据
age_no_na.head()
"""
   PassengerId  Survived  Pclass                                               Name     Sex  ...  Parch            Ticket
0            1         0       3                            Braund, Mr. Owen Harris    male  ...      0         A/5 21171 
1            2         1       1  Cumings, Mrs. John Bradley (Florence Briggs Th...  female  ...      0          PC 17599 
2            3         1       3                             Heikkinen, Miss. Laina  female  ...      0  STON/O2. 3101282 
3            4         1       1       Futrelle, Mrs. Jacques Heath (Lily May Peel)  female  ...      0            113803
4            5         0       3                           Allen, Mr. William Henry    male  ...      0            373450

[5 rows x 12 columns]
"""
```

### loc()  子集 + 条件

也可以选择到某个单元格

完全等同于 `titanic[titanic["Age"] > 35]["Name"]`？（https://pandas.pydata.org/pandas-docs/stable/user_guide/indexing.html#returning-a-view-versus-a-copy）

```python
# 完全等同于 titanic[titanic["Age"] > 35]["Name"]
adult_names = titanic.loc[titanic["Age"] > 35, "Name"]
adult_names.head()
"""
1     Cumings, Mrs. John Bradley (Florence Briggs Th...
6                               McCarthy, Mr. Timothy J
11                             Bonnell, Miss. Elizabeth
13                          Andersson, Mr. Anders Johan
15                     Hewlett, Mrs. (Mary D Kingcome) 
Name: Name, dtype: object
"""
```

### iloc()  二维切片、切片并赋值

切片

```python
titanic.iloc[9:25, 2:5]		# 第 10 到 25 行和第 3 到 5 列
"""
    Pclass                                 Name     Sex
9        2  Nasser, Mrs. Nicholas (Adele Achem)  female
10       3      Sandstrom, Miss. Marguerite Rut  female
11       1             Bonnell, Miss. Elizabeth  female
12       3       Saundercock, Mr. William Henry    male
13       3          Andersson, Mr. Anders Johan    male
..     ...                                  ...     ...
20       2                 Fynney, Mr. Joseph J    male
21       2                Beesley, Mr. Lawrence    male
22       3          McGowan, Miss. Anna "Annie"  female
23       1         Sloper, Mr. William Thompson    male
24       3        Palsson, Miss. Torborg Danira  female

[16 rows x 3 columns]
"""
```

切片并赋值

```python
titanic.iloc[0:3, 3] = "anonymous"
titanic.head()
"""
   PassengerId  Survived  Pclass                                          Name     Sex  ...  Parch            Ticke
0            1         0       3                                     anonymous    male  ...      0         A/5 21171
1            2         1       1                                     anonymous  female  ...      0          PC 17599
2            3         1       3                                     anonymous  female  ...      0  STON/O2. 3101282
3            4         1       1  Futrelle, Mrs. Jacques Heath (Lily May Peel)  female  ...      0            113803
4            5         0       3                      Allen, Mr. William Henry    male  ...      0            373450

[5 rows x 12 columns]
"""
```

## 扩展新列

### 扩展新列

本质：等号右边是一个Series类型

```python
# Series与数字四则运算
air_quality["london_mg_per_cubic"] = air_quality["station_london"] * 1.882  # 添加新列 "london_mg_per_cubic"

# Series与Series四则运算
air_quality["ratio_paris_antwerp"] = (
    air_quality["station_paris"] / air_quality["station_antwerp"]
)
```

### rename()  将数据列重命名

```python
air_quality_renamed = air_quality.rename(		# 修改其中三列的字段
    columns={
        "station_antwerp": "BETR801",
        "station_paris": "FR04014",
        "station_london": "London Westminster",
    }
)

air_quality_renamed = air_quality_renamed.rename(columns=str.lower)	# 将字段名全部修改为小写
```

### Q？TODO 话说我要让他们执行同一个方法怎么办，比如 lower(数据)，而不是.xx方法















## 在Pandas中创建图形

准备工作

```python
import pandas as pd
import matplotlib.pyplot as plt
air_quality = pd.read_csv("data/air_quality_no2.csv", index_col=0, parse_dates=True)
```

### plot()  折线图

```python
air_quality.plot()					# 默认为每一个具有数字数据的列创建一个折线图
"""
<AxesSubplot:xlabel='datetime'>
【这里是一张图片】
"""

air_quality["station_paris"].plot()	# 仅为某个数据创建折线图
"""
<AxesSubplot:xlabel='datetime'>
【这里是一张图片】
"""
```

### plot.scatter()  散点图

```python
air_quality.plot.scatter(x="station_london", y="station_paris", alpha=0.5)
"""
Out[7]: <AxesSubplot:xlabel='station_london', ylabel='station_paris'>
【这里是一张图片】
"""
```

### TODO：此略，暂时跳过

## 计算汇总统计

### 聚合统计

#### 数值统计

最大值

```python
df["Age"].max()						# 获取最大值（Series方法）
""" 58 """
```

平均值

```python
titanic["Age"].mean()				# 泰坦尼克号乘客的平均年龄是多少？（Series方法）
""" 29.69911764705882 """

titanic[["Age", "Fare"]].median()	# 泰坦尼克号乘客的平均年龄和票价是多少？ （DataFrame方法）
"""
Age     28.0000
Fare    14.4542
dtype: float64
"""
```

#### describe()  快速统计

```python
ages.describe()		# 快速生成基本统计
"""
             Age
count   3.000000
mean   38.333333
std    18.230012
min    22.000000
25%    28.500000
50%    35.000000
75%    46.500000
max    58.000000
"""

titanic[["Age", "Fare"]].describe()
"""
              Age        Fare
count  714.000000  891.000000
mean    29.699118   32.204208
std     14.526497   49.693429
min      0.420000    0.000000
25%     20.125000    7.910400
50%     28.000000   14.454200
75%     38.000000   31.000000
max     80.000000  512.329200
"""
```

#### agg()  制定多项统计

```python
titanic.agg(
    {
        "Age": ["min", "max", "median", "skew"],
        "Fare": ["min", "max", "median", "mean"],
    }
)
"""
              Age        Fare
min      0.420000    0.000000
max     80.000000  512.329200
median  28.000000   14.454200
skew     0.389108         NaN
mean          NaN   32.204208
"""
```

### groupby  按分组统计

```python
titanic[["Sex", "Age"]].groupby("Sex").mean()	# 男性和女性泰坦尼克號乘客的平均年齡是多少？ 
"""
              Age
Sex              
female  27.915709
male    30.726645
"""

titanic.groupby("Sex").mean()					# 男性和女性泰坦尼克號乘客的平均数据
"""
        PassengerId  Survived    Pclass        Age     SibSp     Parch       Fare
Sex                                                                              
female   431.028662  0.742038  2.159236  27.915709  0.694268  0.649682  44.479818
male     454.147314  0.188908  2.389948  30.726645  0.429809  0.235702  25.523893
"""

titanic.groupby("Sex")["Age"].mean()			# 好像和第一种方法的区别不大
"""
Sex
female    27.915709
male      30.726645
Name: Age, dtype: float64
"""
```

原理

![06_groupby_select_detail.svg](Excel库-Pandas.assets/06_groupby_select_detail.svg)

双重分组

```python
titanic.groupby(["Sex", "Pclass"])["Fare"].mean()	# 每個性別和艙位組合的平均票價是多少？ 
"""
Sex     Pclass
female  1         106.125798
        2          21.970121
        3          16.118810
male    1          67.226127
        2          19.741782
        3          12.661633
Name: Fare, dtype: float64
"""
```

### 按类别计数

```python
titanic["Pclass"].value_counts()		# 每個艙位的乘客人數是多少？
"""
3    491
1    216
2    184
Name: Pclass, dtype: int64
"""

# 該函數是一個快捷方式，因為它實際上是一個 groupby 操作結合記錄數的計數 每組內
titanic.groupby("Pclass")["Pclass"].count()
"""
Pclass
1    216
2    184
3    491
Name: Pclass, dtype: int64
"""
```



## 合并多个表格数据

准备工作

```python
air_quality_no2 = pd.read_csv("data/air_quality_no2_long.csv",
                              parse_dates=True)

air_quality_no2 = air_quality_no2[["date.utc", "location",
                                   "parameter", "value"]]

air_quality_no2.head()
"""
                    date.utc location parameter  value
0  2019-06-21 00:00:00+00:00  FR04014       no2   20.0
1  2019-06-20 23:00:00+00:00  FR04014       no2   21.8
2  2019-06-20 22:00:00+00:00  FR04014       no2   26.5
3  2019-06-20 21:00:00+00:00  FR04014       no2   24.9
4  2019-06-20 20:00:00+00:00  FR04014       no2   21.4
"""

air_quality_pm25 = pd.read_csv("data/air_quality_pm25_long.csv",
                               parse_dates=True)

air_quality_pm25 = air_quality_pm25[["date.utc", "location",
                                     "parameter", "value"]]

air_quality_pm25.head()
"""
                    date.utc location parameter  value
0  2019-06-18 06:00:00+00:00  BETR801      pm25   18.0
1  2019-06-17 08:00:00+00:00  BETR801      pm25    6.5
2  2019-06-17 07:00:00+00:00  BETR801      pm25   18.5
3  2019-06-17 06:00:00+00:00  BETR801      pm25   16.0
4  2019-06-17 05:00:00+00:00  BETR801      pm25    7.5
"""
```

### concat()  上下合并（連接對象）

```python
air_quality = pd.concat([air_quality_pm25, air_quality_no2], axis=0)

air_quality.head()
"""
                    date.utc location parameter  value
0  2019-06-18 06:00:00+00:00  BETR801      pm25   18.0
1  2019-06-17 08:00:00+00:00  BETR801      pm25    6.5
2  2019-06-17 07:00:00+00:00  BETR801      pm25   18.5
3  2019-06-17 06:00:00+00:00  BETR801      pm25   16.0
4  2019-06-17 05:00:00+00:00  BETR801      pm25    7.5
"""
```

### 左右合并（使用通用标识符）

准备

```python
stations_coord = pd.read_csv("data/air_quality_stations.csv")

stations_coord.head()
"""
  location  coordinates.latitude  coordinates.longitude
0  BELAL01              51.23619                4.38522
1  BELHB23              51.17030                4.34100
2  BELLD01              51.10998                5.00486
3  BELLD02              51.12038                5.02155
4  BELR833              51.32766                4.36226
"""

air_quality.head()
"""
                       date.utc            location parameter  value
2067  2019-05-07 01:00:00+00:00  London Westminster       no2   23.0
1003  2019-05-07 01:00:00+00:00             FR04014       no2   25.0
100   2019-05-07 01:00:00+00:00             BETR801      pm25   12.5
1098  2019-05-07 01:00:00+00:00             BETR801       no2   50.5
1109  2019-05-07 01:00:00+00:00  London Westminster      pm25    8.0
"""
```

合并

```python
air_quality = pd.merge(air_quality, stations_coord, how="left", on="location")	# 其中"location"为主键
# # how: inner共有 left左为准 cross用id作为on参数

air_quality.head()
"""
                    date.utc            location parameter  value  coordinates.latitude  coordinates.longitude
0  2019-05-07 01:00:00+00:00  London Westminster       no2   23.0              51.49467               -0.13193
1  2019-05-07 01:00:00+00:00             FR04014       no2   25.0              48.83724                2.39390
2  2019-05-07 01:00:00+00:00             FR04014       no2   25.0              48.83722                2.39390
3  2019-05-07 01:00:00+00:00             BETR801      pm25   12.5              51.20966                4.43182
4  2019-05-07 01:00:00+00:00             BETR801       no2   50.5              51.20966                4.43182
"""
```









## 0

### 重塑表格布局

### 处理时间序列数据

### 操作文本数据





































