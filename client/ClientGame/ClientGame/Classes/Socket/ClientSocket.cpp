
#include "ClientSocket.h"

ClientSocket::ClientSocket(const char* addr, int port) :
  Socket(addr, port) {  
}

ClientSocket::ClientSocket(){
}

int ClientSocket::connect() {
  struct sockaddr_in srv;
  srv.sin_family = AF_INET;
  srv.sin_port = htons(port);
  srv.sin_addr.s_addr = inet_addr(addr);
  int return_connect = ::connect(fd, (struct sockaddr*) &srv, sizeof(srv));
  if (return_connect < 0){
    perror("connect");
    exit(1);
  }  
  return return_connect;
}
