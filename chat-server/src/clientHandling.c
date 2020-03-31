//FILE          : clientHandling.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   : client thread


#include "../inc/chat-server.h"
#include "../inc/clientLList.h"


//NAME        : socketThread
//DESCRIPTION : recieves messages from client and sends them to a broadcasting function
//PARAMETERS  : void *client - client node from Client linked list
//RETURNS     : void*
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

  // Clear out the input Buffer
  memset(buffer,0,BUFSIZ);

  // increment the numClients
  int iAmClient = numClients;	// assumes that another connection from another client
				// hasn't been created in the meantime

  read (clSocket, buffer, BUFSIZ);

  while(strcmp(buffer,">>bye<<") != 0 && strcmp(buffer, "") != 0)
  {
    sprintf(message, "%s_[%s]_>>_%s_timegoeshere\n", p_client->ip, p_client->name, buffer);
    broadcast_msg(client, message);

    // clear out and get the next command and process
    memset(buffer,0,BUFSIZ);
    read (clSocket, buffer, BUFSIZ);
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
void broadcast_msg(Client* this_client, char msg[])
{
    Client* tmp = root->next;
    while (tmp != NULL)
    {
        if (this_client->socket != tmp->socket) // all clients except itself.
        {
            send(tmp->socket, msg, BUFSIZ, 0);
        }
        tmp = tmp->next;
    }
}
