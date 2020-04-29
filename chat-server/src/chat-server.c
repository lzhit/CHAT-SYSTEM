//FILE          : chat-server.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   : main function for server program

/*
  - the client connections are stored in a linked list
  - each linked list node contains info about the client's IP address, its user ID,
  the socket and a pointer to the next client node
  - a client's IP address is obtained through getpeername function
  - the first message the client sends is the userID - the server will store this name
  in the client's node upon recieving
  - upon recieving the >>bye<< message, the server's listening loop for the given
  client will stop, the client's socket will be closed, and the thread will be exited
  - when the number of clients goes down to 0, the application closes the server
  socket and exits (which is done with the help of a watch dog)
*/


#include "../inc/chat-server.h"
#include "../inc/clientLList.h"


int main (int argc, char* argv[])
{
  //set up a watch dog which will keep track of client connections and shut down
  //the server when the number of connections becomes 0
  signal (SIGALRM, alarmHandler);
  alarm (2);

  //initialize server and start acceptig clients
  initServer(&server_socket);
  acceptClient(server_socket);

  close (server_socket);
  return 0;
}
