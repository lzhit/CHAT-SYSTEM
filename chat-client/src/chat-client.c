//FILE          : chat-client.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   :

#include "../inc/chat-client.h"


int main(int argc, char* argv[])
{
  int                my_server_socket, len, done;
  int                whichClient;
  struct sockaddr_in server_addr;
  struct hostent*    host;

  /*
   * check for sanity
   */
  if (argc != 3)
  {
    printf ("USAGE : tcpipClient <clientID> <server_name>\n");
    return 1;
  }

  whichClient = atoi(argv[1]);

  /*
   * determine host info for server name supplied
   */
  if ((host = gethostbyname (argv[2])) == NULL)
  {
    printf ("[CLIENT-%d] : Host Info Search - FAILED\n",whichClient);
    return 2;
  }

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
  printf ("[CLIENT] : Getting STREAM Socket to talk to SERVER\n");
  fflush(stdout);
  if ((my_server_socket = socket (AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf ("[CLIENT] : Getting Client Socket - FAILED\n");
    return 3;
  }


  /*
   * attempt a connection to server
   */
  printf ("[CLIENT] : Connecting to SERVER\n");
  fflush(stdout);
  if (connect (my_server_socket, (struct sockaddr *)&server_addr,sizeof (server_addr)) < 0)
  {
    printf ("[CLIENT] : Connect to Server - FAILED\n");
    close (my_server_socket);
    return 4;
  }

  done = 1;
  while(done)
  {
    /* clear out the contents of buffer (if any) */
    memset(buffer,0,BUFSIZ);

   /*
    * now that we have a connection, get a commandline from
    * the user, and fire it off to the server
    */
	   memset(buffer,0,BUFSIZ);
	   printf (">> ");
	   fflush (stdout);
	   fgets (buffer, BUFSIZ, stdin);
	   if (buffer[strlen (buffer) - 1] == '\n') buffer[strlen (buffer) - 1] = '\0';

  	 /* check if the user wants to quit */
	   if(strcmp(buffer,">>bye<<") == 0)
	   {
	     // send the command to the SERVER
		   fflush (stdout);
		   write (my_server_socket, buffer, strlen (buffer));
		   done = 0;
	   }
	   else
	   {
	     write (my_server_socket, buffer, strlen (buffer));
		   memset(buffer,0,BUFSIZ);
		   len = read (my_server_socket, buffer, BUFSIZ);
		   printf ("<< %s\n", buffer);
		  fflush (stdout);
	   }
   }

  return 0;
}
