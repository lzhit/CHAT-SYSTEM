//FILE          : chat_server.c
//PROJECT       : SENG2030 - Assignment 4
//AUTHOR        : Lidiia Zhitova
//FIRST VERSION : 2020-03-28

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


#include "../inc/chat_server.h"
#include "../inc/client_linked_list.h"


int main (int argc, char* argv[])
{
  number_of_current_clients = -1;

  //set up a watch dog which will keep track of client connections and shut down
  //the server when the number of connections becomes 0
  signal (SIGALRM, alarm_handler);
  alarm (2);

  //initialize server and start acceptig clients
  initialize_server(&server_socket); // server_socket is global
  accept_client(server_socket);

  close (server_socket);
  return 0;
}



//NAME        : alarmHandler
//DESCRIPTION : exits the program when number of clients becomes 0 (updates every 2s)
//PARAMETERS  : int signal_number
//RETURNS     : void
void alarm_handler(int signal_number)
{
  if(number_of_current_clients == 0)
  {
     close(server_socket);
     exit(0);
  }
  signal (signal_number, alarm_handler);
  alarm (2);	// reset alarm
}
