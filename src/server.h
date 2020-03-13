// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains declaration of class Server that means Server-mode of application. 
//
// I used static methods as entry functions for threads, because
// of class member functions have a hidden this parameter passed in, so 
// _beginthreadex() or pthread_create() has no idea what value of this to use.
//
// Each time a program runs, it is only one object of Server or Client class
// can be created, and no more in current instance of program, so we ñan't have
// a lot of objects that uses the same static methods and variables.
//
#ifndef SERVER_H_
#define SERVER_H_

#include "general.h"

#if defined(WIN)
#include "windows_socket.h"
#include "windows_thread.h"
#include "windows_synchronizer.h"
typedef WindowsSocket Socket;
typedef WindowsThread Thread;
typedef WindowsSynchronizer Synchronizer;
#elif defined(LIN)
#include "linux_socket.h"
#include "linux_thread.h"
#include "linux_synchronizer.h"
typedef LinuxSocket Socket;
typedef LinuxThread Thread;
typedef LinuxSynchronizer Synchronizer;
#endif
#include "file.h"
#include <stdlib.h>

class Server {
 public:
  explicit Server();
  ~Server();
  void Run(const char *filename);

 private:
  // copy operations are private to prevent copying
  Server(const Server&);
  Server& operator=(const Server&);

  // Entry function for serving each new client in new thread
  static void* ServClient(void *sock);
  // Provide sending all messages from each client to other clients. 
  static bool SendToAll(Socket *socket, const char *buffer);
  // Delete socket of client from sockets array
  static void DeleteClient(Socket *socket);
  
  Socket *server_sock_;            // Socket for initialize actions
  Socket *client_sock_;            // Temporary socket for accepting connections 
  static Socket **clients_;        // Array of client's sockets
  static File *file_;              // File for storing conversation history
  static Synchronizer *synchron_;  // Synchronizer object for thread syncronization
  static unsigned int cur_num_;    // Current number of clients
  bool is_init_;                   // Flag for holding initialize status
};

#endif // !SERVER_H_