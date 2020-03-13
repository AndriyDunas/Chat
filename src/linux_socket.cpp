// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains implementation of class LinuxSocket 
// having specialization to use sockets in Linux.
//
#include "general.h"

#if defined(LIN)

#include "linux_socket.h"

LinuxSocket::LinuxSocket() {
  socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

LinuxSocket::~LinuxSocket() {
  CloseSocket();
}

bool LinuxSocket::Bind(const int port) const {
  // The sockaddr_in structure specifies the address family,
  // IP address, and port for the socket that is being bound.
  sockaddr_in loc_addr;
  memset(&loc_addr, 0, sizeof(loc_addr));
  loc_addr.sin_family = AF_INET;
  loc_addr.sin_port = htons(port);
  loc_addr.sin_addr.s_addr = INADDR_ANY;
  int result = bind(socket_, reinterpret_cast<struct sockaddr *>(&loc_addr),
                    sizeof(loc_addr));
  if (result == INVALID_SOCKET) {
    return false;  // bind failed
  }
  return true;  // all is OK
}

bool LinuxSocket::Listen(unsigned int backlog) const {
  int result = listen(socket_, backlog);
  if (result == INVALID_SOCKET) {
    return false;
  }
  return true;
}

LinuxSocket* LinuxSocket::Accept(void) {
  int accept_socket = accept(socket_, NULL, NULL);
  if (accept_socket == INVALID_SOCKET) {
    return nullptr;
  }
  return new LinuxSocket(accept_socket);
}

bool LinuxSocket::Connect(const char *host, const char *port) const {
  // Contains response information about the host after getaddrinfo call
  struct addrinfo *res_info = NULL;
  // Hints about the type of socket the caller supports.
  struct addrinfo hints;
  memset(&hints, 0, sizeof(addrinfo));
  hints.ai_family = AF_INET;
  hints.ai_socktype = SOCK_STREAM;
  hints.ai_protocol = IPPROTO_TCP;

  int result = getaddrinfo(host, port, &hints, &res_info);
  if (result != 0) {
    return false;
  }
  result = connect(socket_, res_info->ai_addr, res_info->ai_addrlen);
  freeaddrinfo(res_info);  // No longer needed
  if (result != 0) {
    return false;
  }
  return true;
}

int LinuxSocket::Send(const char *data, int len) const {
  int result = send(socket_, data, len, 0);
  if (result == INVALID_SOCKET) {
    return 0;
  }
  return len;
}

int LinuxSocket::Receive(char *data, int len) const {
  int result = recv(socket_, data, len, 0);
  if (result == INVALID_SOCKET) {
    return 0;
  }
  return result;
}

bool LinuxSocket::CloseSocket(void) {
  int result = shutdown(socket_, SHUT_RDWR);  
  close(socket_);
  socket_ = INVALID_SOCKET;
  if (result != 0) {
    return false;
  }
  return true;
}

#endif  // !class implementation