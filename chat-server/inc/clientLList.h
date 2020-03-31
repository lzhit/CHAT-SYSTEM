//FILE          : clientLList.h
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

//CONSTANTS
#define IPLEN    16
#define NAMELEN  5

//NODE IMPLEMENTATION
#ifndef CLIENTLIST
#define CLIENTLIST

typedef struct Node
{
    struct Node* prev;
    struct Node* next;
    int socket;
    char ip[IPLEN];
    char name[NAMELEN];
} Client;

#endif

//GLOBAL VARIABLES
Client *root;    //first node of the list
int numClients;


//FUNCTION PROTOTYPES
Client* insert(int client_socket, char* ip);
Client* delete(Client* client);
