-   trace_print()

    一个简单的内核工具，用于 printf() 到公共trace_pipe  (/sys/kernel/debug/tracing/trace_pipe)。
    这对于一些快速示例来说是可以的，但有**限制**：

    -   最多 3 个参数
    -   仅限 1 %s
    -   并且 trace_pipe 是全局共享的，因此并发程序将产生冲突的输出

- b.trace_fields()

    从trace_pipe返回一组固定的字段

- BPF_PERF_OUTPUT()

    建议使用

trace_fields() 与 trace_print() 类似，这对于黑客攻击来说很方便，但对于真正的工具，我们应该切换到BPF_PERF_OUTPUT()