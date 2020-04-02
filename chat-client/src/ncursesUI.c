//FILE          : ncursesUI.c
//PROJECT       : SENG2030 - Assignment 4
//PROGRAMMER    : Lidiia Zhitova
//FIRST VERSION : 2020-03-28
//DESCRIPTION   :


#include "../inc/ncursesUI.h"




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
void clear_ncurses(WINDOW** msg_win, WINDOW** chat_win)
{
  destroy_win(*chat_win);
  destroy_win(*msg_win);
  endwin();
}



//NAME        :
//DESCRIPTION :
//PARAMETERS  :
//RETURNS     :
void setupUI(WINDOW** msg_win, WINDOW** chat_win)
{
  int msg_startx, msg_starty, msg_width, msg_height, i;
  int chat_startx, chat_starty, chat_width, chat_height;

  start_ncurses();

  chat_height = 5;
  chat_width  = COLS - 2;
  chat_startx = 1;
  chat_starty = LINES - chat_height;

  msg_height = LINES - chat_height - 1;
  msg_width  = COLS;
  msg_startx = 0;
  msg_starty = 0;


  /* create the output window */
  *chat_win = create_newwin(chat_height, chat_width, chat_starty, chat_startx);
  scrollok(*chat_win, TRUE);

  /* create the input window */
  *msg_win = create_newwin(msg_height, msg_width, msg_starty, msg_startx);
  scrollok(*msg_win, TRUE);
}



//NAME        :
//DESCRIPTION :
//PARAMETERS  :
//RETURNS     :
void setupChatW(WINDOW** chat_win)
{
  int chat_startx, chat_starty, chat_width, chat_height;

  chat_height = 5;
  chat_width  = COLS - 2;
  chat_startx = 1;
  chat_starty = LINES - chat_height;

  /* create the output window */
  *chat_win = create_newwin(chat_height, chat_width, chat_starty, chat_startx);
  scrollok(*chat_win, TRUE);
}



//NAME        :
//DESCRIPTION :
//PARAMETERS  :
//RETURNS     :
void setupMsgW(WINDOW** msg_win)
{
  int msg_startx, msg_starty, msg_width, msg_height, i;

  msg_height = LINES - 5 - 1;
  msg_width  = COLS;
  msg_startx = 0;
  msg_starty = 0;


  /* create the input window */
  *msg_win = create_newwin(msg_height, msg_width, msg_starty, msg_startx);
  scrollok(*msg_win, TRUE);
}



//NAME        :
//DESCRIPTION :
//PARAMETERS  :
//RETURNS     :
WINDOW *create_newwin(int height, int width, int starty, int startx)
{
  WINDOW *local_win;

  local_win = newwin(height, width, starty, startx);
  box(local_win, 0, 0);               /* draw a box */
  wmove(local_win, 1, 1);             /* position cursor at top */
  wrefresh(local_win);
  return local_win;
}



//NAME        :
//DESCRIPTION : /* This function is for taking input chars from the user */
//PARAMETERS  :
//RETURNS     :
void input_win(WINDOW * win, char *word)
{
  int i, ch;
  int maxrow, maxcol, row = 1, col = 0;



  blankWin(win);                          /* make it a clean window */
  getmaxyx(win, maxrow, maxcol);          /* get window size */
  bzero(word, BUFLEN);
  wmove(win, 1, 1);                       /* position cusor at top */
  for (i = 0; (ch = wgetch(win)) != '\n'; i++)
  {
    word[i] = ch;                       /* '\n' not copied */
    if (col++ < maxcol-2)               /* if within window */
    {
      wprintw(win, "%c", word[i]);      /* display the char recv'd */
    }
    else                                /* last char pos reached */
    {
      col = 1;
      if (row == maxrow-2)              /* last line in the window */
      {
        scroll(win);                    /* go up one line */
        row = maxrow-2;                 /* stay at the last line */
        wmove(win, row, col);           /* move cursor to the beginning */
        wclrtoeol(win);                 /* clear from cursor to eol */
        box(win, 0, 0);                 /* draw the box again */
      }
      else
      {
        row++;
        wmove(win, row, col);           /* move cursor to the beginning */
        wrefresh(win);
        wprintw(win, "%c", word[i]);    /* display the char recv'd */
      }
    }
  }
}



int displayX = 1;
int displayY = 0;

//NAME        :
//DESCRIPTION :
//PARAMETERS  :
//RETURNS     :
void display_win(WINDOW *win, char *word)
{


  // if (displayY > 10)
  // {
  //   printf("here\n");
  //   printf("displayY = %d\n", displayY);
  //   blankWin(win);                          /* make it a clean window */
  //   displayY = 0;
  // }
  displayY++;
  wmove(win, displayY, 1);
  wprintw(win, word);
  wrefresh(win);
} /* display_win */



//NAME        :
//DESCRIPTION :
//PARAMETERS  :
//RETURNS     :
void destroy_win(WINDOW *win)
{
  delwin(win);
}  /* destory_win */



//NAME        :
//DESCRIPTION :
//PARAMETERS  :
//RETURNS     :
void blankWin(WINDOW *win)
{
  int i;
  int maxrow, maxcol;

  getmaxyx(win, maxrow, maxcol);
  for (i = 1; i < maxcol-2; i++)
  {
    wmove(win, i, 1);
    refresh();
    wclrtoeol(win);
    wrefresh(win);
  }
  box(win, 0, 0);             /* draw the box again */
  wrefresh(win);
}  /* blankWin */
