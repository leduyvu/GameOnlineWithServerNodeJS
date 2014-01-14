#include "Socket.h"
#include <iostream>
#include <string.h>
Socket::Socket(const char* addr, int port) {
  strcpy(this->addr, addr);
  this->port = port;
  fd = socket(AF_INET, SOCK_STREAM, 0);
  if (fd < 0) {
    printf("socket");
    exit(1);
  }
}

Socket::Socket(const int newfd) {
  fd = newfd;
}

Socket::Socket(){
}

int Socket::send(const char* str) {
    std::string strc(str);
    int nbytes = ::send(fd, str, sizeof(char) * strc.length(), 0);
    if (nbytes < 0) {
        perror("write");
        exit(1);
    }
    strc.clear();
  return nbytes;
}

int Socket::recv(char *str) {
  int nbytes = ::recv(fd, str, sizeof(char)* 10, 0);
  if (nbytes < 0) {
    perror("read");
    exit(1);
  }  
  return nbytes;
}

void Socket::close() {
  ::close(fd);
}
char* Socket::getIpAddress(){
  struct sockaddr_in client;
  socklen_t len = sizeof(client);
  if(getpeername(fd ,(struct sockaddr*) &client,&len) < 0){
	perror("error");
  }
  return inet_ntoa(client.sin_addr);
}

int Socket::getPort(){
  struct sockaddr_in client;
  socklen_t len = sizeof(client);
  if(getpeername(fd ,(struct sockaddr*) &client,&len) < 0){
	perror("error");
  }
  return ntohs(client.sin_port);
}
