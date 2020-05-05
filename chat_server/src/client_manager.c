//FILE          : client_manager.c
//PROJECT       : SENG2030 - Assignment 4
//AUTHOR        : Lidiia Zhitova
//FIRST VERSION : 2020-03-28


#include "../inc/chat_server.h"
#include "../inc/client_linked_list.h"


//NAME        : acceptClient
//DESCRIPTION : accepts packets from the clients and starts threads for them
//PARAMETERS  : int server_socket
//RETURNS     : void
void accept_client(int server_socket)
{
  int                 address_length;
  int                 client_socket;
  struct sockaddr_in  client_address;
  pthread_t           thread_ids[NUMBER_OF_CLIENTS_ALLOWED];
  int                 whichClient;
  Client              *client_linked_list_node;


  while (number_of_current_clients < NUMBER_OF_CLIENTS_ALLOWED)
  {
    // accept a packet from the client
    address_length = sizeof (client_address);
    if ((client_socket = accept (server_socket,(struct sockaddr *)&client_address, &address_length)) < 0)
    {
      printf ("[SERVER] : accept() FAILED\n");
      fflush(stdout);
      exit(4);
    }

    getpeername(client_socket,(struct sockaddr *)&client_address, &address_length);

    // Store the client info in the linked list
    client_linked_list_node = insert(client_socket, inet_ntoa(client_address.sin_addr));

    if (number_of_current_clients == -1 )
    {
      number_of_current_clients = 1;
    }
    else
    {
      number_of_current_clients++;
    }

    if (pthread_create(&(thread_ids[(number_of_current_clients - 1)]), NULL, socket_thread, (void *)client_linked_list_node))
    {
      printf ("[SERVER] : pthread_create() FAILED\n");
      fflush(stdout);
      exit(5);
    }
  }

  // Now we wait for the threads to complete
  for(int i = 0; i < NUMBER_OF_CLIENTS_ALLOWED; i++)
  {
    pthread_join(thread_ids[i], (void *)(&whichClient));
  }
}



//NAME        : socket_thread
//DESCRIPTION : recieves messages from client and sends them to a broadcasting function
//PARAMETERS  : void *client_linked_list_node - client node from Client linked list
//RETURNS     : void*
void *socket_thread(void *client_linked_list_node)
{
  char received_data[BUFFSIZ];
  Client *p_client_node = (Client *) client_linked_list_node;
  int client_socket = p_client_node->socket;          // remap the clientSocket value (which is a void*) back into an INT
  int this_client_index = number_of_current_clients;	// assumes that another connection from another client
				                                              // hasn't been created in the meantime

  // Clear out the input Buffer
  memset(received_data, 0, BUFFSIZ);

  //get the client user name / user ID
  if (recv(p_client_node->socket, p_client_node->name, NAME_LENGTH, 0) <= 0)
  {
    send(p_client_node->socket, "Error: user ID is invalid\n", BUFFSIZ, 0);
    strcpy(received_data, "");
  }
  else
  {
      read (client_socket, received_data, BUFFSIZ);
  }

  while(strcmp(received_data, ">>bye<<") != 0 && strcmp(received_data, "") != 0)
  {
    broadcast_message(p_client_node, received_data);

    // clear out and get the next command and process
    memset(received_data, 0, BUFFSIZ);
    read (client_socket, received_data, BUFFSIZ);
  }
  close(client_socket);

  // decrement the number of clients
  delete(p_client_node);
  number_of_current_clients--;

  // the return status will be the client # of this thread
  pthread_exit((void *)(this_client_index));

  return 0;
}



//NAME        : broadcast_message
//DESCRIPTION : sends a message to all clients except for the client passed as a param
//PARAMETERS  : Client* this_client - the client not to send a message to
//              char buffer - message to send
//RETURNS     : void
void broadcast_message(Client* this_client, char buffer[])
{
    Client* root_copy = root->next;
    char message[MESSAGE_SIZE];
    time_t raw_time;
    struct tm * time_info;

    //get the local time
    time ( &raw_time );
    time_info = localtime ( &raw_time );
    while (root_copy != NULL)
    {
        //send the message to all clients except sender
        if (this_client->socket != root_copy->socket)
        {
          sprintf(message, "%-15s [%-5s] >> %-40s (%d:%d:%d)", this_client->ip, this_client->name, buffer, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
          write(root_copy->socket, message, MESSAGE_SIZE);
        }
        else //send to sender (this message has the '<<' instead of the '>>')
        {
          sprintf(message, "%-15s [%-5s] << %-40s (%d:%d:%d)", this_client->ip, this_client->name, buffer, time_info->tm_hour, time_info->tm_min, time_info->tm_sec);
          write(root_copy->socket, message, MESSAGE_SIZE);
        }

        root_copy = root_copy->next;
    }
}
