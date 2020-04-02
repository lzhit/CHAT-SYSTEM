//FILE          : clientLList.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   : xlient linked list implementation

#include "../inc/clientLList.h"

//NAME        : insert
//DESCRIPTION : creates a new node in the list
//PARAMETERS  : int client_socket, char* ip - IP address
//RETURNS     : Client* - newly created client node
Client* insert(int client_socket, char* ip)
{
    Client* pNode = root; //root is global
    Client* newClient = (Client*) malloc (sizeof(Client));

    newClient->socket = client_socket;
    strncpy(newClient->ip, ip, IPLEN);
    strncpy(newClient->name, "NULL", NAMELEN);
    newClient->next = NULL;

    if(pNode == NULL)
    {
      pNode = newClient;
      pNode->next = NULL;
    }
    else
    {
      while(pNode->next != NULL)
      {
        pNode = pNode->next;
      }

      pNode->next = newClient;
    }

    return newClient;
}



//NAME        : delete
//DESCRIPTION : deletes a client from the linked list
//PARAMETERS  : Client* client - the client to delete
//RETURNS     : Client* - first node of the list
Client* delete(Client* client)
{
  Client* pNode = root; //root is global
  Client* preNode = NULL;

  if (root->socket == client->socket)
  {
    root = root->next;
  }
  else
  {
    while(pNode->socket != client->socket)
    {
      preNode = pNode;
      pNode = pNode->next;
    }

    preNode->next = pNode->next;
  }

  close(pNode->socket);
  free(pNode);
  return root;
}
