//FILE          : ncursesUI.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   : ncurses functions


#include "../inc/ncurses_UI.h"




//NAME        : start_ncurses
//DESCRIPTION : Start curses mode
//PARAMETERS  : void
//RETURNS     : void
void start_ncurses()
{
  initscr();
  cbreak();
  noecho();
  refresh();
}



//NAME        : clear_ncurses
//DESCRIPTION : removes the created windows
//PARAMETERS  : WINDOW** msg_win, WINDOW** chat_win
//RETURNS     : void
void clear_ncurses(WINDOW** message_window, WINDOW** chat_window)
{
  destroy_window(*chat_window);
  destroy_window(*message_window);
  endwin();
}



//NAME        : setup_chat_window
//DESCRIPTION : displays the chat window
//PARAMETERS  : WINDOW** chat_win - pointer to the chat window
//RETURNS     : void
void setup_chat_window(WINDOW** chat_window)
{
  int chat_start_x, chat_start_y, chat_width, chat_height;

  chat_height = 5;
  chat_width  = COLS - 2;
  chat_start_x = 1;
  chat_start_y = LINES - chat_height;

  /* create the output window */
  *chat_window = create_new_window(chat_height, chat_width, chat_start_y, chat_start_x);
  scrollok(*chat_window, TRUE);
}



//NAME        : setupMsgW
//DESCRIPTION : displays the message window
//PARAMETERS  : WINDOW** msg_win - pointer to the message window
//RETURNS     : void
void setup_message_window(WINDOW** message_window)
{
  int msg_start_x, msg_start_y, msg_width, msg_height, i;

  msg_height = LINES - 5 - 1;
  msg_width  = COLS;
  msg_start_x = 0;
  msg_start_y = 0;


  /* create the input window */
  *message_window = create_new_window(msg_height, msg_width, msg_start_y, msg_start_x);
  scrollok(*message_window, TRUE);
}



//NAME        : create_new_window
//DESCRIPTION : draws a window in the console
//PARAMETERS  : int height - hight of the window
//              int width - the width of the window
//              int starty - the top most point of the window
//              int startx - the left most point of the window
//RETURNS     : void
WINDOW *create_new_window(int height, int width, int start_y, int start_x)
{
  WINDOW *local_window;

  local_window = newwin(height, width, start_y, start_x);
  box(local_window, 0, 0);               /* draw a box */
  wmove(local_window, 1, 1);             /* position cursor at top */
  wrefresh(local_window);
  return local_window;
}



//NAME        : input_win
//DESCRIPTION : This function is for taking input chars from the user
//PARAMETERS  : WINDOW* win - window for collecting user input
//              char* word - user input will be stored in this variable
//RETURNS     : void
void input_window(WINDOW * window, char *word)
{
  int character;
  int maxrow, maxcol, row = 1, column = 0;



  blank_window(window);                          /* make it a clean window */
  getmaxyx(window, maxrow, maxcol);          /* get window size */
  bzero(word, BUFLEN);
  wmove(window, 1, 1);                       /* position cusor at top */
  for (int i = 0; (character = wgetch(window)) != '\n'; i++)
  {
    if (i > BUFLEN-2)
    {
      continue;                         //no more than 80 characters are accepted
    }

    word[i] = character;                /* '\n' not copied */
    if (column++ < maxcol-2)            /* if within window */
    {
      wprintw(window, "%c", word[i]);   /* display the char recv'd */
    }
    else                                /* last char pos reached */
    {
      column = 1;
      if (row == maxrow-2)              /* last line in the window */
      {
        scroll(window);                 /* go up one line */
        row = maxrow-2;                 /* stay at the last line */
        wmove(window, row, column);     /* move cursor to the beginning */
        wclrtoeol(window);              /* clear from cursor to eol */
        box(window, 0, 0);              /* draw the box again */
      }
      else
      {
        row++;
        wmove(window, row, column);        /* move cursor to the beginning */
        wrefresh(window);
        wprintw(window, "%c", word[i]);    /* display the char recv'd */
      }
    }
  }
}



int displayY = 0;

//NAME        : display_window
//DESCRIPTION :
//PARAMETERS  : WINDOW* win - window for displaying text
//              char* word - contains the text to display
//RETURNS     : void
void display_window(WINDOW *window, char *word)
{
  //clear the screen after every 10 messages
  if (displayY >= 10)
  {
    blank_window(window);   /* make it a clean window */
    displayY = 0;
  }
  displayY++; // display every message on a new line
  wmove(window, displayY, 1);
  wprintw(window, word);
  wrefresh(window);
}



//NAME        : destroy_win
//DESCRIPTION : removes a window from the console
//PARAMETERS  : WINDOW* win - the window to remove
//RETURNS     : void
void destroy_window(WINDOW *window)
{
  delwin(window);
}



//NAME        : blankWin
//DESCRIPTION : removes the contents of a window
//PARAMETERS  : WINDOW* win - the window to clear
//RETURNS     : void
void blank_window(WINDOW *window)
{
  int maxrow, maxcol;

  getmaxyx(window, maxrow, maxcol);
  for (int i = 1; i < maxcol - 2; i++)
  {
    wmove(window, i, 1);
    refresh();
    wclrtoeol(window);
    wrefresh(window);
  }
  box(window, 0, 0);             /* draw the box again */
  wrefresh(window);
}
