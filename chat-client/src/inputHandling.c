//FILE          : inputHandling.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   : contains an input thread function and a function which starts the thread

#include "../inc/chat-client.h"
#include "../inc/ncursesUI.h"



//NAME        : startInputThread
//DESCRIPTION : creates and starts the input thread
//PARAMETERS  : pthread_t *thread
//              int my_server_socket - pointer to the server socket
//RETURNS     : void
void startInputThread(pthread_t* thread, int *my_server_socket)
{
  if (pthread_create(thread, NULL, inputThread, (void*)&(*my_server_socket)))
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
void *inputThread(void* server_socket)
{
  int* my_server_socket = (int*) server_socket;
  int done = 1;
  int len = 0;
  char buffer[MSGSIZ] = "";
  WINDOW *chat_win;
  setupChatW(&chat_win);

  char buffer2[BUFFLEN] = "";


  while(done)
  {

    input_win(chat_win, buffer);

  	/* check if the user wants to quit */
	  if(strcmp(buffer,">>bye<<") == 0)
	  {
		  done = 0;
	  }

    if (strlen (buffer) > BUFFLEN)
    {
      memcpy(buffer2, buffer + BUFFLEN, BUFFLEN);
      buffer[BUFFLEN] = '\0';
      write (*my_server_socket, buffer, strlen (buffer));
      write (*my_server_socket, buffer2, strlen (buffer2));
      memset(buffer2, 0, MSGSIZ);
    }
    else
    {
          write (*my_server_socket, buffer, strlen (buffer));
    }

    /* clear out the contents of buffer (if any) */
    memset(buffer, 0, MSGSIZ);
  }
  destroy_win(chat_win);
  close(*my_server_socket);
}
