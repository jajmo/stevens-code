#ifndef _MYNOTSOMINISHELL_H_
#define _MYNOTSOMINISHELL_H_

/*
 * mynotsominishell program
 *
 * An implementation of some basic functionality of a shell
 *
 * Last Modified: 10/4/14 9:51 PM
 */
#include <sys/ioctl.h>
#include <stdio.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/termios.h>
#include "my.h"
#include <unistd.h>
#include <stdlib.h>
#include <termcap.h>

#ifndef NULL
#define NULL (0)
#endif

//Clear termcal termcap
#define CLEAR "cl"

//Arrow key termcaps
#define UP "ku"
#define DOWN "kd"
#define LEFT "kl"
#define RIGHT "kr"

//Backspace termcap
#define BACKSPACE "le"

//Move right termcap
#define MOVE_RIGHT "nd"

//Control key input combinations
#define CTRL_A 1
#define CTRL_E 5
#define CTRL_W 23
#define CTRL_L 12
#define CTRL_K 11
#define CTRL_Y 25
#define CTRL_C 3

//Arrow key input combinations
#define KU "\E[A"
#define KD "\E[B"
#define KR "\E[C"
#define KL "\E[D"

//General buffer size
#define BUFFER_SIZE 512

//How many elements do we want to keep in the history? (Including current)
#define HISTORY_SIZE 4

typedef struct	s_env
{
  char		*left;
  char		*right;
  char		*up;
  char		*down;
  char		*esc;
  char    *backspace;
  char    *move_right;
  char    *clear;
  char    *dir;
  char   **history;
  struct termio	line_backup;
  struct winsize win;
  int		 stdio_backup;
  int    count; //The number of characters on the line
  int    pos; //The current position of the cursor
  int    current_history; //The history number we're on (0 thru HISTORY_COUNT - 1)
  int    current_row; //The current row the cursor is on
  int    max_chars; //The max number of characters in each row
}	t_env;

t_env	gl_env;

void  init_caps(); //Setup the termcaps
char* term_get_cap(char*); //Get a termcap
void  process_input(char**); //Parse and process a command
int   my_termprint(int); //Termprint for tputs()
void  init_terminal(); //Setup the terminal
void  restore_terminal(); //Restore terminal to original state
int   do_cap(char*); //Check if input is a cap. If it is, execute it and return 1. If not, return 0
void  process_char(char); //Process a character when a key is pressed
void  rewrite_pos_to_end(int, int); //Rewrite the terminal input from a position to the end
void  backspace(); //Backspace one character
void  history_up(); //Move up one spot in the history
void  history_down(); //Move down in the history (more recent)
void  shift_history(); //Shift the history up one spot to make room for the next command
void  move_cursor_to_pos(int); //Move the cursor to a specific position
void  clear_input(); //Clear the user's typed input

#endif