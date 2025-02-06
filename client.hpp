#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include <cstdint>

void createClientKey();

int connectToServer();

int establishClientKey(int socketfd);

#endif
