# Linux开机自启

## 实战

以我在公司2U ubuntu 服务器中弄的两个ftp自启为例：

```bash
sudo nano /etc/systemd/system/httpServer.service
sudo systemctl daemon-reload # 重新加载文件
sudo systemctl start httpServer.service # 启动
sudo systemctl enable httpServer.service # (话说这个似乎省略也能成功)

sudo nano /etc/systemd/system/httpServer2.service
sudo systemctl daemon-reload
sudo systemctl start httpServer2.service
sudo systemctl enable httpServer2.service
```

文件内容

/etc/systemd/system/httpServer.service

```ini
[Unit]
Description=My HTTP Service
After=network.target

[Service]
ExecStart=/usr/bin/python3 /root/Http/python.py
WorkingDirectory=/root/Http
User=root
Restart=always

[Install]
WantedBy=multi-user.target
```

/root/Http/python.py

```python
import http.server
import socketserver

PORT = 8050

Handler = http.server.SimpleHTTPRequestHandler
Handler.extensions_map.update({
    '.js':  'application/javascript',
})

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print("serving at port", PORT)
    httpd.serve_forever()
```

/etc/systemd/system/httpServer2.service

```ini
[Unit]
Description=My HTTP Service
After=network.target

[Service]
ExecStart=/usr/bin/python3 /home/msy/ftp/ftpuser/python.py
WorkingDirectory=/home/msy/ftp/ftpuser/
User=root
Restart=always

[Install]
WantedBy=multi-user.target
```

/home/msy/ftp/ftpuser/python.py

```python

import http.server
import socketserver

PORT = 7080

Handler = http.server.SimpleHTTPRequestHandler
Handler.extensions_map.update({
    '.js':  'application/javascript',
})

with socketserver.TCPServer(("", PORT), Handler) as httpd:
    print("serving at port", PORT)
    httpd.serve_forever()
```

备用方式：

```
python -m http.server 8050
```

