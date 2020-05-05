//FILE          : server_setup.c
//PROJECT       : SENG2030 - Assignment 4
//AUTHOR        : Lidiia Zhitova
//FIRST VERSION : 2020-03-28

#include "../inc/chat_server.h"
#include "../inc/client_linked_list.h"



//NAME        : initialize_server
//DESCRIPTION : obtains a socket, inititalizes server and sets up a listener
//PARAMETERS  : int* server_socket - reference to server socket variable
//RETURNS     : void
void initialize_server(int* server_socket)
{
  struct sockaddr_in server_address;

  // obtain a socket for the server
  if ((*server_socket = socket (AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf ("[SERVER] : socket() FAILED\n");
    exit(1);
  }

  // initialize our server address info for binding purposes
  memset (&server_address, 0, sizeof (server_address));
  server_address.sin_family = AF_INET;
  server_address.sin_addr.s_addr = htonl (INADDR_ANY);
  server_address.sin_port = htons (PORT);

  if (bind (*server_socket, (struct sockaddr*)&server_address, sizeof (server_address)) < 0)
  {
    printf ("[SERVER] : bind() FAILED\n");
    close (*server_socket);
    exit(2);
  }

  // start listening on the socket
  if (listen (*server_socket, 5) < 0)
  {
    printf ("[SERVER] : listen() - FAILED.\n");
    close (*server_socket);
    exit(3);
  }

  // Initialize the linked list for storing clients
  // root is global
  root = insert(*server_socket, inet_ntoa(server_address.sin_addr));

}
