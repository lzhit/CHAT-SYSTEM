//FILE          : chat-server.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   : functions that initialize the server and listens for clients

#include "../inc/chat-server.h"
#include "../inc/clientLList.h"



//NAME        : initServer
//DESCRIPTION : obtains a socket, inititalizes server and sets up a listener
//PARAMETERS  : int* server_socket - reference to server socket variable
//RETURNS     : void
void initServer(int* server_socket)
{
  struct sockaddr_in server_addr;

  // obtain a socket for the server
  if ((*server_socket = socket (AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf ("[SERVER] : socket() FAILED\n");
    exit(1);
  }

  // initialize our server address info for binding purposes
  memset (&server_addr, 0, sizeof (server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl (INADDR_ANY);
  server_addr.sin_port = htons (PORT);

  if (bind (*server_socket, (struct sockaddr*)&server_addr, sizeof (server_addr)) < 0)
  {
    printf ("[SERVER] : bind() FAILED\n");
    close (*server_socket);
    exit(2);
  }

  // start listening on the socket
  if (listen (*server_socket, 5) < 0)
  {
    printf ("[SERVER] : listen() - FAILED.\n");
    close (*server_socket);
    exit(3);
  }

  // Initial linked list for clients
  root = insert(*server_socket, inet_ntoa(server_addr.sin_addr));

}




//NAME        : acceptClient
//DESCRIPTION : accepts packets from the clients and starts threads for them
//PARAMETERS  : int server_socket
//RETURNS     : void
void acceptClient(int server_socket)
{
  int                client_len;
  int                client_socket;
  struct sockaddr_in client_addr;
  pthread_t	         tid[10];
  int                whichClient;
                     numClients = -1;

  while (numClients < 10)
  {
    // accept a packet from the client
    client_len = sizeof (client_addr);
    if ((client_socket = accept (server_socket,(struct sockaddr *)&client_addr, &client_len)) < 0)
    {
      printf ("[SERVER] : accept() FAILED\n");
      fflush(stdout);
      exit(4);
    }

    getpeername(client_socket,(struct sockaddr *)&client_addr, &client_len);

    // Store the client info in the linked list
    Client *c = insert(client_socket, inet_ntoa(client_addr.sin_addr));

    if (numClients == -1 )
    {
      numClients = 1;
    }
    else
    {
      printf ( "%d\n", numClients);
      numClients++;
    }

    if (pthread_create(&(tid[(numClients-1)]), NULL, socketThread, (void *)c))
    {
      printf ("[SERVER] : pthread_create() FAILED\n");
      fflush(stdout);
      exit(5);
    }
  }

  printf("\n[SERVER] : Now we wait for the threads to complete ... \n");
  for(int i=0; i<10; i++)
  {
    pthread_join(tid[i], (void *)(&whichClient));
  }
}



//NAME        : alarmHandler
//DESCRIPTION : exits the program when number of clients becomes 0 (updates every 2s)
//PARAMETERS  : int signal_number
//RETURNS     : void
void alarmHandler(int signal_number)
{
  if(numClients == 0)
  {
     exit(-1);
  }
  signal (signal_number, alarmHandler);
  alarm (2);	// reset alarm
}
