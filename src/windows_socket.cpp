// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains implementation of class WindowsSocket 
// having specialization to use sockets in Windows.
//
#include "windows_socket.h"

#if defined(WIN)

WindowsSocket::WindowsSocket() {
  socket_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
}

WindowsSocket::~WindowsSocket() {
  CloseSocket();
}

bool WindowsSocket::Bind(const int port) const {
  // The sockaddr_in structure specifies the address family,
  // IP address, and port for the socket that is being bound.
  sockaddr_in loc_addr;
  loc_addr.sin_family = AF_INET;
  loc_addr.sin_port = htons(port);
  loc_addr.sin_addr.s_addr = INADDR_ANY;  // inet_addr(host);

  int result = bind(socket_, reinterpret_cast<struct sockaddr*>(&loc_addr),
                    sizeof(loc_addr));
  if (result == SOCKET_ERROR) {
    return false;  // bind failed
  }
  return true;  // all is OK
}

bool WindowsSocket::Listen(unsigned int backlog) const {
  int result = listen(socket_, backlog);
  if (result == SOCKET_ERROR) {
    return false;
  }
  return true;
}

WindowsSocket* WindowsSocket::Accept(void) {
  SOCKET accept_socket = accept(socket_, NULL, NULL);
  if (accept_socket == INVALID_SOCKET) {
    return nullptr;
  } 
  return new WindowsSocket(accept_socket);
}

bool WindowsSocket::Connect(const char *host, const char *port) const {
  // Contains response information about the host after after getaddrinfo call
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
  result = connect(socket_, res_info->ai_addr, 
                   static_cast<int>(res_info->ai_addrlen));
  freeaddrinfo(res_info);  // No longer needed
  if(result != 0) {
    return false;
  }
  return true;
}

int WindowsSocket::Send(const char *data, int len) const {
  int result = send(socket_, data, len, 0);
  if (result == SOCKET_ERROR) {
    return 0;
  }
  return len;
}

int WindowsSocket::Receive(char *data, int len) const {
  int result = recv(socket_, data, len, 0);
  if (result == SOCKET_ERROR) {
    return 0;
  }
  return result;
}

bool WindowsSocket::CloseSocket(void) {
  int result = shutdown(socket_, SD_BOTH);
  closesocket(socket_);
  socket_ = INVALID_SOCKET;
  if (result == SOCKET_ERROR) {
    return false;
  }
  return true;
}

bool WindowsSocket::Initialize(void) {
  WSADATA wsa_data;
  const unsigned int kMinorVersion = 2, kMajorVersion = 2;
  WORD w_version_requested = MAKEWORD(kMinorVersion, kMajorVersion);		

  // WSAStartup initiates use of the Winsock DLL by a process.
  int result = WSAStartup(w_version_requested, &wsa_data);  
  if (result != 0) {                       
    return false;	 // Winsock DLL not found
  }
  return true;  // all is OK
}

int WindowsSocket::LastError(void) {
// returns the error status for the last Windows Sockets operation that failed.
  return WSAGetLastError();
}

bool WindowsSocket::Clean(void) {
  // WSACleanup terminates use of the Winsock 2 DLL (Ws2_32.dll).
  if (WSACleanup() == 0) {
    return true;
  }
  return false;  // WSACleanup returns the SOCKET_ERROR
}

#endif  // !implementation of class