//FILE          : connection_manager.c
//PROJECT       : SENG2030 - Assignment 4
//AUTHOR        : Lidiia Zhitova
//FIRST VERSION : 2020-03-28


#include "../inc/chat_client.h"



//NAME        : get_server_address
//DESCRIPTION : initialize struct to get a socket to host
//PARAMETERS  : struct sockaddr_in* server_address
//              struct hostent** host
//RETURNS     : void
void get_server_address(struct sockaddr_in* server_address, struct hostent** host)
{
  memset (&(*server_address), 0, sizeof (*server_address));
  (*server_address).sin_family = AF_INET;
  memcpy (&(*server_address).sin_addr, (*host)->h_addr, (*host)->h_length);
  (*server_address).sin_port = htons (PORT);
}



//NAME        : get_socket
//DESCRIPTION : get a socket for communications
//PARAMETERS  : int *server_socket
//RETURNS     : void
void get_socket(int *server_socket)
{
  fflush(stdout);
  if ((*server_socket = socket (AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf ("[CLIENT] : Getting Client Socket - FAILED\n");
    exit(3);
  }
}



//NAME        : connect_to_server
//DESCRIPTION : attempt a connection to server
//PARAMETERS  : int *server_socket
//              struct sockaddr *server_address
//RETURNS     : void
void connect_to_server(int *server_socket, struct sockaddr_in *server_address)
{
  if (connect (*server_socket, (struct sockaddr *)&(*server_address),sizeof (*server_address)) < 0)
  {
    printf ("[CLIENT] : Connect to Server - FAILED\n");
    close (*server_socket);
    exit(4);
  }
}
