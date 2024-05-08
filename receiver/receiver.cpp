#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define A_PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];

    // 创建UDP套接字
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 设置A的地址结构
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(A_PORT);

    // 将套接字绑定到指定端口
    if (bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("A is listening on port %d...\n", A_PORT);

    while (1) {
        // 接收来自B的消息
        ssize_t recv_len = recvfrom(sockfd, buffer, BUFFER_SIZE, 0,
                                    (struct sockaddr*)&client_addr, &addr_len);

        if (recv_len == -1) {
            perror("recvfrom");
            continue;
        }

        // 打印接收到的消息
        buffer[recv_len] = '\0';  // 确保字符串结束符
        printf("Received from B %s:%d: %s\n",
               inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port), buffer);

        // 在这里进行消息处理，可以根据具体需求进行逻辑编写
        // 例如，处理接收到的消息并回复
        const char *response = "Message received and processed by A";
        if (sendto(sockfd, response, strlen(response), 0,
                   (struct sockaddr*)&client_addr, addr_len) == -1) {
            perror("sendto");
        }
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}
