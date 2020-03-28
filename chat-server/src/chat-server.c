//FILE          : chat-server.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   :


#include "../inc/chat-server.h"

// global variable to keep count of the number of clients ...
static int numClients = 0;
Client *root;
Client *current;

int main (int argc, char* argv[])
{
  int                server_socket, client_socket;
  int                client_len;
  struct sockaddr_in client_addr, server_addr;
  int                len, i;
  pthread_t	         tid[3];
  int                whichClient;

  int shmid;
	key_t shmem_key;
	MSGINFO *msg;
	int x;

  /*
   * obtain a socket for the server
   */

  if ((server_socket = socket (AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf ("[SERVER] : socket() FAILED\n");
    return 1;
  }
  printf("[SERVER] : socket() successful\n");

  /*
   * initialize our server address info for binding purposes
   */
  memset (&server_addr, 0, sizeof (server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = htonl (INADDR_ANY);
  server_addr.sin_port = htons (PORT);

  if (bind (server_socket, (struct sockaddr *)&server_addr, sizeof (server_addr)) < 0)
  {
    printf ("[SERVER] : bind() FAILED\n");
    close (server_socket);
    return 2;
  }
  printf ("[SERVER] : bind() successful\n");

  /*
   * start listening on the socket
   */
  if (listen (server_socket, 5) < 0)
  {
    printf ("[SERVER] : listen() - FAILED.\n");
    close (server_socket);
    return 3;
  }
  printf ("[SERVER] : listen() successful\n");

  // Initial linked list for clients
   root = newNode(server_socket, inet_ntoa(server_addr.sin_addr));
   current = root;


  while (numClients < 10)
  {
    printf("[SERVER] : Ready to accept()\n");
    fflush(stdout);

    /*
  	 * accept a packet from the client
  	 */
  	client_len = sizeof (client_addr);
  	if ((client_socket = accept (server_socket,(struct sockaddr *)&client_addr, &client_len)) < 0)
  	{
            printf ("[SERVER] : accept() FAILED\n");
            fflush(stdout);
            return 4;
  	}

    getpeername(client_socket,(struct sockaddr *)&client_addr, &client_len);

    // Store the client info in the linked list
    Client *c = newNode(client_socket, inet_ntoa(client_addr.sin_addr));
    c->prev = current;
    current->next = c;
    current = c;
    numClients++;


    if (pthread_create(&(tid[(numClients-1)]), NULL, socketThread, (void *)c))
    {
      printf ("[SERVER] : pthread_create() FAILED\n");
      fflush(stdout);
      return 5;
    }

    printf("[SERVER] : pthread_create() successful for CLIENT-%02d\n", numClients);
    fflush(stdout);


    }

    // once we reach 3 clients - let's go into a busy "join" loop waiting for
    // all of the clients to finish and join back up to this main thread
    printf("\n[SERVER] : Now we wait for the threads to complete ... \n");
    for(i=0; i<3; i++)
    {
          if(pthread_join(tid[i], (void *)(&whichClient)))
          {
             printf("[SERVER] : pthread_join() FAILED\n");
             return 6;
          }
    printf("\n[SERVER] : received QUIT command from CLIENT-%02d\n", whichClient);
    }

    printf("\n[SERVER] : All clients have returned - exiting ...\n");
    close (server_socket);
    return 0;


}





void *socketThread(void *client)
{
  // used for accepting incoming command and also holding the command's response
  char buffer[BUFSIZ];
  char message[BUFSIZ];
  int sizeOfRead;
  int timeToExit;
  Client *p_client = (Client *) client;


  // remap the clientSocket value (which is a void*) back into an INT
  int clSocket = p_client->socket;

  /* Clear out the input Buffer */
  memset(buffer,0,BUFSIZ);

  // increment the numClients
  int iAmClient = numClients;	// assumes that another connection from another client
				// hasn't been created in the meantime

  read (clSocket, buffer, BUFSIZ);

  while(strcmp(buffer,">>bye<<") != 0 && strcmp(buffer, ""))
  {
    /* we're actually not going to execute the command - but we could if we wanted */
    sprintf (message, "[SERVER (Thread-%02d)] : Received the command - %s\n", iAmClient, buffer);
    printf("%s", message);
    sprintf(message, "%s_[%s]_>>_%s_timegoeshere\n", p_client->ip, p_client->name, buffer);
    send_to_all_clients(client, message);

    // clear out and get the next command and process
    memset(buffer,0,BUFSIZ);
    read (clSocket, buffer, BUFSIZ);
  }
  close(clSocket);

  // decrement the number of clients
  numClients--;

  // Remove Node
    close(p_client->socket);
    if (p_client == current) { // remove an edge node
        current = p_client->prev;
        current->next = NULL;
    } else { // remove a middle node
        p_client->prev->next = p_client->next;
        p_client->next->prev = p_client->prev;
    }
    free(p_client);

  // the return status will be the client # of this thread
  timeToExit = iAmClient;
  pthread_exit((void *)(timeToExit));
  printf ("[SERVER (Thread-%02d)] : closing socket\n", iAmClient);

  return 0;
}


void send_to_all_clients(Client *this_client, char msg[])
{
    Client *tmp = root->next;
    while (tmp != NULL)
    {
        if (this_client->socket != tmp->socket) // all clients except itself.
        {
            printf("Send to sockfd %d: \"%s\" \n", tmp->socket, msg);
            send(tmp->socket, msg, BUFSIZ, 0);
        }
        tmp = tmp->next;
    }
}
