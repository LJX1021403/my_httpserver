
# my-httpserver

一个用于学习网络编程的简单 C++ HTTP 服务器。

##当前功能

- v1:单线程阻塞式HTTP服务器
- 监听9090端口
- 对任何请求返回"Hello World"

##编译

```bash
g++ -std=c++17 -o serve src/main.cpp

