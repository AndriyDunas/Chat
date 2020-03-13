// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains abstract class AbstractSocket with virtual methods
// that are overrided in derived classes having specializations for each platform. 
// Sockets are used for a communication flow between two programs running
// over a network.
//
#ifndef ABSTRACT_SOCKET_H_
#define ABSTRACT_SOCKET_H_

class AbstractSocket {
 public:
  virtual ~AbstractSocket() {}

  // Server-part methods
  // Associates a local address with a socket.
  virtual bool Bind(const int port) const = 0;		
  // Listen function places a socket in a state in 
  // which it is listening for an incoming connection.
  virtual bool Listen(unsigned int backlog) const = 0;
  // Accept function permits an incoming connection attempt on a socket.
  virtual AbstractSocket* Accept() = 0;

  // Client-part method
  // The Connect function establishes a connection to a specified socket.
  virtual bool Connect(const char* host, const char* port) const = 0;
	
  // Send and receive messages
  virtual int Send(const char *data, int len) const = 0;
  virtual int Receive(char *data, int len) const = 0;

  //close socket for both read and write
  virtual bool CloseSocket(void) = 0; 

  static bool Initialize(void);  // Initialize socket library
  static int LastError(void);    // Returns ID of last error which occured
  static bool Clean(void);       // Clean socket library 
};

#endif // !ABSTRACT_SOCKET_H_