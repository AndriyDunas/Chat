// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains implementation of class Client.
//
#include "client.h"

const char *kHost = "127.0.0.1";
extern const char *kPort;
const unsigned int kBufferLen = 100;  // max size of input buffer
const unsigned int kNameLen = 20;     // max size of client nickname
const unsigned int kTimeLen = 10;     // max size of time buffer
// max size of message
extern const unsigned int kMessageLen = kBufferLen + kNameLen + kTimeLen + 5;  

// Memory allocation for static member
char* Client::received_message_ = new char[kMessageLen];

Client::Client() {
  is_init_ = Socket::Initialize();
  socket_ = new Socket;
  name_ = new char[kNameLen];
  buffer_ = new char[kBufferLen];
  time_ = new char[kTimeLen];
  message_ = new char[kMessageLen];
}

Client::~Client() {
  delete socket_;
  delete[] name_;
  delete[] buffer_;
  delete[] time_;
  delete[] message_;
  delete[] received_message_;
  Socket::Clean();
}

void Client::Run(void) {
  if (!is_init_) {
    puts("Initialize() failed!");
    return;
  }
  if (socket_->GetSocket() == INVALID_SOCKET) {
    printf("socket() failed with error: %d\n", socket_->LastError());
    return;
  }
  if (!socket_->Connect(kHost, kPort)) {
    printf("Connect failed with error: %d\n", socket_->LastError());
    return;
  }
  printf("CLIENT APP\nWhat's your nickname: ");
  fgets(name_, kNameLen - 1, stdin);  // User input
  RemoveNewline(name_);              

  while (strstr(message_, "exit") == 0) {
    // Create a new thread for receiving messages from server
    void *p_void = (void*)socket_;
    Thread recv_thread(ReceiveMessage, p_void);	
    // Create message shapes
    fgets(buffer_, kBufferLen - 1, stdin);
    RemoveNewline(buffer_);
    GetTime(time_, kTimeLen);  // Get the current system time
    *message_ = '\0';
    // Concatenate Time + Name + Input to message
    strcat(message_, time_); strcat(message_, " ");
    strcat(message_, name_); strcat(message_, ": "); strcat(message_, buffer_);
    // Send message to server
    if (!socket_->Send(message_, kMessageLen)) {
      printf("Send failed with error: %d\n", socket_->LastError());
      break;
    }
  }
}

void* Client::ReceiveMessage(void *sock) {
  Socket *socket = static_cast<Socket*>(sock);
  // Receive message from server and print it
  while (socket->Receive(received_message_, kMessageLen)) {  
    puts(received_message_);
  }
  return nullptr;
}

void Client::GetTime(char *buffer, unsigned int size) {
  // Get the current calendar time as a value of type time_t.
  time_t now = time(0);  
  // Structure containing a calendar date and time.
  struct tm  tstruct = *localtime(&now);
  // Copies into buffer the time described in tstruct
  strftime(buffer, size, "%X", &tstruct);
}

void Client::RemoveNewline(char *str) {
  // Locate first occurrence of character in string
  char *ptr = strchr(str, '\n');
  // Put there a null-terminator
  if (ptr) {
    *ptr = '\0';
  } 
}