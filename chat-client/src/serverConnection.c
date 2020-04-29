//FILE          : serverConnection.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   : contains functions which help to establish a connection with a server


#include "../inc/chat-client.h"



//NAME        : initAddr
//DESCRIPTION : initialize struct to get a socket to host
//PARAMETERS  : struct sockaddr_in* server_addr -
//              struct hostent** host
//RETURNS     : void
void initAddr(struct sockaddr_in* server_addr, struct hostent** host)
{
  memset (&(*server_addr), 0, sizeof (*server_addr));
  (*server_addr).sin_family = AF_INET;
  memcpy (&(*server_addr).sin_addr, (*host)->h_addr, (*host)->h_length);
  (*server_addr).sin_port = htons (PORT);
}



//NAME        : getSocket
//DESCRIPTION : get a socket for communications
//PARAMETERS  : int *my_server_socket
//RETURNS     : void
void getSocket(int *my_server_socket)
{
  fflush(stdout);
  if ((*my_server_socket = socket (AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf ("[CLIENT] : Getting Client Socket - FAILED\n");
    exit(3);
  }
}



//NAME        : connectServer
//DESCRIPTION : attempt a connection to server
//PARAMETERS  : int *my_server_socket
//              struct sockaddr *server_addr
//RETURNS     : void
void connectServer(int *my_server_socket, struct sockaddr_in *server_addr)
{
  if (connect (*my_server_socket, (struct sockaddr *)&(*server_addr),sizeof (*server_addr)) < 0)
  {
    printf ("[CLIENT] : Connect to Server - FAILED\n");
    close (*my_server_socket);
    exit(4);
  }
}
