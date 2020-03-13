// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains declaration of class WindowsSocket 
// having specialization to use sockets in Windows.
//
#ifndef WINDOWS_SOCKET_H_
#define WINDOWS_SOCKET_H_

#include "general.h"

#if defined(WIN)

#define _WIN32_WINNT  0x501
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>  
#include <ws2tcpip.h>	 // For getaddrinfo
#include "abstract_socket.h"
//#pragma comment(lib, "ws2_32.lib")  // Need to link with Ws2_32.lib, use it in VS

class WindowsSocket : public AbstractSocket {
 public:
  explicit WindowsSocket();
  explicit WindowsSocket(SOCKET sock) : socket_(sock) {};
  ~WindowsSocket();

  bool Bind(const int port) const override;
  bool Listen(unsigned int backlog) const override;
  WindowsSocket* Accept(void) override;

  bool Connect(const char *host, const char *port) const override;

  int Send(const char *data, int len) const override;
  int Receive(char *data, int len) const override;

  SOCKET GetSocket(void) { return socket_; }
  bool CloseSocket(void) override;

  static bool Initialize(void);
  static int LastError(void);
  static bool Clean(void);

 private:
  SOCKET socket_;  
};

#endif  // !includes, class declaration

#endif  // !WINDOWS_SOCKET_H_