

https://github.com/esnet/iperf

源码分析：https://blog.csdn.net/meihualing/article/details/130815688 作者

### 个人常用流程

```bash
# 服务端
iperf3 -s -B 192.168.208.199 -p 5201

# 客户端
# iperf3 -c 192.168.208.199 -p 5201 --udp # 简单版
# iperf3 -c 192.168.208.199 -p 5201 --udp -l 100 -b 1000M # 中等版
iperf3 -B 192.168.208.1 -c 192.168.208.199 -p 5201 --udp -l 100 -b 1000M # 高参数版
```

