//FILE          : chat-client.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   :

#include "../inc/chat-client.h"
#include "../inc/ncursesUI.h"

int main(int argc, char* argv[])
{
  int                my_server_socket;
  char                userID[5];
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

  //setupUI(&msg_win, &chat_win);

  /*
   * initialize struct to get a socket to host
   */
  memset (&server_addr, 0, sizeof (server_addr));
  server_addr.sin_family = AF_INET;
  memcpy (&server_addr.sin_addr, host->h_addr, host->h_length);
  server_addr.sin_port = htons (PORT);

  /*
  * get a socket for communications
  */
  fflush(stdout);
  if ((my_server_socket = socket (AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf ("[CLIENT] : Getting Client Socket - FAILED\n");
    return 3;
  }


  /*
   * attempt a connection to server
   */
  if (connect (my_server_socket, (struct sockaddr *)&server_addr,sizeof (server_addr)) < 0)
  {
    printf ("[CLIENT] : Connect to Server - FAILED\n");
    close (my_server_socket);
    return 4;
  }

  //send the user ID first
  send(my_server_socket, userID, 5, 0);

  start_ncurses();

  if (pthread_create(&(tid[0]), NULL, inputThread, (void*)&my_server_socket))
  {
    printf ("[SERVER] : pthread_create() FAILED\n");
    fflush(stdout);
    exit(5);
  }

  if (pthread_create(&(tid[1]), NULL, outputThread, (void*)&my_server_socket))
  {
    printf ("[SERVER] : pthread_create() FAILED\n");
    fflush(stdout);
    exit(5);
  }

  pthread_join(tid[0], NULL);
  pthread_cancel(tid[1]);
  endwin();
  close (my_server_socket);
  return 0;
}



//NAME        :
//DESCRIPTION :
//PARAMETERS  :
//RETURNS     :
void *inputThread(void* server_socket)
{
  int* my_server_socket = (int*) server_socket;
  int done = 1;
  int len = 0;
  char buffer[BUFLEN] = "";
  WINDOW *chat_win;
  setupChatW(&chat_win);

  while(done)
  {

    input_win(chat_win, buffer);

  	/* check if the user wants to quit */
	  if(strcmp(buffer,">>bye<<") == 0)
	  {
		  done = 0;
	  }

    write (*my_server_socket, buffer, strlen (buffer));

    /* clear out the contents of buffer (if any) */
    memset(buffer, 0, BUFLEN);
  }
  destroy_win(chat_win);
  close(*my_server_socket);
}



//NAME        :
//DESCRIPTION :
//PARAMETERS  :
//RETURNS     :
void *outputThread(void* server_socket)
{
  int* my_server_socket = (int*) server_socket;
  int len = 0;
  char buffer[BUFLEN];
  WINDOW *msg_win;
  setupMsgW(&msg_win);

  while(1)
  {
    /* clear out the contents of buffer (if any) */
    memset(buffer,0,BUFLEN);

		len = read (*my_server_socket, buffer, BUFLEN);
    int i = checkPattern(buffer);
    // printf("%s", buffer);
    //printf("%d ", i);
    if((strcmp(buffer, "") != 0) && (i == 0))
    {
      display_win(msg_win, buffer);
    }
  }
    destroy_win(msg_win);
}



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
          //printf("%c, %d", c, i);
          return -1;
        }
        break;
      case 15:
      case 23:
      case 26:
        if (c != ' ')
        {
          //printf("[%c, %d]", c, i);
          return -1;
        }
        break;
      case 16:
        if (c != '[')
        {
          //printf("[%c, %d]", c, i);
          return -1;
        }
        break;
      case 22:
        if (c != ']')
        {
          //printf("[%c, %d]", c, i);
          return -1;
        }
        break;
      case 24:
      case 25:
        if (c != '<' && c != '>')
        {
          //printf("[%c, %d]", c, i);
          return -1;
        }
        break;
      default:
        break;
    }
  }
      return 0;
}
