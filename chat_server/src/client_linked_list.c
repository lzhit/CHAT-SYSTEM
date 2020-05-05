//FILE          : client_linked_list.c
//PROJECT       : SENG2030 - Assignment 4
//AUTHOR        : Lidiia Zhitova
//FIRST VERSION : 2020-03-28

#include "../inc/client_linked_list.h"


//NAME        : insert
//DESCRIPTION : creates a new node in the list
//PARAMETERS  : int client_socket, char* ip - IP address
//RETURNS     : Client* - newly created client node
Client* insert(int client_socket, char* ip)
{
    Client* p_node = root; //root is global
    Client* new_client = (Client*) malloc (sizeof(Client));

    new_client->socket = client_socket;
    strncpy(new_client->ip, ip, IP_LENGTH);
    strncpy(new_client->name, "NULL", NAME_LENGTH);
    new_client->next = NULL;

    if(p_node == NULL)
    {
      p_node = new_client;
      p_node->next = NULL;
    }
    else
    {
      while(p_node->next != NULL)
      {
        p_node = p_node->next;
      }

      p_node->next = new_client;
    }

    return new_client;
}



//NAME        : delete
//DESCRIPTION : deletes a client from the linked list
//PARAMETERS  : Client* client - the client to delete
//RETURNS     : Client* - first node of the list
Client* delete(Client* client)
{
  Client* p_node = root; //root is global
  Client* prev_node = NULL;

  if (root->socket == client->socket)
  {
    root = root->next;
  }
  else
  {
    while(p_node->socket != client->socket)
    {
      prev_node = p_node;
      p_node = p_node->next;
    }

    prev_node->next = p_node->next;
  }

  close(p_node->socket);
  free(p_node);
  return root;
}
