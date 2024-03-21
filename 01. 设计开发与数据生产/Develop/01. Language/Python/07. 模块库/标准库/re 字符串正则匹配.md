# Python

# 目录

# re 字符串正则匹配

## 字符串方法

只需简单的操作时，字符串方法最好用，因为它们易读，又容易调试:

```python
>>> 'tea for too'.replace('too', 'two')
'tea for two'
```

## re 基本使用

[re](https://docs.python.org/3/library/re.html#module-re) 模块为高级字符串处理提供了正则表达式工具。对于复杂的匹配和处理，正则表达式提供了简洁、优化的解决方案：

### findall、sub

```python
>>> import re
>>> re.findall(r'\bf[a-z]*', 'which foot or hand fell fastest')  # 匹配
['foot', 'fell', 'fastest']

>>> re.sub(r'(\b[a-z]+) \1', r'\1', 'cat in the the hat')  # 替换。注意sub()方法替换字符串的时候如果不匹配，就会返回原字符串。很容易出错
'cat in the hat'
```

### 其他

详见文档

```python
re.search(pattern, string, flags=0)
# 扫描整个 字符串 找到匹配样式的第一个位置，并返回一个相应的 匹配对象。如果没有匹配，就返回一个 None ； 注意这和找到一个零长度匹配是不同的。

re.match(pattern, string, flags=0)
# 如果 string 开始的0或者多个字符匹配到了正则表达式样式，就返回一个相应的 匹配对象 。 如果没有匹配，就返回 None ；注意它跟零长度匹配是不同的。

re.sub(pattern, repl, string, count=0, flags=0)
# 返回通过使用 repl 替换在 string 最左边非重叠出现的 pattern 而获得的字符串。 如果样式没有找到，则不加改变地返回 string。 repl 可以是字符串或函数；如为字符串，则其中任何反斜杠转义序列都会被处理。 也就是说，\n 会被转换为一个换行符，\r 会被转换为一个回车符，依此类推。 未知的 ASCII 字符转义序列保留在未来使用，会被当作错误来处理。 其他未知转义序列例如 \& 会保持原样。 向后引用像是 \6 会用样式中第 6 组所匹配到的子字符串来替换。
```

rearch和match的区别

```python
# match()和search()都只匹配一个结果，但是match()是从字符串的开头开始匹配的，如果匹配的字符不是在开头处，那么它将会报错，匹配成功返回结果，没有返回None。而search()是从头开始匹配，匹配整一个字符串得出结果
import re
result1 = re.match('li', 'liadadafbba').group()
result2 = re.match('li', 'addadlidadaf')
print(result1, result2)  # li None

import re
# result1 = re.match('li', 'liadadafbba')
result2 = re.match('li', 'addadlidadaf').group()
print(result2)  # 报错

import re
result1 = re.search('li', 'liadadafbba').group()
result2 = re.search('li', 'addadlidadaf').group()
print(result1, result2)  # li li
```

### 取子串（坑点）

坑的地方在于：序列0是完整匹配（默认是0），序列1才是第一个，非常反直觉......

```python
>>> m = re.match(r"(\w+) (\w+)", "Isaac Newton, physicist")
>>> m.group(0)       # The entire match
'Isaac Newton'
>>> m.group(1)       # The first parenthesized subgroup.
'Isaac'
>>> m.group(2)       # The second parenthesized subgroup.
'Newton'
>>> m.group(1, 2)    # Multiple arguments give us a tuple.
('Isaac', 'Newton')
```

不过话说其他程序中的正则也是，例如QT C++的 `<QRegularExpression>` 模块

```c++
QRegularExpression re(R"(^OnGetWebViewPageFinish:(.+?/log)$)");
QString line = in.readLine();
QRegularExpressionMatch match = re.match(line);
if(match.hasMatch())
{
    qDebug()<<"WishUrl1: "<<match.captured(1);	// 序列1才是第一个匹配项
    return match.captured(1);
}
```

## 实战 - 匹配并替换内容

```python
import re
pattern = r"元"	 # 模式字符串
str1 = "75元、89元"  # 匹配字符串
replace = re.sub(pattern, "美元", str1)
print(str1)	 # "75美元、89美元"
```

























