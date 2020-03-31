//FILE          : chat-server.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   : main function for server program


#include "../inc/chat-server.h"
#include "../inc/clientLList.h"


int main (int argc, char* argv[])
{
  int server_socket;

  //set up a watch dog
  signal (SIGALRM, alarmHandler);
  alarm (2);

  //initialize server and start acceptig clients
  initServer(&server_socket);
  acceptClient(server_socket);

  close (server_socket);
  return 0;
}
