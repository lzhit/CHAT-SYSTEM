//FILE          : chat-server.h
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
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
#include "clientLList.h"

//CONSTANTS
#define PORT     5006

// FUNCTION PROTOTYPES
void initServer(int* server_socket);
void acceptClient(int server_socket);
void *socketThread(void *);
void broadcast_msg(Client* this_client, char msg[]);
void alarmHandler(int signal_number);
