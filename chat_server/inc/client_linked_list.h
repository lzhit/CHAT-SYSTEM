//FILE          : client_linked_list.h
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

//CONSTANTS
#define IP_LENGTH    16
#define NAME_LENGTH  5

//NODE IMPLEMENTATION
#ifndef CLIENTLIST
#define CLIENTLIST

typedef struct Node
{
    struct Node* next;
    int socket;
    char ip[IP_LENGTH];
    char name[NAME_LENGTH];
} Client;

#endif

//GLOBAL VARIABLES
Client *root;    //first node of the list
int number_of_current_clients;


//FUNCTION PROTOTYPES
Client* insert(int client_socket, char* ip);
Client* delete(Client* client);
