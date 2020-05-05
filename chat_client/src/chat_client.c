//FILE          : chat_client.c
//PROJECT       : SENG2030 - Assignment 4
//AUTHOR        : Lidiia Zhitova
//FIRST VERSION : 2020-03-28


#include "../inc/chat_client.h"
#include "../inc/ncurses_UI.h"

int main(int argc, char* argv[])
{
  int                server_socket;
  char               user_id[5];
  struct sockaddr_in server_address;
  struct hostent*    host;
  pthread_t	         thread_ids[2];


  /*
   * check for sanity
   */
  if (argc != 3)
  {
    printf ("USAGE : chat_client <user_ID> <server_IP>\n");
    return 1;
  }

  memcpy(user_id, argv[1], 5);

  /*
   * determine host info for server name supplied
   */
  if ((host = gethostbyname (argv[2])) == NULL)
  {
    printf ("[%s] : Host Info Search - FAILED\n",user_id);
    return 2;
  }

  // establish a connection with the server
  get_server_address(&server_address, &host);
  get_socket(&server_socket);
  connect_to_server(&server_socket, &server_address);

  //share the user ID with the server
  send(server_socket, user_id, 5, 0);

  start_ncurses();

  start_input_thread(&thread_ids[0], &server_socket);
  start_output_thread(&(thread_ids[1]), &server_socket);

  pthread_join(thread_ids[0], NULL);
  pthread_cancel(thread_ids[1]);
  endwin();
  close (server_socket);

  return 0;
}
