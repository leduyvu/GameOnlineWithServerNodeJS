#if !defined(_CLIENTSOCKET_H)
#define _CLIENTSOCKET_H

#include "Socket.h"

class ClientSocket : public Socket {
public:
    ClientSocket();
    ClientSocket(const char* addr, int port);
    int connect();
};

#endif  //_CLIENTSOCKET_H
