//FILE          : ncursesUI.c
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
#include <stdarg.h>
#include <fcntl.h>
#include <ncurses.h>


//CONSTANTS
#define BUFLEN  80


//FUNCTION PROTOTYPES
void start_ncurses();
void clear_ncurses(WINDOW** message_window, WINDOW** chat_window);
void setup_message_window(WINDOW** message_window);
void setup_chat_window(WINDOW** chat_window);
WINDOW *create_new_window(int, int, int, int);
void destroy_window(WINDOW *);
void input_window(WINDOW *, char *);
void display_window(WINDOW *, char *);
void destroy_window(WINDOW *window);
void blank_window(WINDOW *window);
