# 目录

因为

## 基本

- 官网：https://obsidian.md
- 官网插件：https://obsidian.md/plugins
- 官网帮助文档：https://publish.obsidian.md/help-zh/



## CSS开发

- CSS
	- 自定义CSS：https://publish.obsidian.md/help-zh/高级用法/自定义+CSS
	- 常用选择器：https://forum.obsidian.md/t/common-selectors-for-custom-css/1984
	  用这个会规范很多，方便设置主题

CTRL-SHIFT-I，打开开发者窗口
只支持CSS，不支持SCSS、SASS、LESS



## 插件开发

详见：Develop > Project > Type Script > Plugin_Obsidian



## 插件语法 - Dataview & Dataviewjs

这个有比较全的文档：https://blacksmithgu.github.io/obsidian-dataview/api/data-array/

### 隐式字段

Dataview 会自动为每个页面添加大量元数据： 

- `file.name`：文件标题（字符串）。 
- `file.folder`：该文件所属文件夹的路径。 
- `file.path`：完整的文件路径（字符串）。 
- `file.ext`: 文件类型的扩展名；  通常是“.md”（一个字符串）。 
- `file.link`：文件的链接（链接）。 
- `file.size`：文件的大小（以字节为单位）（一个数字）。 
- `file.ctime`：文件的创建日期（日期+时间）。 
- `file.cday`：文件的创建日期（只是一个日期）。 
- `file.mtime`：文件最后修改的日期（日期+时间）。 
- `file.mday`：文件最后修改的日期（只是一个日期）。 
- `file.tags`：笔记中所有唯一标签的数组。  子标签按每个级别细分，所以 `#Tag/1/A`将存储在   数组为 `[#Tag, #Tag/1, #Tag/1/A]`. 
- `file.etags`：注释中所有显式标签的数组；  不像 `file.tags`, 不包括子标签。 
- `file.inlinks`：指向此文件的所有传入链接的数组。 
- `file.outlinks`：此文件中所有传出链接的数组。 
- `file.aliases`：笔记的所有别名的数组。 
- `file.tasks`：所有任务的数组（即， `- [ ] blah blah blah`) 在这个文件中。 
- `file.lists`：文件中所有列表元素的数组（包括任务）；  这些元素是有效的任务，可以在任务视图中呈现。 
- `file.frontmatter`：包含所有frontmatter的原始值；  主要用于检查原始 frontmatter 值或   用于动态列出 frontmatter 键。 

如果文件的标题中有日期（形式为 `yyyy-mm-dd`或者 `yyyymmdd`)，或者有一个 `Date`field/inline 字段，它还具有以下属性： 

- `file.day`：与文件标题关联的明确日期。 

如果您使用 Obsidian Core 插件“已加星标的文件”，还可以使用以下元数据： 

- `file.starred`：如果此文件已被“星星”黑曜石插件加注星标。 



## 插件语法 - Admonition & Callout

注意：Callout语法是微软Md准则中允许的语法

注意：Obsidian 0.14 在其核心功能中引入了Callout框，使用了与 Microsoft Document Callout 相同的语法
这使得用于警告的Microsoft Document语法过时了，但仍然可以使用警告创建和管理自定义调出类型

通用语法：

```markdown
> [!类型]折叠标记 标题
> 内容
```

使用示例：

```markdown
> [!note]- 这里是标题
> 这里是内容
```

常用类型有：

```shell
note		# 蓝色笔
abstract	# 蓝色书
info		# 蓝色i
tip			# 绿色火
success		# 绿色勾，check
question	# 绿色问号
warning		# 黄色三角感叹号
fail		# 红色叉
error		# 红色闪电，danger
bug			# 红色虫子
example		# 紫色列表
quote		# 灰色引用号，cite
```

折叠标记有：

```shell
	# 什么也不填
+	# 默认展开
-	# 默认折叠
```



## 高级插件：Style Settings





































