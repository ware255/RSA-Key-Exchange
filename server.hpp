#ifndef _SERVER_HPP_
#define _SERVER_HPP_

#include <cstdint>

void createHostKey();

uint64_t establishHostKey(int accept_socket);

#endif
