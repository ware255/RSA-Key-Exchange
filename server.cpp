#include <cstdio>
#include <thread>
#include <windows.h>
#include "server.hpp"
#include "rsa.hpp"

#ifdef WIN32
#define MSG_NOSIGNAL   0
#define socklen_t      int
#endif

// createHostKey guides the client to chat.
void createHostKey(){
    int accept_socket, socketfd;
    struct sockaddr_in addr;

    socketfd = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);
    addr.sin_addr.S_un.S_addr = INADDR_ANY;

    bind(socketfd, (struct sockaddr *)&addr, sizeof(addr));

    listen(socketfd, 10);

    // int accept_socket is the client socket descriptor
    socklen_t addrlen;
    accept_socket = accept(socketfd, (struct sockaddr *)&addr, &addrlen);

    // int key is our public key
    uint64_t key = establishHostKey(accept_socket);
    printf("This should be the same: %lld\n", key);

    closesocket(socketfd);
}

uint64_t establishHostKey(int accept_socket) {
    RSA host;
    char buffer[256];

    sprintf(buffer, "%lld", host.getPubKey());
    send(accept_socket, buffer, sizeof(buffer), 0);

    recv(accept_socket, buffer, sizeof(buffer), 0);

    return host.Decrypt(atoi(buffer));
}
