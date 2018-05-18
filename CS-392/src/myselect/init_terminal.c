#include "myselect.h"

/*
 * init_terminal()
 *
 * Prepare the terminal for the program execution
 *
 * Precondition: None
 * Postcondition: Terminal is prepared for special use
 */
void               init_terminal()
{
    struct termio modify;
    char*          name;
    int           fd;

    ioctl(0, TCGETA, &(gl_env.line_backup));
    modify = gl_env.line_backup;

    modify.c_lflag &= ~(ICANON | ECHO | ISIG);
    modify.c_cc[VMIN] = READMIN;
    modify.c_cc[VTIME] = READTIME;

    ioctl(0, TCSETA, &modify);

    name = ttyname(0);
    fd = open(name, O_WRONLY);

    gl_env.stdio_backup = dup(1);
    dup2(fd, 1);

    gl_env.pos = 0;
}