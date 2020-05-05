//FILE          : inputHandling.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   : contains an input thread function and a function which starts the thread

#include "../inc/chat_client.h"
#include "../inc/ncurses_UI.h"



//NAME        : startInputThread
//DESCRIPTION : creates and starts the input thread
//PARAMETERS  : pthread_t *thread
//              int my_server_socket - pointer to the server socket
//RETURNS     : void
void start_input_thread(pthread_t* thread, int *server_socket)
{
  if (pthread_create(thread, NULL, input_thread, (void*)&(*server_socket)))
  {
    printf ("[SERVER] : pthread_create() FAILED\n");
    fflush(stdout);
    exit(5);
  }
}



//NAME        : inputThread
//DESCRIPTION : a thread functoin that is responsible for collecting input and sending it to the server
//PARAMETERS  : void * server_socket - pointer to the server socket
//RETURNS     : void
void *input_thread(void* socket)
{
  int* server_socket = (int*) socket;
  int done = 0;
  WINDOW *chat_window;
  char message[MESSAGE_SIZE] = "";
  char second_half_of_message[BUFFLEN] = ""; // if the message the user wants to send
                                             // is longer than 40 characters, the
                                             // message will be divided into 2


  setup_chat_window(&chat_window);

  while(done == 0)
  {

    input_window(chat_window, message);

  	/* check if the user wants to quit */
	  if(strcmp(message, ">>bye<<") == 0)
	  {
		  done = 1;
	  }

    if (strlen (message) > BUFFLEN)
    {
      memcpy(second_half_of_message, message + BUFFLEN, BUFFLEN);
      message[BUFFLEN] = '\0';
      write (*server_socket, message, strlen (message));
      write (*server_socket, second_half_of_message, strlen (second_half_of_message));
      memset(second_half_of_message, 0, MESSAGE_SIZE); // clear out the contents
    }
    else
    {
          write (*server_socket, message, strlen (message));
    }

    /* clear out the contents of message (if any) */
    memset(message, 0, MESSAGE_SIZE);
  }

  destroy_window(chat_window);
  close(*server_socket);
}
