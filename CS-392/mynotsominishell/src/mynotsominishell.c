#include "mynotsominishell.h"

/*
 * main()
 *
 * The main driver of the mynotsominishell project
 *
 * Precondition: None
 * Postcondition: The program is ran
 *
 * @param int argc The number of command line arguments
 * @param char** argv The vector of command line arguments
 */
int main(int argc, char** argv)
{
    char   buffer[BUFFER_SIZE];
    char** args;
    int    bytes;
    int    i;
    int    done;

    init_terminal();
    init_caps();

    gl_env.history = (char**) xmalloc(HISTORY_SIZE * sizeof(char*));
    for(i = 0; i < HISTORY_SIZE; i++)
    {
        gl_env.history[i] = (char*) xmalloc(BUFFER_SIZE * sizeof(char));
    }

    done = 1;

    while(1)
    {
        if(done)
        {
            gl_env.history[gl_env.current_history][0] = '\0';
            gl_env.dir = getcwd(gl_env.dir, BUFFER_SIZE);
            my_str(gl_env.dir);
            my_str(": ");
            done = 0;
            gl_env.count = 0;
            gl_env.pos = 0;
        }

        if((bytes = read(0, buffer, BUFFER_SIZE - 1)) < 0)
        {
            my_str("Read failed\n");
            exit(0);
        }

        buffer[bytes] = '\0';

        if(buffer[0] == '\n')
        {
            my_char('\n');
            gl_env.history[gl_env.current_history][gl_env.count] = '\0';
            args = my_str2vect(gl_env.history[gl_env.current_history]);
            process_input(args);
            my_freevect(args);
            if(my_strcmp(gl_env.history[gl_env.current_history], "") != 0)
            {
                shift_history();
            }
            done = 1;
        }
        else if(buffer[0] == 0x7f)
        {
            if(gl_env.pos > 0)
            {
                backspace();
            }
        }
        else
        {
            if(!do_cap(buffer))
            {
                process_char(buffer[0]);
            }
        }
    }

    return 0;
}
