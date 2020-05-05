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

#define PORT           5008
#define BUFFLEN        40
#define MESSAGE_SIZE   78

void get_server_address(struct sockaddr_in* server_address, struct hostent** host);
void get_socket(int *server_socket);
void connect_to_server(int *server_socket, struct sockaddr_in *server_address);
void start_input_thread(pthread_t* thread, int* server_socket);
void start_output_thread(pthread_t* thread, int* server_socket);
void *input_thread(void* socket);
void *output_thread(void* socket);
int check_pattern(char string[]);
