//FILE          : chat_server.h
//PROJECT       : SENG2030 - Assignment 4
//AUTHOR        : Lidiia Zhitova
//FIRST VERSION : 2020-03-28


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
#include <time.h>
#include "client_linked_list.h"

//CONSTANTS
#define PORT                      5008
#define BUFFSIZ                   40
#define MESSAGE_SIZE              78
#define NUMBER_OF_CLIENTS_ALLOWED 10

static int server_socket;

// FUNCTION PROTOTYPES
void initialize_server(int* server_socket);
void accept_client(int server_socket);
void *socket_thread(void *);
void broadcast_message(Client* this_client, char buffer[]);
void alarm_handler(int signal_number);
