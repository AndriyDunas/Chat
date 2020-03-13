// Copyright (c) 2015 GL Base Camp.
// @author Andriy Dunas
//
// Main function of programm.
// You can choose your role by running the app with the key:
// s - server, c - client.
// Also you can do it in console menu.
//
#include "server.h"
#include "client.h"

int main(int argc, char **argv) 
{
  char var;
  if (argc == 1) {
    printf("Type 's'(server) or 'c'(client): ");
    var = getchar(); 
    // Removing unwanted characters from stdin
    const unsigned int trash_length = 20;
    char *trash = new char[trash_length];
    fgets(trash, trash_length, stdin);
    delete[] trash;	
  }
  else {
    var = *argv[1];	   
  } 
  if (var == 's') {
    Server *server = new Server;
    if (argc == 3) {
      server->Run(argv[2]);  
    } else {
      server->Run("history.txt"); 
    }
    delete server;
  } else if (var == 'c') {
    Client *client = new Client;
    client->Run();
    delete client;
  } else {
    puts("Incorrect input!");
  }	
  return 0;
}
