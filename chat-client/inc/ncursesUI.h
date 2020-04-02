//FILE          : ncursesUI.c
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
#include <stdarg.h>
#include <fcntl.h>
#include <ncurses.h>

#define BUFLEN  80

void start_ncurses();
void clear_ncurses(WINDOW** msg_win, WINDOW** chat_win);
void setupUI(WINDOW** msg_win, WINDOW** chat_win);
void setupMsgW(WINDOW** msg_win);
void setupChatW(WINDOW** chat_win);
WINDOW *create_newwin(int, int, int, int);
void destroy_win(WINDOW *);
void input_win(WINDOW *, char *);
void display_win(WINDOW *, char *);
void destroy_win(WINDOW *win);
void blankWin(WINDOW *win);

//WINDOW *chat_win, *msg_win;
