#include <cstdio>
#include <cstring>
#include <winsock2.h>
#include "server.hpp"
#include "client.hpp"

int main(int argc, char const *argv[]){
    WSAData wsaData;
    int error = WSAStartup(MAKEWORD(2,2),&wsaData);
    if (error != 0) return 1;

    if (argc != 2) {
        fprintf(stderr,"usagve: Diffie [client] or [host]\n");
        return 1;
    }
    if(strcmp(argv[1],"host") == 0){
        createHostKey();
    }
    if(strcmp(argv[1],"client") == 0){
        createClientKey();
    }

    WSACleanup();

    return 0;
}
