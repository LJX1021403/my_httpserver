#include <iostream>
#include <string>
#include <cstring>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

int main() {
    // 1. 创建 socket
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd < 0) {
        std::cerr << "socket error" << std::endl;
        return 1;
    }

    // 2. 绑定地址
    struct sockaddr_in address;
    std::memset(&address, 0, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(9090);   

    if (bind(listen_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cerr << "bind error" << std::endl;
        close(listen_fd);
        return 1;
    }

    // 3. 监听
    if (listen(listen_fd, 5) < 0) {
        std::cerr << "listen error" << std::endl;
        close(listen_fd);
        return 1;
    }

    std::cout << "Server listening on port 9090..." << std::endl;

    while (true) {
        // 4. 接受连接
        int client_fd = accept(listen_fd, nullptr, nullptr);
        if (client_fd < 0) {
            std::cerr << "accept error" << std::endl;
            continue;
        }

        // 5. 读取请求
        char buffer[1024] = {0};
        int n = read(client_fd, buffer, sizeof(buffer) - 1);
        if (n > 0) {
            std::cout << "Received request:\n" << buffer << std::endl;
        }

        // 6. 构造并发送响应
	std::string body="hello Word";

	std::string response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "Content-Length:"+ std::to_string(body.size())+"\r\n"
            "\r\n"+
            body;

        write(client_fd, response.c_str(), response.size());

        // 7. 关闭连接（关闭套接字会告知客户端数据已结束）
        close(client_fd);
    }

    close(listen_fd);
    return 0;
}
