//FILE          : chat-client.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   : main for the chat-client


#include "../inc/chat-client.h"
#include "../inc/ncursesUI.h"

int main(int argc, char* argv[])
{
  int                my_server_socket;
  char               userID[5];
  struct sockaddr_in server_addr;
  struct hostent*    host;
  pthread_t	         tid[2];


  /*
   * check for sanity
   */
  if (argc != 3)
  {
    printf ("USAGE : chat-client <userID> <server_IP>\n");
    return 1;
  }

  memcpy(userID, argv[1], 5);

  /*
   * determine host info for server name supplied
   */
  if ((host = gethostbyname (argv[2])) == NULL)
  {
    printf ("[%s] : Host Info Search - FAILED\n",userID);
    return 2;
  }

  // establish a connection with the server
  initAddr(&server_addr, &host);
  getSocket(&my_server_socket);
  connectServer(&my_server_socket, &server_addr);

  //share the user ID with the server
  send(my_server_socket, userID, 5, 0);

  start_ncurses();

  startInputThread(&tid[0], &my_server_socket);
  startOutputThread(&(tid[1]), &my_server_socket);

  pthread_join(tid[0], NULL);
  pthread_cancel(tid[1]);
  endwin();
  close (my_server_socket);

  return 0;
}
