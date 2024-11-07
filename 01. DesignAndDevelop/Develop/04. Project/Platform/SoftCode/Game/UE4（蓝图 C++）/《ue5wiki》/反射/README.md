# README

原文：https://ue5wiki.com/wiki/12624/

## UE 反射实现分析：基础概念

**反射**，是指程序在运行时进行自检的的能力，在编辑器的属性面板、序列化、GC 等方面非常有用。但是 C++ 语言本身不支持反射特性，UE 在 C++ 的语法基础上通过 UHT 实现了反射信息的生成，从而实现了运行时的反射的目的。

在之前的文章中，有一些涉及到 UE 的构建系统和反射相关的内容。

涉及了 UE 的构建系统文章：

- [Build flow of the Unreal Engine4 project](https://imzlp.com/posts/6362/)
- [UE4 Build System: Target and Module](https://img.imzlp.com/imgs/zlp/blog/posts/16643/)
- [UEC++ 与标准 C++ 的区别与联系](https://imzlp.com/posts/20425/)

基于 UE 的反射机制来做一些奇淫巧技的文章：

- [UE4：Hook UObject](https://imzlp.com/posts/15049/)

UE 的反射实现是依赖于构建系统中 UHT 来执行代码生成的，本篇文章对 UE 的反射做一个基础概念介绍，后续会花几篇文章完整地介绍 UE 里反射的实现机制。

UE 的反射可以实现 Enum 的反射 (`UEnum`)、类反射(`UClass`)、结构反射(`UStruct`)、数据成员反射(`UProperty`/`FProperty`)、成员函数反射(`UFunction`)，可以在运行时访问到它们，其实反射被称作 **属性系统** 应该更合适。

可以根据这些反射信息来获取它们的类型信息，本篇文章以类反射为例子介绍一下 UE 的反射。

如以下纯 C++ 代码：

```cpp
class ClassRef  
{  
public:  
    int32 ival = 666;  
    bool func(int32 InIval){ return false;}  
};
```

想要在运行时获取 `ClassRef` 类有哪些数据成员、函数，要如何操作？

C++ 原生并没有提供这样的能力，相同的需求在 UE 中创建的类是以下形式：

```cpp
#pragma once  
#include "CoreMinimal.h"  
#include "RefObject.generated.h"  
  
UCLASS()  
class REF_API URefObject : public UObject  
{  
	GENERATED_BODY()  
public:  
	UPROPERTY()  
	int32 ival = 666;  
	  
	UFUNCTION()  
	bool func(int32 InIval)  
	{  
    	UE_LOG(LogTemp,Log,TEXT("Function func: %d"),InIval);  
    	return true;  
	}  
};
```

其中关键需要注意的点：

1. `RefObject.generated.h`文件
2. UCLASS 标记
3. GENERATED_BODY 标记
4. UPROPERTY 标记
5. UFUNCTION 标记

本文不对它们的具体含义做过多的介绍，后续的文章会做详细的分析。

`UCLASS`/`USTRUCT`/`UFUNCTION`/`UPROPERTY`等可以在 `()` 中添加很多的标记值以及 meta 参数，用于指导 UHT 来生成对应的反射代码，它们支持的参数可以在 UE 的文档中查看：

- [Class Specifiers](https://docs.unrealengine.com/en-US/Programming/UnrealArchitecture/Reference/Classes/Specifiers)
- [Struct Specifiers](https://docs.unrealengine.com/en-US/ProgrammingAndScripting/GameplayArchitecture/Structs/Specifiers/index.html)
- [Function Specifiers](https://docs.unrealengine.com/en-us/Programming/UnrealArchitecture/Reference/Functions/Specifiers)
- [Property Specifiers](https://docs.unrealengine.com/en-US/ProgrammingAndScripting/GameplayArchitecture/Properties/Specifiers/index.html)
- [Metadata Specifiers](https://docs.unrealengine.com/en-US/ProgrammingAndScripting/GameplayArchitecture/Metadata/index.html)

这种通过添加的 **代码标记** 来告诉 UE 的构建系统，由 UHT 来生成反射的代码，反射的代码保存在 `gen.cpp` 中，注意这些反射标记 **只是** 用来告诉 UHT 来生成代码的，在经过 C++ 的预处理阶段后它们大多都是空宏（有些是真的 C++ 宏），这也导致 UE 的反射标记有一个缺点：无法使用 C++ 的宏来包裹 UE 的反射标记，因为它们先于 **预处理** 执行。

> 而且，UHT 只是简单粗暴的关键字匹配硬扫描，限制很大。

对于继承自 UObject 的类而言，它的反射信息被创建出了一个 UClass 对象，可以通过这个对象在运行时获取对象类型的信息。并且，类内部的 **反射数据成员** 和**反射成员函数** ，都会给生成对应的`FProperty` 和`UFunction`对象，用来运行时访问到它们。

UClass 的继承关系：

```
UObjectBase
  UObjectBaseUtility
    UObject
      UField
        UStruct
          UClass
```

针对继承自 UObject 的类，可以通过 `GetClass()` 来获取 UClass 实例，但是如果想直接获取某个类型的 UClass，则可以通过 `StaticClass<UObject>` 或者 `UObject::StaticClass()` 来获取。

UClass 中记录这类的继承关系、实现的接口、各种 Flag 等等，具体可以直接查阅 UClass 的类定义，通过它可以访问到该 UObject 的 C++ 类型中的信息。

而且，在运行时可以通过 `TFieldIterator` 来遍历 UClass 中的反射属性：

```cpp
URefObject::URefObject(const FObjectInitializer& Initializer):Super(Initializer)  
{  
    for(TFieldIterator<FProperty> PropertyIter(GetClass());PropertyIter;++PropertyIter)  
    {  
        FProperty* PropertyIns = *PropertyIter;  
        UE_LOG(LogTemp,Log,TEXT("Property Name: %s"),*PropertyIns->GetName());  
    }  
    for(TFieldIterator<UFunction> PropertyIter(GetClass());PropertyIter;++PropertyIter)  
    {  
        UFunction* PropertyIns = *PropertyIter;  
        UE_LOG(LogTemp,Log,TEXT("Function Name: %s"),*PropertyIns->GetName());  
    }  
}
```

执行结果：

```bash
LogTemp: Property Name: ival  
LogTemp: Function Name: func  
LogTemp: Function Name: ExecuteUbergraph
```

那么如何通过属性和成员函数的反射信息来访问到它们呢？

### 访问数据成员

首先，在 C++ 中类内存布局中是编译时固定的，所以一个数据成员在类中的位置是固定的，C++ 有一个特性叫做 **指向类成员的指针**，本质上就是描述了当前数据成员在类布局内的偏移值。这部分内容在我之前的文章中有介绍：[C++ 中指向类成员的指针并非指针](https://imzlp.com/posts/27615/)。

FProperty 做的就是类似的事情，记录反射数据成员的类内偏移信息，UE 中的实现也是通过 **指向成员的指针** 来实现的，这部分后面的文章会着重介绍，这里只介绍使用方法。

通过 FProperty 获取对象中值的方式，需要通过调用 `FProperty` 的`ContainerPtrToValuePtr`来实现：

```cpp
for(TFieldIterator<FProperty> PropertyIter(GetClass());PropertyIter;++PropertyIter)
{
    FProperty* PropertyIns = *PropertyIter;
    if(PropertyIns->GetName().Equals(TEXT("ival")))
    {
        int32* i32 = PropertyIns->ContainerPtrToValuePtr<int32>(this);            
        UE_LOG(LogTemp,Log,TEXT("Property %s value is %d"),*PropertyIns->GetName(),*i32);
    }
}
```

![](https://img.imzlp.com/imgs/zlp/blog/posts/12624/fproperty-get-data-member-value.webp)

这样就实现了通过 FProperty 来访问数据成员的目的，因为获取到的是数据成员的指针，所以修改它也是没问题的。

### 访问成员函数

通过反射访问函数则要复杂一些，因为要处理参数传递和返回值的接收问题。

前面已经提到了，UE 的反射成员函数会生成 `UFunction` 对象，函数的反射信息就在它里面，因为 UFUNCTION 是只能标记在继承自 UObject 的类中，所以 UE 封装了一套基于 UObject 的反射函数调用方式：

……

……

……
