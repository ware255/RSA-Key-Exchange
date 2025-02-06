#include <cstdio>
#include <thread>
#include <cstring>
#include <winsock2.h>
#include "client.hpp"
#include "rsa.hpp"

// createClientKey guides the client to chat
void createClientKey() {
    // int socketfd is our client socket descriptor
    int socketfd = connectToServer();

    // int key is our public key
    int key = establishClientKey(socketfd);

    printf("These should be the same: %d\n", key);

    closesocket(socketfd);
}

int connectToServer() {
    int socketfd;
    struct sockaddr_in server_addr;

    char host[256];
    printf("What address do you want to connect to? \n");
    scanf("%s", host);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr(host);

    if (server_addr.sin_addr.s_addr == INADDR_NONE) {
        fprintf(stderr, "Invalid address/ Address not supported\n");
        return -1;
    }

    if ((socketfd = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
        fprintf(stderr, "socket error\n");
        return -1;
    }

    if (connect(socketfd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        fprintf(stderr, "Connection failed\n");
        closesocket(socketfd);
        return -1;
    }

    return socketfd;
}

int establishClientKey(int socketfd) {
    RSA client;
    char buffer[256];

    recv(socketfd, buffer, sizeof(buffer), 0);
    client.setPubKey(atoi(buffer));

    sprintf(buffer, "%lld", client.Encrypt(810));
    send(socketfd, buffer, sizeof(buffer), 0);

    return 810;
}

