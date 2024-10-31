---
tags:
  - 源码
---

# 【NDPI】源码解析之深度包检测分析

参考：https://blog.csdn.net/A_lber_t/article/details/89632412

## 前言

关于nDPI的基本功能就不在这介绍了，有兴趣了解的读者可以阅读官方的快速入门指南：https://github.com/ntop/nDPI/blob/dev/doc/nDPI_QuickStartGuide.pdf，也可以阅读我翻译过来的文章：NDPI快速入门指南（翻译自官方文档）。

nDPI是在OpenDPI基础上扩展的一个库，解决了Opendpi的许多问题，并且具有比较完善的应用层协议识别功能。所以简单来说nDPI就是一个网络协议分析器，可以分析出抓取的流量是什么应用类型，比如来自facebook、ntop、qq还是推特等应用。当然不限于这些它自带的协议分析器，我们同样可以通过向引擎添加自定义的协议分析器，理论上可以分析任何我们想分析的协议。

nDPI源代码在编译后会生成两个部分，第一个部分是通过向Linux内核中的插件netfilter中注册nDPI的协议分析引擎，生成内核层的xt_ndpi.ko模块，用来分析实时的流量信息。编译的另一个结果就是生成了一个应用层的lib库，给ndpiReader这个工具提供一个函数库，可以用来分析抓包工具提供的pcap文件或者底层网卡提供的数据包，这个之后会有一系列文章向大家展示如何使用gdb工具来调试ndpiReader，用来研究ndpiReader分析流量的过程以及它是如何引用nDPI这个库的。

在这个系列呢主要是解读生成内核层模块的源代码，也就是研究这个库是如何进行深度包检测的。下面是正式分析部分：

## nDPI深度包检测流程

## 重要结构体的源码分析

### ndpi_ethdr、ndpi_iphdr、ndpi_tcphdr、ndpi_udphdr

### ndpi_flow_struct

### ndpi_packet_struct

### ndpi_detection_module_struct

## ndpi_api.h 源代码分析及注释

在分析一些工具或者库的源码时，我们不妨先看看它的API文档。

- 在nDPI的快速入门指南中，API文档只有少数的一些函数。
- 但在nDPI的src/include文件夹中，有一个头文件“ndpi_api.h”，里面声明了非常多的函数。

在我们分析其流程之前，可以先分析浏览一下这个头文件中声明的函数，大概搞清楚他们的功能，哪怕是字面意义上，之后在我们分析函数主体时便于我们理解，遇到不清楚的也可以回来查阅，下面我将展示出 “ndpi_api.h” 的源代码，里面有我的一些注释，供大家参考：

