### 支持三种拆包方式

```cpp
int hio_unpack(hio_t* io, void* buf, int readbytes); // 自动选择三种方式的其中一种拆包  
int hio_unpack_by_fixed_length(hio_t* io, void* buf, int readbytes); // 固定长度拆包  
int hio_unpack_by_delimiter(hio_t* io, void* buf, int readbytes); // 定界符拆包  
int hio_unpack_by_length_field(hio_t* io, void* buf, int readbytes); // 按长度字段拆包
```

### 先来看最简单的一种：按长度拆包。其他两个大同小异

```cpp

```

### 再来看使用demo —— 200行实现一个纯C版jsonrpc框架

使用libhv可以在200行内实现一个完整的jsonrpc框架，这得益于libhv新提供的一个接口 `hio_set_unpack` 设置拆包规则，支持 `固定包长、分隔符、头部长度字段` 三种常见的拆包方式，调用该接口设置拆包规则后，内部会根据拆包规则处理粘包与分包，保证回调上来的是完整的一包数据，大大节省了上层处理粘包与分包的成本，该接口具体定义如下：

```cpp
typedef enum {
    UNPACK_BY_FIXED_LENGTH  = 1,    // 根据固定长度拆包
    UNPACK_BY_DELIMITER     = 2,	// 根据分隔符拆包，如常见的“\r\n”
    UNPACK_BY_LENGTH_FIELD  = 3,    // 根据头部长度字段拆包
} unpack_mode_e;

#define DEFAULT_PACKAGE_MAX_LENGTH  (1 << 21)   // 2M

// UNPACK_BY_DELIMITER
#define PACKAGE_MAX_DELIMITER_BYTES 8

// UNPACK_BY_LENGTH_FIELD
typedef enum {
    ENCODE_BY_VARINT        = 1,				// varint编码
    ENCODE_BY_LITTEL_ENDIAN = LITTLE_ENDIAN,    // 小端编码
    ENCODE_BY_BIG_ENDIAN    = BIG_ENDIAN,       // 大端编码
} unpack_coding_e;

typedef struct unpack_setting_s {
    unpack_mode_e   mode; // 拆包模式
    unsigned int    package_max_length; // 最大包长度限制
    // UNPACK_BY_FIXED_LENGTH
    unsigned int    fixed_length; // 固定包长度
    // UNPACK_BY_DELIMITER
    unsigned char   delimiter[PACKAGE_MAX_DELIMITER_BYTES]; // 分隔符
    unsigned short  delimiter_bytes; // 分隔符长度
    // UNPACK_BY_LENGTH_FIELD
    unsigned short  body_offset; // body偏移量（即头部长度）real_body_offset = body_offset + varint_bytes - length_field_bytes
    unsigned short  length_field_offset; // 头部长度字段偏移量
    unsigned short  length_field_bytes; // 头部长度字段所占字节数
    unpack_coding_e length_field_coding; // 头部长度字段编码方式，支持varint、大小端三种编码方式，通常使用大端字节序（即网络字节序）
#ifdef __cplusplus
    unpack_setting_s() {
        // Recommended setting:
        // head = flags:1byte + length:4bytes = 5bytes
        mode = UNPACK_BY_LENGTH_FIELD;
        package_max_length = DEFAULT_PACKAGE_MAX_LENGTH;
        fixed_length = 0;
        delimiter_bytes = 0;
        body_offset = 5;
        length_field_offset = 1;
        length_field_bytes = 4;
        length_field_coding = ENCODE_BY_BIG_ENDIAN;
    }
#endif
} unpack_setting_t;

HV_EXPORT void hio_set_unpack(hio_t* io, unpack_setting_t* setting);
```

示例代码

