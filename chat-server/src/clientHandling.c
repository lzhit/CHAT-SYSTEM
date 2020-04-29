//FILE          : clientHandling.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   : client thread


#include "../inc/chat-server.h"
#include "../inc/clientLList.h"


//NAME        : acceptClient
//DESCRIPTION : accepts packets from the clients and starts threads for them
//PARAMETERS  : int server_socket
//RETURNS     : void
void acceptClient(int server_socket)
{
  int                 client_len;
  int                 client_socket;
  struct sockaddr_in  client_addr;
  pthread_t	      tid[10];
  int                 whichClient;
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



//NAME        : socketThread
//DESCRIPTION : recieves messages from client and sends them to a broadcasting function
//PARAMETERS  : void *client - client node from Client linked list
//RETURNS     : void*
void *socketThread(void *client)
{
  // used for accepting incoming command and also holding the command's response
  char buffer[BUFFSIZ];
  int sizeOfRead;
  int timeToExit;
  Client *p_client = (Client *) client;


  // remap the clientSocket value (which is a void*) back into an INT
  int clSocket = p_client->socket;

  // Clear out the input Buffer
  memset(buffer,0,BUFFSIZ);

  // increment the numClients
  int iAmClient = numClients;	// assumes that another connection from another client
				// hasn't been created in the meantime

  //get the client user name / user ID
  if (recv(p_client->socket, p_client->name, NAMELEN, 0) <= 0)
  {
    send(p_client->socket, "Error: user ID is invalid\n", BUFFSIZ, 0);
    strcpy(buffer, "");
  }
  else
  {
      read (clSocket, buffer, BUFFSIZ);
  }

  while(strcmp(buffer,">>bye<<") != 0 && strcmp(buffer, "") != 0)
  {
    broadcast_msg(client, buffer);

    // clear out and get the next command and process
    memset(buffer,0,BUFFSIZ);
    read (clSocket, buffer, BUFFSIZ);
  }
  close(clSocket);

  // decrement the number of clients
  delete(p_client);
  numClients--;

  // the return status will be the client # of this thread
  timeToExit = iAmClient;
  pthread_exit((void *)(timeToExit));

  return 0;
}



//NAME        : broadcast_msg
//DESCRIPTION : sends a message to all clients except for the client passed as a param
//PARAMETERS  : Client* this_client - the client not to send a message to
//              char msg - message to send
//RETURNS     : void
void broadcast_msg(Client* this_client, char buffer[])
{
    Client* tmp = root->next;
    char message[MSGSIZ];
    time_t rawtime;
    struct tm * timeinfo;

    //get the local time
    time ( &rawtime );
    timeinfo = localtime ( &rawtime );
    while (tmp != NULL)
    {
        //send the message to all clients except sender
        if (this_client->socket != tmp->socket)
        {
          sprintf(message, "%-15s [%-5s] >> %-40s (%d:%d:%d)", this_client->ip, this_client->name, buffer, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
          write(tmp->socket, message, MSGSIZ);
        }
        else //send to sender (this message has the '<<' instead of the '>>')
        {
          sprintf(message, "%-15s [%-5s] << %-40s (%d:%d:%d)", this_client->ip, this_client->name, buffer, timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
          write(tmp->socket, message, MSGSIZ);
        }

        tmp = tmp->next;
    }
}
