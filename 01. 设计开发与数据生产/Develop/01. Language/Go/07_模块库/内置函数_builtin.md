# 内置函数_builtin

特点：无需导包，或者说默认强制导包。如果需要查文档，对应的包是 `builtin`

## 常用

- len
- new
- make

```go
// 返回v的长度，取决于类型
// - 数组：v中元素数量
// - 数组指针:*v中元素的数量
// - 切片、映射：v中元素的数量，若v为nil则len(v)为0
// - 字符串：v中字节数量 (按字节)
// - 通道：通道缓存中队列(未读取)元素的数量
func len(v Type) int
count := len(str)

// 分配内存，第一个参数是类型而非值，返回指针
func new(Type) *Type
num := new(int)			//     返回int*

// 分配内存，主要用来分配引用类型 (指针、slice切片、map、管道chan、interface 等)
// - 切片：size长度，切片容量等于长度。make([]int, 0, 10) 会分配一个长度0容量10的切片
// - 映射：初始大小取决于size，若长度为0可省略size
// - 通道
func make(Type, size IntegerType) Type
```





















