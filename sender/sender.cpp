#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>

#define A_IP "127.0.0.1"  // A的IP地址
#define A_PORT 12345       // A的端口号
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
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
    server_addr.sin_addr.s_addr = inet_addr(A_IP);
    server_addr.sin_port = htons(A_PORT);

    while (1) {
        // 从用户输入读取消息
        printf("Enter message for A: ");
        fgets(buffer, BUFFER_SIZE, stdin);

        // 发送消息到A
        if (sendto(sockfd, buffer, strlen(buffer), 0,
                   (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
            perror("sendto");
            break;
        }
    }

    // 关闭套接字
    close(sockfd);

    return 0;
}
