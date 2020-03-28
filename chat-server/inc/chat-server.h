#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <pthread.h>

#define PORT 5000

typedef struct msgInfo
{
  char ip[16];
  char name[5];
  char msg[80];


} MSGINFO;



#ifndef LIST
#define LIST

typedef struct Node {
    struct Node* prev;
    struct Node* next;
    int socket;
    char ip[16];
    char name[5];
} Client;

Client *newNode(int client_socket, char* ip) {
    Client *client = (Client *)malloc( sizeof(Client) );
    client->socket = client_socket;
    client->prev = NULL;
    client->next = NULL;
    strncpy(client->ip, ip, 16);
    strncpy(client->name, "NULL", 5);
    return client;
}

#endif // LIST

// thread function prototype
void *socketThread(void *);
void send_to_all_clients(Client *this_client, char msg[]);
