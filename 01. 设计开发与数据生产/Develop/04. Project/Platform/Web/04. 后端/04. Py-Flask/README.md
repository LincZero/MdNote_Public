# 04. Py-Flask

参考

- 中文文档：https://dormousehole.readthedocs.io/en/latest/

## 快速上手 - 一个最小的应用

```python
from flask import Flask

app = Flask(__name__)

@app.route("/")
def hello_world():
    return "<p>Hello, World!</p>"
```

