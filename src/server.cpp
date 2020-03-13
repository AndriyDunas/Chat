// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// This file contains implementation of class Server 
//
#include "server.h"

const char *kPort = "3030";
const unsigned int kClientNum =  10;    // max number of clients
const unsigned int kBacklog = 1000;     // Backlog for Listen() function
const char *kGreeting = "Server: Hello! Welcome to conversation!\n\
Type 'exit' to leave the conversation.";
extern const unsigned int kMessageLen;  // max size of message

// Initializing and memory allocation for static members
Socket** Server::clients_ = new Socket*[kClientNum];
File* Server::file_ = nullptr;
unsigned int Server::cur_num_ = 0;
Synchronizer* Server::synchron_ = new Synchronizer;

Server::Server() {
  is_init_ = Socket::Initialize();
  server_sock_ = new Socket;
  client_sock_ = new Socket;
  for (unsigned int i = 0; i < kClientNum; i++) {
    clients_[i] = new Socket;  // allocate memory for each socket in array
    clients_[i] = nullptr;
  }
}

Server::~Server() {
  delete server_sock_;
  delete client_sock_;
  for (unsigned int i = 0; i < kClientNum; i++) {
    delete clients_[i];  // deallocate memory for each socket in array
  }
  delete[] clients_; 
  if(file_) {
    delete file_;
  }
  delete synchron_;
  Socket::Clean();
}

void Server::Run(const char *filename) {
  if (!is_init_) {
    puts("Initialize() failed!");
    return;
  }
  if (server_sock_->GetSocket() == INVALID_SOCKET ||
    client_sock_->GetSocket() == INVALID_SOCKET) {
    printf("socket() failed with error: %d\n", server_sock_->LastError());
    return;
  }
  if (!server_sock_->Bind(atoi(kPort))) {
    printf("Bind failed with error: %d\n", server_sock_->LastError());
    return;
  }
  if (!server_sock_->Listen(kBacklog)) {
    printf("Listen failed with error: %d\n", server_sock_->LastError());
    return;
  }
  puts("SERVER APP"); 
  file_ = new File(filename);
  if (file_->IsValid()) {
    file_->Write("\nNew conversation");  
    file_->Refresh();
  } else {
    puts("Cannot open a file. Message doesn't saved.");
  }

  // loop for accepting connections
  while ((client_sock_ = server_sock_->Accept())) { 
    if (client_sock_->GetSocket() == INVALID_SOCKET) {
      printf("Accept failed with error: %d\n", client_sock_->LastError());
      return;
    }	
    // Loop for finding a place for new client in client's array
    for (unsigned int cl = 0; cl < kClientNum; cl++) {
      if (clients_[cl] == nullptr) {  // If an index of array is free
        clients_[cl] = client_sock_;  // put client socket in this index
        SendToAll(client_sock_, "Server: Client has joined!");
        // Send greeting to new client
        if (!client_sock_->Send(kGreeting, kMessageLen)) {  
          printf("Send failed with error: %d\n", clients_[cl]->LastError());
          clients_[cl]->CloseSocket();
          clients_[cl] = nullptr;
          break;
        }
        // Create a new thread for new client
        void *p_void = (void*)clients_[cl];
        Thread con_thread(ServClient, p_void);
        cur_num_++;
        // Used %lu format because of in linux we have pthread_t type aka long unsigned int
        printf("New connection! Thread ID: %lu\n", static_cast<long unsigned int>(con_thread.GetId()));
        printf("Number of clients: %u\n", cur_num_);
        break;
      }
    }
  }

}

void* Server::ServClient(void *sock) {
  Socket *socket = static_cast<Socket*>(sock);
  char *message = new char[kMessageLen];

  while (socket->Receive(message, kMessageLen)) { // loop for receiving messages from client
    if (file_->IsValid()) {
      synchron_->Lock();      // Request ownership of the critical region in code
      file_->Write(message);  // Write message to file
      file_->Refresh();       // Reload file
      synchron_->Unlock();    // Release ownership of the critical region in code
    } else {
      // We don't terminates conversation if file is not valid,
      // just print message about this issue
      puts("Cannot open a file. Message doesn't saved.");
    }
    if (!SendToAll(socket, message)) {
      printf("Send failed with error: %d\n", socket->LastError());
      break;
    }
    if (strstr(message, "exit") != 0) { 
      break;
    }
  }
  DeleteClient(socket);
  delete[] message;
  return nullptr;
}

bool Server::SendToAll(Socket *socket, const char* buffer) {
  for (unsigned int cl = 0; cl < kClientNum; cl++) {  
    if (clients_[cl] == nullptr ||   // if index is free
        // or sockets is the same (it doesn't makes sense
        // to send a message from myself to myself)
        clients_[cl]->GetSocket() == socket->GetSocket()) {
		  continue;  // go to the next index
    }
    if (!clients_[cl]->Send(buffer, kMessageLen)) {
      return false;
    }
  }
  return true;
}

void Server::DeleteClient(Socket *socket) {
  for (unsigned int cl = 0; cl < kClientNum; cl++) {
    if (clients_[cl] == nullptr) {  // if index is empty
      continue;
    }
    if (clients_[cl]->GetSocket() == socket->GetSocket()) {  
      // Reached a socket that should be deleted
      puts("Client has left the convesation");
      SendToAll(socket, "Server: Client has left the convesation");
      clients_[cl]->CloseSocket();
      clients_[cl] = nullptr;  // Release an index of client's array
      cur_num_--;
      printf("Number of clients: %u\n", cur_num_);
      break;
    }
  }
}