//FILE          : chat-client.h
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
#include <stdarg.h>
#include <fcntl.h>
#include <ncurses.h>

#define PORT     5008
#define BUFFLEN  40
#define MSGSIZ   78

void initAddr(struct sockaddr_in* server_addr, struct hostent** host);
void getSocket(int *my_server_socket);
void connectServer(int *my_server_socket, struct sockaddr_in *server_addr);
void startInputThread(pthread_t* thread, int* my_server_socket);
void startOutputThread(pthread_t* thread, int* my_server_socket);
void *inputThread(void* server_socket);
void *outputThread(void* server_socket);
int checkPattern(char string[]);