```c
/*相关宏定义*/
#ifndef __NDPI_API_H__
#define __NDPI_API_H__
 
#include "ndpi_main.h"
 
#ifdef __cplusplus
extern "C" {
#endif
 
  /* 与nDPI动态链接的app可以通过使用下面的宏定义来确认数据结构，跨版本适配。
  */
#define NDPI_API_VERSION                      1
 
#define SIZEOF_ID_STRUCT                      ( sizeof(struct ndpi_id_struct)   )
#define SIZEOF_FLOW_STRUCT                    ( sizeof(struct ndpi_flow_struct) )
 
#define NDPI_DETECTION_ONLY_IPV4              ( 1 << 0 )
#define NDPI_DETECTION_ONLY_IPV6              ( 1 << 1 )
 
#define ADD_TO_DETECTION_BITMASK              1
#define NO_ADD_TO_DETECTION_BITMASK           0
#define SAVE_DETECTION_BITMASK_AS_UNKNOWN     1
#define NO_SAVE_DETECTION_BITMASK_AS_UNKNOWN  0
 
 
  /**
   *查看字符串是否使用了域名码的编码方式的函数
   * ( https://tools.ietf.org/html/rfc3492 )
   *   参数含义：
   * @par    buff = 指向检查的字符串的指针
   * @par    len  = 字符串长度
   * @return 1 如果这个字符串是域名码;
   *         else 0
   *
   */
  int check_punycode_string(char *buff, int len);
 
 
  /**
   * 获得流结构的长度大小
   *
   * @返回ndpi_flow_struct长度大小
   *
   */
  u_int32_t ndpi_detection_get_sizeof_ndpi_flow_struct(void);
 
 
  /**
   * 获得id struct长度大小
   *
   * @返回其长度大小
   *
   */
  u_int32_t ndpi_detection_get_sizeof_ndpi_id_struct(void);
 
  /**
   * nDPI 分配内存跟释放函数
  **/
  void * ndpi_malloc(size_t size);//动态分配长度为size的内存空间，返回指向这块内存的指针
  void * ndpi_calloc(unsigned long count, size_t size);  //分配内存，初始化，用于存数组
  void * ndpi_realloc(void *ptr, size_t old_size, size_t new_size);//增加内存大小
  char * ndpi_strdup(const char *s);   //拷贝字符串
  void   ndpi_free(void *ptr);//释放内存
  void * ndpi_flow_malloc(size_t size);
  void   ndpi_flow_free(void *ptr);
 
  /**
   * 搜索子字符串第一次出现的地方 -find- in -s-
   * 搜索仅限于字符串的第一个-slen-字符
   *
   * @par    s     = 解析字符串
   * @par    find  = 要与-s匹配的字符串
   * @par    slen  =匹配 -s- and -find-的最大长度
   * @返回一个指针，指向定位到的子字符串;
   *        返回空指针则表示子字符串未找到
   *
   */
  char* ndpi_strnstr(const char *s, const char *find, size_t slen);
 
 
 
  /**
   * 与 ndpi_strnstr函数功能相似但是不区分大小写
   *
   * @par    s     =解析的字符串
   * @par    find  = 要与 -s-匹配的字符串
   * @par    slen  = max length to match between -s- and -find-
   * @返回一个指针，指向定位到的子字符串;
   *        返回空指针则表示子字符串未找到
   *
   */
  char* ndpi_strncasestr(const char *s, const char *find, size_t slen);
 
 
 
  /**
   *返回nDPI协议ID用于基于IP的协议检测
   *
   * @par    ndpi_struct  = 创建这个结构体用于协议检测
   * @par    pin          =IP主机地址（必须按网络字节顺序）：
   *详情见Man（7）IP
   * @返回nDPI协议ID
   *
   */
  u_int16_t ndpi_network_ptree_match(struct ndpi_detection_module_struct *ndpi_struct,struct in_addr *pin);
 
  /**
   * 初始化单个协议的匹配
   *
   * @par ndpi_mod  = 创建这个结构体用于协议检测
   * @par match     = 结构传递进函数，用于协议匹配
   *
   */
  void ndpi_init_protocol_match(struct ndpi_detection_module_struct *ndpi_mod,
				ndpi_protocol_match *match);
 
  /**
   * 模块初始化函数，返回一个新的初始化过的检测模块
   *
   * @返回一个初始化的检测检测模块
   *
   */
  struct ndpi_detection_module_struct *ndpi_init_detection_module(void);
 
  /**
   * 释放指定流中分配的内存
   *
   * @par flow  = 需要被释放内存的流
   *
   */
  void ndpi_free_flow(struct ndpi_flow_struct *flow);
 
  /**
   *使能存储器支持.
   * In nDPI is used for some protocol用于支持一些协议 (i.e. Skype)
   *
   * @par ndpi_mod  =用于协议检测的结构体
   * @par host      = 域（主机）名字符串
   * @par port      = 端口名（无符号整型）
   *
   */
  void ndpi_enable_cache(struct ndpi_detection_module_struct *ndpi_mod,
			 char* host, u_int port);
 
  /**
   * 清除检测模块
   *
   * @par ndpi_struct  = 需要清除的检测模块
   *
   */
  void ndpi_exit_detection_module(struct ndpi_detection_module_struct *ndpi_struct);
 
  /**
   * 设置单个协议的位掩码
   * 此函数不会增加回调缓冲区的索引
   *
   * @par label                    = 协议名字符串
   * @par ndpi_struct              = 检测模块
   * @par detection_bitmask        = 检测位掩码
   * @par idx                      = 每个协议的回调函数的索引
   * @par func                     = 协议搜索的函数指针
   * @par ndpi_selection_bitmask   = 被选择的位掩码
   * @par b_save_bitmask_unknow    = 如果被设置为“true”，将检测的位掩码保存为unknown
   * @par b_add_detection_bitmask  = 如果被设置为“true”添加这个协议的bitmask到detection bitmask中
   *
   */
  void ndpi_set_bitmask_protocol_detection(char *label,
					   struct ndpi_detection_module_struct *ndpi_struct,
					   const NDPI_PROTOCOL_BITMASK *detection_bitmask,
					   const u_int32_t idx,
					   u_int16_t ndpi_protocol_id,
					   void (*func) (struct ndpi_detection_module_struct *,
							 struct ndpi_flow_struct *flow),
					   const NDPI_SELECTION_BITMASK_PROTOCOL_SIZE ndpi_selection_bitmask,
					   u_int8_t b_save_bitmask_unknow,
					   u_int8_t b_add_detection_bitmask);
 
  /**
   *设置协议的 bitmask2
   *
   * @par ndpi_struct        =检测模块
   * @par detection_bitmask  = the protocol bitmask to set
   *
   */
  void ndpi_set_protocol_detection_bitmask2(struct ndpi_detection_module_struct *ndpi_struct,const NDPI_PROTOCOL_BITMASK * detection_bitmask);
  
  /**
   * 在未知匹配的情况下要调用的函数，以查看当前ndpi首选项配置是否阻止了部分匹配
   *
   * @par    ndpi_struct  = 检测模块
   * @par    flow         = 检测模块检测的流
   * 即使流不是完整的，也返回检测到的协议;
   *
   */
  ndpi_protocol ndpi_get_partial_detection(struct ndpi_detection_module_struct *ndpi_struct,
                struct ndpi_flow_struct *flow);
  /**
   *  在放弃对给定流的检测之前要调用的函数
   *  这个函数减少了对NDPI_UNKNOWN_PROTOCOL未知协议的检测
   *
   * @par    ndpi_struct  = the detection module
   * @par    flow         = the flow given for the detection module
   * @par    enable_guess = 如果协议未知，猜测协议
   * @即使流不是完整的，也返回检测到的协议
   *
   */
  ndpi_protocol ndpi_detection_giveup(struct ndpi_detection_module_struct *ndpi_struct,
				      struct ndpi_flow_struct *flow,
				      u_int8_t enable_guess);
 
  /**
   * 处理一个额外的数据包，以便获得给定协议的更多信息
   * (就像ssl获取客户端和服务器证书一样，即使在看到客户端证书之后我们已经知道这个协议是什么。)
   *
   * @par    ndpi_struct   = the detection module
   * @par    flow          = pointer to the connection state machine指向连接状态机的指针。
   * @par    packet        = unsigned char pointer to the Layer 3 (IP header)
   * @par    packetlen     = 数据包长度
   * @par    current_tick  = 包的时间戳
   * @par    src           = pointer to the source subscriber state machine
   *                          指向源订阅状态机
   * @par    dst           = pointer to the destination subscriber state machine
   *                          指向目的订阅状态机
   * @return void
   *
   */
  void ndpi_process_extra_packet(struct ndpi_detection_module_struct *ndpi_struct,
				 struct ndpi_flow_struct *flow,
				 const unsigned char *packet,
				 const unsigned short packetlen,
				 const u_int64_t current_tick,
				 struct ndpi_id_struct *src,
				 struct ndpi_id_struct *dst);
 
  /**
   * 处理一个数据包，并且返回检测到的协议ID
   * This is the MAIN PACKET PROCESSING FUNCTION.
   *            主要的包处理函数，很重要，之后我们会分析到
   * @par    ndpi_struct   = the detection module
   * @par    flow          = pointer to the connection state machine指向连接状态机的指针
   * @par    packet        = unsigned char pointer to the Layer 3 (IP header)
   * @par    packetlen     = the length of the packet
   * @par    current_tick  = the current timestamp for the packet
   * @par    src           = pointer to the source subscriber state machine
   * @par    dst           = pointer to the destination subscriber state machine
   * @return the detected ID of the protocol
   *
   */
  ndpi_protocol ndpi_detection_process_packet(struct ndpi_detection_module_struct *ndpi_struct,
					      struct ndpi_flow_struct *flow,
					      const unsigned char *packet,
					      const unsigned short packetlen,
					      const u_int64_t current_tick,
					      struct ndpi_id_struct *src,
					      struct ndpi_id_struct *dst);
  /**
   * 获取检测模块检测到传递流的主协议
   *
   *
   * @par    ndpi_struct  = the detection module
   * @par    flow         = the flow given for the detection module
   * @return the ID of the master protocol detected主协议
   *
   */
  u_int16_t ndpi_get_flow_masterprotocol(struct ndpi_detection_module_struct *ndpi_struct,
					 struct ndpi_flow_struct *flow);
  
  /**
   *ndpi_detection_process_packet函数或应用程序在内部调用的API calls
   * 希望避免调用ndpi_detection_process_packet函数，因为它们已经解析了数据包，因此希望避免这种情况，这说明app在外部并不能调用ndpi_detection_process_packet函数来处理数据包
   *
   *
   * @par    ndpi_struct              = the detection module
   * @par    flow                     = the flow given for the detection module
   * @par    ndpi_selection_bitmask   = the protocol selected bitmask
   *
   */
  void ndpi_check_flow_func(struct ndpi_detection_module_struct *ndpi_struct,
			    struct ndpi_flow_struct *flow,
			    NDPI_SELECTION_BITMASK_PROTOCOL_SIZE *ndpi_selection_packet);
 
  /**
   * 查询指向第4层数据包的指针
   *
   * @par    l3 = pointer to the layer 3 data
   * @par    l3_len = length of the layer 3 data
   * @par    l4_return = address to the pointer of the layer 4 data if return value == 0, else undefined 如果返回值=0，则指向第4层数据指针的地址，否则未定义
   * @par    l4_len_return = length of the layer 4 data if return value == 0, else undefined
   * @par    l4_protocol_return = protocol of the layer 4 data if return value == 0, undefined otherwise
   * @par    flags = limit operation on ipv4 or ipv6 packets. Possible values: NDPI_DETECTION_ONLY_IPV4 - NDPI_DETECTION_ONLY_IPV6 - 0 (any)限制IPV4或者IPV6
   * @return 0 if layer 4 data could be found correctly; 正确找到了第四层数据，返回0，否则不返回0
             else != 0
   *
   */
  u_int8_t ndpi_detection_get_l4(const u_int8_t *l3, u_int16_t l3_len, const u_int8_t **l4_return, u_int16_t *l4_len_return,
				 u_int8_t *l4_protocol_return, u_int32_t flags);
 
  /**
   * 根据匹配的端口搜索并返回协议
   *
   * @par    ndpi_struct  = the detection module
   * @par    shost        = source address in host byte order 主机字节顺序的源地址
   * @par    sport        = source port number
   * @par    dhost        = destination address in host byte order
   * @par    dport        = destination port number
   * @return the struct ndpi_protocol that match the port base protocol
   * 注意此处返回的是一个结构ndpi_protocol
   */
  ndpi_protocol ndpi_find_port_based_protocol(struct ndpi_detection_module_struct *ndpi_struct/* , u_int8_t proto */,
					      u_int32_t shost,
					      u_int16_t sport,
					      u_int32_t dhost,
					      u_int16_t dport);
  /**
   * Search and return the protocol guessed that is undetected
   *  搜索并返回未检测出但是被猜测的协议
   * @par    ndpi_struct  = the detection module
   * @par    flow         = the flow we're trying to guess, NULL if not available需要猜测的流
   * @par    proto        = the l4 protocol number
   * @par    shost        = source address in host byte order
   * @par    sport        = source port number
   * @par    dhost        = destination address in host byte order
   * @par    dport        = destination port number
   * @return the struct ndpi_protocol that match the port base protocol
   *
   */
  ndpi_protocol ndpi_guess_undetected_protocol(struct ndpi_detection_module_struct *ndpi_struct,
					       struct ndpi_flow_struct *flow,
					       u_int8_t proto,
					       u_int32_t shost,
					       u_int16_t sport,
					       u_int32_t dhost,
					       u_int16_t dport);
 
 
  /**下面三个函数对应了三个方法，检测子协议**/
  /*
   *检查传递的字符串是否与协议匹配， 用于子协议的检测
   *
   * @par    ndpi_struct         = the detection module
   * @par    string_to_match     = the string to match
   * @par    string_to_match_len = the length of the string
   * @par    ret_match           = completed returned match information
   * @par    is_host_match       = value of the second field of struct ndpi_automa
   * @return the ID of the matched subprotocol 返回匹配的子协议ID
   *
   */
  int ndpi_match_string_subprotocol(struct ndpi_detection_module_struct *ndpi_struct,
				    char *string_to_match,
				    u_int string_to_match_len,
				    ndpi_protocol_match_result *ret_match,
				    u_int8_t is_host_match);
  /**
   * 检查传递的域名（主机）是否与协议匹配
   *
   * @par    ndpi_struct         = the detection module
   * @par    flow                = the flow where match the host
   * @par    string_to_match     = the string to match 匹配的字符串
   * @par    string_to_match_len = the length of the string
   * @par    ret_match           = completed returned match information 匹配结果信息
   * @par    master_protocol_id  = value of the ID associated to the master protocol detected    主协议ID
   * @return the ID of the matched subprotocol  返回子协议ID
   *
   */
  int ndpi_match_host_subprotocol(struct ndpi_detection_module_struct *ndpi_struct,
				  struct ndpi_flow_struct *flow,
				  char *string_to_match,
				  u_int string_to_match_len,
				  ndpi_protocol_match_result *ret_match,
				  u_int16_t master_protocol_id);
 
 
  /**
   * 检查传递的字符串内容是否与协议匹配
   *
   * @par    ndpi_struct         = the detection module
   * @par    flow                = the flow where match the host
   * @par    string_to_match     = the string to match
   * @par    string_to_match_len = the length of the string
   * @par    ret_match           = completed returned match information
   * @par    master_protocol_id  = value of the ID associated to the master protocol detected
   * @return the ID of the matched subprotocol
   *
   */
  int ndpi_match_content_subprotocol(struct ndpi_detection_module_struct *ndpi_struct,
				     struct ndpi_flow_struct *flow,
				     char *string_to_match,
				     u_int string_to_match_len,
				     ndpi_protocol_match_result *ret_match,
				     u_int16_t master_protocol_id);
 
 
  /**
   * 从搜索中排除协议
   *
   * @par    ndpi_struct         = the detection module
   * @par    flow                = the flow where match the host
   * @par    master_protocol_id  = value of the ID associated to the master protocol detected
   *
   */
  void ndpi_exclude_protocol(struct ndpi_detection_module_struct *ndpi_struct,
				  struct ndpi_flow_struct *flow,
				  u_int16_t master_protocol_id,
				  const char *_file, const char *_func,int _line);
  /**
   *检查字符串-bigram-to-u是否匹配-automa的bigram- 双字节匹配
   *
   * @par     ndpi_mod         = the detection module
   * @par     automa           = the struct ndpi_automa for the bigram
   * @par     bigram_to_match  = the bigram string to match
   * @return  0
   *
   */
  int ndpi_match_bigram(struct ndpi_detection_module_struct *ndpi_mod,
			ndpi_automa *automa,
			char *bigram_to_match);
 
  /**
   * Write the protocol name in the buffer -buf- as master_protocol.protocol
   *在数组-buf- as master_protocol.protocol中写入协议名
   * @par     ndpi_mod      = the detection module
   * @par     proto         = the struct ndpi_protocol contain the protocols name
   * @par     buf           = the buffer to write the name of the protocols
   * @par     buf_len       = the length of the buffer
   * @return  the buffer contains the master_protocol and protocol name
   *
   */
  char* ndpi_protocol2name(struct ndpi_detection_module_struct *ndpi_mod,
			   ndpi_protocol proto, char *buf, u_int buf_len);
 
  /**
   * Same as ndpi_protocol2name() with the difference that the numeric protocol
   * name is returned  
   * 返回数字协议名
   * @par     ndpi_mod      = the detection module
   * @par     proto         = the struct ndpi_protocol contain the protocols name
   * @par     buf           = the buffer to write the name of the protocols
   * @par     buf_len       = the length of the buffer
   * @return  the buffer contains the master_protocol and protocol name
   *
   */
  char* ndpi_protocol2id(struct ndpi_detection_module_struct *ndpi_mod,
			 ndpi_protocol proto, char *buf, u_int buf_len);
 
  /**
   * 找出给定的类别是否是自定义/用户定义的
   *
   * @par     category      = the category associated to the protocol
   * @return  1 if this is a custom user category, 0 otherwise
   * 如果是自定义则返回1
   */
  int ndpi_is_custom_category(ndpi_protocol_category_t category);
 
  /**
   * 用自定义类型覆盖由NDPI定义的协议类型
   *
   * @par     ndpi_mod      = the detection module
   * @par     protoId       = the protocol identifier to overwrite 用于覆盖的协议分析器
   * @par     breed         = the breed to be associated to the protocol
   *
   */
  void ndpi_set_proto_breed(struct ndpi_detection_module_struct *ndpi_mod,
			    u_int16_t protoId, ndpi_protocol_breed_t breed);
 
  /**
   * 用自定义类别覆盖由NDPI定义的协议类别
   *
   * @par     ndpi_mod      = the detection module
   * @par     protoId       = the protocol identifier to overwrite
   * @par     category      = the category associated to the protocol
   *
   */
  void ndpi_set_proto_category(struct ndpi_detection_module_struct *ndpi_mod,
			       u_int16_t protoId, ndpi_protocol_category_t protoCategory);
 
  /**
   * 检查指定主协议的子协议是否只是信息性的（而不是真实的）
   *
   * @par     mod           = the detection module
   * @par     protoId       = the (master) protocol identifier to query
   * @return  1 = the subprotocol is informative, 0 otherwise.
   *
   */
  u_int8_t ndpi_is_subprotocol_informative(struct ndpi_detection_module_struct *ndpi_mod,
					   u_int16_t protoId);
 
  /**
   * 将协议类别作为字符串获取
   *
   * @par     mod           = the detection module
   * @par     category      = the category associated to the protocol
   * @return  the string name of the category
   *
   */
  const char* ndpi_category_get_name(struct ndpi_detection_module_struct *ndpi_mod,
				     ndpi_protocol_category_t category);
 
  /**
   * 设置协议类别字符串
   *
   * @par     mod           = the detection module
   * @par     category      = the category associated to the protocol
   * @paw     name          = the string name of the category
   *
   */
  void ndpi_category_set_name(struct ndpi_detection_module_struct *ndpi_mod,
			      ndpi_protocol_category_t category, char *name);
 
  /**
   * 获得协议种类
   *
   * @par     ndpi_mod      = the detection module
   * @par     proto         = the struct ndpi_protocol contain the protocols name
   * @return  the protocol category
   */
  ndpi_protocol_category_t ndpi_get_proto_category(struct ndpi_detection_module_struct *ndpi_mod,
						   ndpi_protocol proto);
 
  /**
   * 获取与ID关联的协议名
   *
   * @par     mod           = the detection module
   * @par     proto_id      = the ID of the protocol
   * @return  the buffer contains the master_protocol and protocol name
   *
   */
  char* ndpi_get_proto_name(struct ndpi_detection_module_struct *mod, u_int16_t proto_id);
 
 
  /**
   * 返回与协议相关联的协议类型ID
   *
   * @par     ndpi_struct   = the detection module
   * @par     proto         = the ID of the protocol
   * @return  the breed ID associated to the protocol
   *
   */
  ndpi_protocol_breed_t ndpi_get_proto_breed(struct ndpi_detection_module_struct *ndpi_struct,
					     u_int16_t proto);
 
  /**
   * Return the string name of the protocol breed
   *返回协议类型的字符串名
   * @par     ndpi_struct   = the detection module
   * @par     breed_id      = the breed ID associated to the protocol
   * @return  the string name of the breed ID
   *
   */
  char* ndpi_get_proto_breed_name(struct ndpi_detection_module_struct *ndpi_struct,
				  ndpi_protocol_breed_t breed_id);
 
  /**
   * Return the ID of the protocol返回协议ID，整型
   *
   * @par     ndpi_mod   = the detection module
   * @par     proto      = the protocol name
   * @return  the ID of the protocol
   *
   */
  int ndpi_get_protocol_id(struct ndpi_detection_module_struct *ndpi_mod, char *proto);
 
  /**
   * Return the ID of the category返回类型ID
   *
   * @par     ndpi_mod   = the detection module
   * @par     proto      = the category name
   * @return  the ID of the category
   *
   */
  int ndpi_get_category_id(struct ndpi_detection_module_struct *ndpi_mod, char *cat);
 
  /**
   * 生成子协议列表Write the list of the supported protocols
   *
   * @par  ndpi_mod = the detection module
   */
  void ndpi_dump_protocols(struct ndpi_detection_module_struct *mod);
 
  /**
   * 读文件加载协议 Read a file and load the protocols
   *
   * Format: <tcp|udp>:<port>,<tcp|udp>:<port>,.....@<proto>
   *
   * Example:
   * tcp:80,tcp:3128@HTTP
   * udp:139@NETBIOS
   *
   * @par     ndpi_mod = the detection module
   * @par     path     = the path of the file
   * @return  0 if the file is loaded correctly;
   *          -1 else
   *
   */
  int ndpi_load_protocols_file(struct ndpi_detection_module_struct *ndpi_mod,
			       const char* path);
 
  /**
   * 获得子协议的总数Get the total number of the supported protocols
   *
   * @par     ndpi_mod = the detection module
   * @return  the number of protocols
   *
   */
  u_int ndpi_get_num_supported_protocols(struct ndpi_detection_module_struct *ndpi_mod);
 
  /**
   * Get the nDPI version release 获取 nDPI 版本
   *
   * @return the NDPI_GIT_RELEASE
   *
   */
  char* ndpi_revision(void);
 
  /**
   * 为协议搜索设置自动匹配 Set the automa for the protocol search 
   *
   * @par ndpi_struct = the detection module
   * @par automa      = the automa to match
   *
   */
  void ndpi_set_automa(struct ndpi_detection_module_struct *ndpi_struct,
		       void* automa);
 
/* NDPI_PROTOCOL_HTTP */
  /**
   * 检索HTTP流的信息
   *
   * @par     ndpi_mod = the detection module
   * @par     flow     = the detected flow
   * @return  the HTTP method information about the flow
   *
  */
  ndpi_http_method ndpi_get_http_method(struct ndpi_detection_module_struct *ndpi_mod,
					struct ndpi_flow_struct *flow);
 
  /**
   * Get the HTTP url 获取HTTP URL
   *
   * @par     ndpi_mod = the detection module
   * @par     flow     = the detected flow
   * @return  the HTTP method information about the flow
   *
  */
  char* ndpi_get_http_url(struct ndpi_detection_module_struct *ndpi_mod,
			  struct ndpi_flow_struct *flow);
 
  /**
   * Get the HTTP content-type  内容类型
   *
   * @par     ndpi_mod = the detection module
   * @par     flow     = the detected flow
   * @return  the HTTP method information about the flow
   *
  */
  char* ndpi_get_http_content_type(struct ndpi_detection_module_struct *ndpi_mod,
				   struct ndpi_flow_struct *flow);
 
/* NDPI_PROTOCOL_TOR */
  /**
   * 检查流是否可以作为Tor协议检测到Check if the flow could be detected as TOR protocol
   *
   * @par     ndpi_struct = the detection module
   * @par     flow = the detected flow
   * @par     certificate = the ssl certificate
   * @return  1 if the flow is TOR;
   *          0 else
   *
   */
  int ndpi_is_ssl_tor(struct ndpi_detection_module_struct *ndpi_struct,
		      struct ndpi_flow_struct *flow, char *certificate);
 
  /* Wrappers functions */
  /**
   * Init Aho-Corasick automata  初始化AC自动机
   *
   * @return  The requested automata, or NULL if an error occurred
   *
   */
  void* ndpi_init_automa(void);
 
 
 /**
   * Free Aho-Corasick automata allocated with ndpi_init_automa();
   *
   * @par     The automata initialized with ndpi_init_automa();
   *
   */
  void ndpi_free_automa(void *_automa);
 
  /**
   * Add a string to match to an automata
   *
   * @par     The automata initialized with ndpi_init_automa();
   * @par     The (sub)string to search
   * @par     The number associated with this string
   * @return  0 in case of no error, or -1 if an error occurred.
   *
   */
  int ndpi_add_string_value_to_automa(void *_automa, char *str, unsigned long num);
 
  /**
   * Add a string to match to an automata. Same as ndpi_add_string_value_to_automa() with num set to 1
   *
   * @par     The automata initialized with ndpi_init_automa();
   * @par     The (sub)string to search
   * @return  0 in case of no error, or -1 if an error occurred.
   *
   */
  int ndpi_add_string_to_automa(void *_automa, char *str);
 
  /**
   * Finalize the automa (necessary before start searching)开始搜索必须设置好自动机
   *
   * @par     The automata initialized with ndpi_init_automa();
   *
   */
  void ndpi_finalize_automa(void *_automa);
 
  /** 
   * Add a string to match to an automata  添加与自动机匹配的字符串
   *
   * @par     The automata initialized with ndpi_init_automa();
   * @par     The (sub)string to search
   * @return  0 in case of match, or -1 if no match, or -2 if an error occurred.
   *
   */
  int ndpi_match_string(void *_automa, char *string_to_match);
 
  void ndpi_load_ip_category(struct ndpi_detection_module_struct *ndpi_struct,
			     char *ip_address_and_mask, ndpi_protocol_category_t category);
  int ndpi_load_hostname_category(struct ndpi_detection_module_struct *ndpi_struct,
				  char *name, ndpi_protocol_category_t category);
  int ndpi_enable_loaded_categories(struct ndpi_detection_module_struct *ndpi_struct);
  int ndpi_fill_ip_protocol_category(struct ndpi_detection_module_struct *ndpi_struct,
				 u_int32_t saddr,
				 u_int32_t daddr,
				 ndpi_protocol *ret);
  int ndpi_match_custom_category(struct ndpi_detection_module_struct *ndpi_struct,
				      char *name, unsigned long *id);
  void ndpi_fill_protocol_category(struct ndpi_detection_module_struct *ndpi_struct,
				   struct ndpi_flow_struct *flow,
				   ndpi_protocol *ret);
  int ndpi_get_custom_category_match(struct ndpi_detection_module_struct *ndpi_struct,
				      char *name_or_ip, unsigned long *id);
  int ndpi_set_detection_preferences(struct ndpi_detection_module_struct *ndpi_mod,
				     ndpi_detection_preference pref,
				     int value);
 
  ndpi_proto_defaults_t* ndpi_get_proto_defaults(struct ndpi_detection_module_struct *ndpi_mod);
  u_int ndpi_get_ndpi_num_supported_protocols(struct ndpi_detection_module_struct *ndpi_mod);
  u_int ndpi_get_ndpi_num_custom_protocols(struct ndpi_detection_module_struct *ndpi_mod);
  u_int ndpi_get_ndpi_detection_module_size();
  void ndpi_set_log_level(struct ndpi_detection_module_struct *ndpi_mod, u_int l);
 
  /* LRU cache */
  struct ndpi_lru_cache* ndpi_lru_cache_init(u_int32_t num_entries);
  void ndpi_lru_free_cache(struct ndpi_lru_cache *c);
  u_int8_t ndpi_lru_find_cache(struct ndpi_lru_cache *c, u_int32_t key, u_int8_t clean_key_when_found);
  void ndpi_lru_add_to_cache(struct ndpi_lru_cache *c, u_int32_t key);
  
  /**
   * Add a string to match to an automata  //ID字符串
   *
   * @par     The automata initialized with ndpi_init_automa();
   * @par     The (sub)string to search
   * @par     The id associated with the matched string or 0 id not found.
   * @return  0 in case of match, or -1 if no match, or -2 if an error occurred.
   *
   */
  int ndpi_match_string_id(void *_automa, char *string_to_match, unsigned long *id);
 
  /* Utility functions to set ndpi malloc/free/print wrappers
    *设置ndpi malloc/free/print wrappers的实用程序函数 */
  void set_ndpi_malloc(void* (*__ndpi_malloc)(size_t size));
  void set_ndpi_free(void  (*__ndpi_free)(void *ptr));
  void set_ndpi_flow_malloc(void* (*__ndpi_flow_malloc)(size_t size));
  void set_ndpi_flow_free(void  (*__ndpi_flow_free)(void *ptr));
  void set_ndpi_debug_function(struct ndpi_detection_module_struct *ndpi_str,
			       ndpi_debug_function_ptr ndpi_debug_printf);
  void * ndpi_malloc(size_t size);
  void * ndpi_calloc(unsigned long count, size_t size);
  void ndpi_free(void *ptr);
  u_int8_t ndpi_get_api_version();
 
  /* https://github.com/corelight/community-id-spec */
  int ndpi_flowv4_flow_hash(u_int8_t l4_proto, u_int32_t src_ip, u_int32_t dst_ip, u_int16_t src_port, u_int16_t dst_port,
			    u_int8_t icmp_type, u_int8_t icmp_code, u_char *hash_buf, u_int8_t hash_buf_len);
  int ndpi_flowv6_flow_hash(u_int8_t l4_proto, struct ndpi_in6_addr *src_ip, struct ndpi_in6_addr *dst_ip,
			    u_int16_t src_port, u_int16_t dst_port, u_int8_t icmp_type, u_int8_t icmp_code,
			    u_char *hash_buf, u_int8_t hash_buf_len);
  
#ifdef __cplusplus
}
#endif
 
#endif	/* __NDPI_API_H__ */
```

文件中声明的函数非常多，很多函数也许现在并不是很理解其功能，但是我们会在今后一步一步来分析它们，而且这些函数声明中有很多参数都是我们上一篇文章中分析的重要结构体，所以在阅读函数主体之前我们应该熟悉掌握这些重要的结构体。之后的函数分析则会根据nDPI的工作流程来逐步分析所用到的函数及其功能。





















