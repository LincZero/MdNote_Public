# Python

# 目录

# Excel库

参考：

- [【CSDN】Python 自动化操作 Excel 看这一篇就够了，办公效率直线提升︕](https://blog.csdn.net/m0_59235508/article/details/122808875)

## 九个Excel库对比

我们先来看一下python中能操作Excel的库对比（一共九个库、均为非标准库）：

### 兼容性与功能

![img](Excel库.assets/c85f1b571dcc06ee6627150d6cc46e9a.png)

表格

|           | WIN_   | MAC_   | PY2_   | PY3_   | .xls_  | .xlsx  | 读     | 写     | 改     | 样式和<br />图片 | 10MB<br />耗时 |
| --------- | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ | ------ |
| xlrd      | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | 否     | 否 | 否 | 12.38s |
| xlwt      | ==能== | ==能== | ==能== | ==能== | ==能== | 否    | 否    | ==能== | ==能== | ==能== | ——  |
| xlutils   | ==能== | ==能== | ==能== | ==能== | ==能== | 否  | 否 | 否 | ==能== | 否 | —— |
| xlwings   | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | 7.06s |
| openpyxl  | ==能== | 否 | ==能== | ==能== | 否 | ==能== | ==能== | ==能== | ==能== | ==能== | 27.93s |
| xlswriter | ==能== | ==能== | ==能== | ==能== | 否 | ==能== | 否 | ==能== | 否 | ==能== | —— |
| win32com  | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | —— | —— |
| DataNitro | ==能== | 否 | ==能== | ==能== | ==能== | ==能== | ——     | ——     | ——     | ——   | —— |
| pandas    | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | ==能== | 否 | 否 | 17.55s |

### 官网和补充

|           | pip                    | 官网                                                         | 说明                                                         |
| :-------- | ---------------------- | ------------------------------------------------------------ | ------------------------------------------------------------ |
| xlrd      | pip install xlrd       | 官方文档：https://xlrd.readthedocs.io/en/latest/             | 可以用于读取Excel的数据，<br />速度非常快，推荐使用！        |
| xlwt      | pip install xlwt       | 官方文档：https://xlwt.readthedocs.io/en/latest/             | 可以用于写入新的Excel表格<br />或者在原表格基础上进行修改，<br />速度也很快，推荐使用！ |
| xlutils   | pip install xlutils    | 官方文档：https://xlutils.readthedocs.io/en/latest/          | 可用于拷贝原excel<br />或者在原excel基础上进行修改，并保存<br />（可配合xlrd使用） |
| xlwings   | pip install xlwings    | 官网地址：www.xlwings.org/<br />官方文档：https://docs.xlwings.org/en/stable/api.html | 豪华。==开源免费，一直在更新==                               |
| openpyxl  | pip install openpyxl   | 官方文档：https://openpyxl.readthedocs.io/en/stable/         |                                                              |
| xlswriter | pip install XlsxWriter | 官方文档：https://xlsxwriter.readthedocs.io/                 | 缺点：不能用来读取和修改excel文件                            |
| win32com  | pip install pypiwin32  |                                                              | 可以操作word、调用宏等                                       |
| DataNitro | ——                     | ——                                                           | ——                                                           |
| pandas    | pip install pandas     | 官方网站：https://pandas.pydata.org/<br />中文网站：https://www.pypandas.cn/<br />官方文档：https://pandas.pydata.org/pandas-docs/stable/ | 该工具是为了解决数据分析任务而创建的                         |

补充：
话说Pandas的 “可选依赖项” 里有：

| 依賴       | 最低版本 | 筆記                |
| ---------- | -------- | ------------------- |
| xlrd       | 2.0.1    | 閱讀 Excel          |
| xlwt       | 1.3.0    | 編寫 Excel          |
| xlsxwriter | 1.2.2    | 編寫 Excel          |
| openpyxl   | 3.0.3    | 讀取/寫入 xlsx 文件 |
| pyxlsb     | 1.0.6    | 讀取 xlsb 文件      |

### 优缺点以及选择

- xlwings
  - ==开源免费==、功能全面、速度快
- pandas
  - 处理方便，但是不能添加图片修改样式
- openpyxl
  - 主要用到三个概念：Workbooks，Sheets，Cells
  - 虽然各种操作都支持，但是速度又相对慢一点