见 [examples/jsonrpc](https://github.com/ithewei/libhv/tree/master/examples/jsonrpc)

```cpp
#include "hloop.h"
#include "hbase.h"
#include "hsocket.h"

#include "jsonrpc.h"
#include "cJSON.h"
#include "router.h"
#include "handler.h"

// hloop_create_tcp_server -> on_accept -> hio_read -> on_recv -> hio_write

static unpack_setting_t jsonrpc_unpack_setting;

jsonrpc_router router[] = {
    {"add", do_add},
    {"sub", do_sub},
    {"mul", do_mul},
    {"div", do_div},
};
#define JSONRPC_ROUTER_NUM  (sizeof(router)/sizeof(router[0]))

static void on_close(hio_t* io) {
    printf("on_close fd=%d error=%d\n", hio_fd(io), hio_error(io));
}

static void on_recv(hio_t* io, void* readbuf, int readbytes) {
    // unpack -> cJSON_Parse -> router -> cJSON_Print -> pack -> hio_write
    // unpack
    jsonrpc_message msg;
    memset(&msg, 0, sizeof(msg));
    int packlen = jsonrpc_unpack(&msg, readbuf, readbytes);
    if (packlen < 0) {
        printf("jsonrpc_unpack failed!\n");
        return;
    }
    assert(packlen == readbytes);

    // cJSON_Parse
    printf("> %.*s\n", msg.head.length, msg.body);
    cJSON* jreq = cJSON_ParseWithLength(msg.body, msg.head.length);
    cJSON* jres = cJSON_CreateObject();
    cJSON* jmethod = cJSON_GetObjectItem(jreq, "method");
    if (!jmethod || !cJSON_IsString(jmethod)) {
        bad_request(jreq, jres);
    } else {
        // router
        char* method = cJSON_GetStringValue(jmethod);
        bool found = false;
        for (int i = 0; i < JSONRPC_ROUTER_NUM; ++i) {
            if (strcmp(method, router[i].method) == 0) {
                found = true;
                router[i].handler(jreq, jres);
                break;
            }
        }
        if (!found) {
            not_found(jreq, jres);
        }
    }

    // cJSON_Print
    memset(&msg, 0, sizeof(msg));
    msg.body = cJSON_PrintUnformatted(jres);
    msg.head.length = strlen(msg.body);
    printf("< %.*s\n", msg.head.length, msg.body);

    // pack
    packlen = jsonrpc_package_length(&msg.head);
    unsigned char* writebuf = NULL;
    HV_ALLOC(writebuf, packlen);
    packlen = jsonrpc_pack(&msg, writebuf, packlen);
    if (packlen > 0) {
        hio_write(io, writebuf, packlen);
    }

    cJSON_Delete(jreq);
    cJSON_Delete(jres);
    cJSON_free((void*)msg.body);
    HV_FREE(writebuf);
}

static void on_accept(hio_t* io) {
    printf("on_accept connfd=%d\n", hio_fd(io));

    hio_setcb_close(io, on_close);
    hio_setcb_read(io, on_recv);
    hio_set_unpack(io, &jsonrpc_unpack_setting);
    hio_read(io);
}

int main(int argc, char** argv) {
    if (argc < 2) {
        printf("Usage: %s port\n", argv[0]);
        return -10;
    }
    int port = atoi(argv[1]);

    // init jsonrpc_unpack_setting
    memset(&jsonrpc_unpack_setting, 0, sizeof(unpack_setting_t));
    jsonrpc_unpack_setting.mode = UNPACK_BY_LENGTH_FIELD;
    jsonrpc_unpack_setting.package_max_length = DEFAULT_PACKAGE_MAX_LENGTH;
    jsonrpc_unpack_setting.body_offset = JSONRPC_HEAD_LENGTH;
    jsonrpc_unpack_setting.length_field_offset = 1;
    jsonrpc_unpack_setting.length_field_bytes = 4;
    jsonrpc_unpack_setting.length_field_coding = ENCODE_BY_BIG_ENDIAN;

    hloop_t* loop = hloop_new(0);
    hio_t* listenio = hloop_create_tcp_server(loop, "0.0.0.0", port, on_accept);
    if (listenio == NULL) {
        return -20;
    }
    printf("listenfd=%d\n", hio_fd(listenio));
    hloop_run(loop);
    hloop_free(&loop);
    return 0;
}
```













