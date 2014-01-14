#if !defined(_SOCKET_H)
#define _SOCKET_H

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;
class Socket {
public:
    char addr[16];
    int port;
    int fd;
    Socket();
    Socket(const char* addr, int port);
    Socket(const int newfd);
    int send(const char* str);
    int recv(char str[]);
    void close();
    char* getIpAddress();
    int getPort();
};

class Package{
};

#endif  //_SOCKET_H
