#include "mynotsominishell.h"

/*
 * do_cap()
 *
 * Check if the input is a termcap. If so, execute it
 *
 * Precondition: Caps are initialized
 * Postcondition: The termcap is processed, or 0 is returned
 *
 * @param char* inp The input character
 * @return 0 for not a cap, or 1 if a cap
 */
int       do_cap(char* inp)
{
    char* dir;
    int   count;

    if(my_strcmp(inp, KL) == 0)
    {
        if(gl_env.pos > 0)
        {
            tputs(gl_env.backspace, 1, my_termprint);
            gl_env.pos--;
        }
        
        return 1;
    }
    else if(my_strcmp(inp, KR) == 0)
    {
        if(gl_env.pos < gl_env.count)
        {
            tputs(gl_env.move_right, 1, my_termprint);
            gl_env.pos++;
        }

        return 1;
    }
    else if(my_strcmp(inp, KU) == 0)
    {
        if(gl_env.current_history > 0 && my_strcmp(gl_env.history[gl_env.current_history - 1], "") != 0)
        {
            history_up();
        }

        return 1;
    }
    else if(my_strcmp(inp, KD) == 0)
    {
        if(gl_env.current_history < HISTORY_SIZE - 1)
        {
            history_down();
        }

        return 1;
    }
    else if(inp[0] == CTRL_L)
    {
        tputs(gl_env.clear, 1, my_termprint);
        my_str(gl_env.dir);
        my_str(": ");
        rewrite_pos_to_end(0, gl_env.current_history);
        count = 0;
        while(count++ < gl_env.pos)
        {
            tputs(gl_env.move_right, 1, my_termprint);
        }
        return 1;
    }
    else if(inp[0] == CTRL_A)
    {
        move_cursor_to_pos(0);
        gl_env.pos = 0;
        return 1;
    }
    else if(inp[0] == CTRL_E)
    {
        move_cursor_to_pos(gl_env.count);
        gl_env.pos = gl_env.count;
        return 1;
    }

    return 0;
}