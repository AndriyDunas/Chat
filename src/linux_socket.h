// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains declaration of class LinuxSocket 
// having specialization to use sockets in Linux.
//
#ifndef LINUX_SOCKET_H_
#define LINUX_SOCKET_H_

#include "general.h"

#if defined(LIN)

// Analog of INVALID_SOCKET in Windows
#define INVALID_SOCKET -1  

#include <unistd.h>
#include <errno.h>
#include <string.h>

#include <sys/socket.h>
#include <sys/resource.h>
#include <sys/types.h>

#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include "abstract_socket.h"

class LinuxSocket : public AbstractSocket {
 public:
  explicit LinuxSocket();
  explicit LinuxSocket(int socket) : socket_(socket) {};
  ~LinuxSocket();

  bool Bind(const int port) const override;
  bool Listen(unsigned int backlog) const override;
  LinuxSocket* Accept(void) override;

  bool Connect(const char *host, const char *port) const override;

  int Send(const char *data, int len) const override;
  int Receive(char *data, int len) const override;

  int GetSocket(void) { return socket_; }
  bool CloseSocket(void) override;

  // Nothing to do for Linux
  static bool Initialize(void) { return true; }
  static bool Clean(void) { return true; }
  // Returns last error occured
  static int LastError(void) { return errno; }

 private:
  int socket_;
};

#endif  // !includes, class declaration

#endif  // !LINUX_SOCKET_H_