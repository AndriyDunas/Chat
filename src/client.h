// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains declaration of class Client that means Client-mode of application. 
//
#ifndef CLIENT_H_
#define CLIENT_H_

#include "general.h"

#if defined(WIN)
#include "windows_socket.h"
#include "windows_thread.h"
typedef WindowsSocket Socket;
typedef WindowsThread Thread;
#elif defined(LIN)
#include "linux_socket.h"
#include "linux_thread.h"
typedef LinuxSocket Socket;
typedef LinuxThread Thread;
#endif
#include <stdio.h>
#include <time.h>  // for strftime()

class Client {
 public:
  explicit Client();
  ~Client();
  void Run(void);
 
 private:
  // Copy operations are private to prevent copying
  Client(const Client&);
  Client& operator=(const Client&);

  // Entry function for thread that receiving messages from server
  static void* ReceiveMessage(void *sock);
  // Get current system time to buffer, format is HH:MM:SS
  void GetTime(char *buffer, unsigned int size);
  // Removing trailing newline character from fgets() input
  void RemoveNewline(char *str);

  bool is_init_;    // Flag for holding initialize status
  Socket *socket_;  // Socket for sending and receiving messages
  char *name_;      // Name of user
  char *buffer_;    // Buffer for user input
  char *time_;      // Buffer for storing current system time
  char *message_;   // Buffer for the message that we send to server
  static char *received_message_;  // Buffer for the message we receive to server
};

#endif // !CLIENT_H_