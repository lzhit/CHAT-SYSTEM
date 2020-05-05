//FILE          : outputHandling.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   : contains an output thread function and a function which starts the thread

#include "../inc/chat_client.h"
#include "../inc/ncurses_UI.h"



//NAME        : start_output_thread
//DESCRIPTION : creates and starts the output thread
//PARAMETERS  : pthread_t *thread
//              int my_server_socket - pointer to the server socket
//RETURNS     : void
void start_output_thread(pthread_t* thread, int* server_socket)
{
  if (pthread_create(thread, NULL, output_thread, (void*)&(*server_socket)))
  {
    printf ("[SERVER] : pthread_create() FAILED\n");
    fflush(stdout);
    exit(5);
  }
}



//NAME        : output_thread
//DESCRIPTION : thread fucntion that is responsible for reading the incoming messages and displaying them
//PARAMETERS  : void * server_socket - pointer to the server socket
//RETURNS     : void
void *output_thread(void* socket)
{
  int* server_socket = (int*) socket;
  int received_data_length = 0;
  char message[MESSAGE_SIZE];
  WINDOW *message_window;
  setup_message_window(&message_window);

  while(1)
  {
    /* clear out the contents of buffer (if any) */
    memset(message, 0, MESSAGE_SIZE);
		received_data_length = read (*server_socket, message, MESSAGE_SIZE);
    int is_correct_pattern = check_pattern(message);
    if((strcmp(message, "") != 0) && (is_correct_pattern == 0)) // only display message if it has the correct pattern
    {
      display_window(message_window, message);
    }
  }
    destroy_window(message_window);
}



//NAME        : check_pattern
//DESCRIPTION : checks the pattern of the message is correct
//PARAMETERS  : char string[] - the message to check
//RETURNS     : int 0 if the pattern is correct, -1 otherwise
int check_pattern(char string[])
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
