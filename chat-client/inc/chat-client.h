//FILE          : chat-client.h
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   :


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
#include <stdarg.h>
#include <fcntl.h>
#include <ncurses.h>

#define PORT    5006
#define BUFLEN  80

//char buffer[BUFSIZ];

void *inputThread(void* server_socket);
void *outputThread(void* server_socket);
int checkPattern(char string[]);
