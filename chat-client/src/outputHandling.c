//FILE          : outputHandling.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   : contains an output thread function and a function which starts the thread

#include "../inc/chat-client.h"
#include "../inc/ncursesUI.h"



//NAME        : startOutputThread
//DESCRIPTION : creates and starts the output thread
//PARAMETERS  : pthread_t *thread
//              int my_server_socket - pointer to the server socket
//RETURNS     : void
void startOutputThread(pthread_t* thread, int* my_server_socket)
{
  if (pthread_create(thread, NULL, outputThread, (void*)&(*my_server_socket)))
  {
    printf ("[SERVER] : pthread_create() FAILED\n");
    fflush(stdout);
    exit(5);
  }
}



//NAME        : outputThread
//DESCRIPTION : thread fucntion that is responsible for reading the incoming messages and displaying them
//PARAMETERS  : void * server_socket - pointer to the server socket
//RETURNS     : void
void *outputThread(void* server_socket)
{
  int* my_server_socket = (int*) server_socket;
  int len = 0;
  char buffer[MSGSIZ];
  WINDOW *msg_win;
  setupMsgW(&msg_win);

  while(1)
  {
    /* clear out the contents of buffer (if any) */
    memset(buffer, 0, MSGSIZ);
		len = read (*my_server_socket, buffer, MSGSIZ);
    int i = checkPattern(buffer);
    if((strcmp(buffer, "") != 0) && (i == 0)) // only display message if it has the correct pattern
    {
      display_win(msg_win, buffer);
    }
  }
    destroy_win(msg_win);
}



//NAME        : checkPattern
//DESCRIPTION : checks the pattern of the message is correct
//PARAMETERS  : char string[] - the message to check
//RETURNS     : int 0 if the pattern is correct, -1 otherwise
int checkPattern(char string[])
{
  for (int i = 0; i <= 26; i++)
  {
    char c = string[i];

    switch(i)
    {
      case 0:
        if (!isdigit(c))
        {
          return -1;
        }
        break;
      case 15:
      case 23:
      case 26:
        if (c != ' ')
        {
          return -1;
        }
        break;
      case 16:
        if (c != '[')
        {
          return -1;
        }
        break;
      case 22:
        if (c != ']')
        {
          return -1;
        }
        break;
      case 24:
      case 25:
        if (c != '<' && c != '>')
        {
          return -1;
        }
        break;
      default:
        break;
    }
  }
      return 0;
}
