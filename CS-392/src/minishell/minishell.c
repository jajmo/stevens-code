#include "my.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif

/*
 * minishell
 *
 * A smaller version of Bash, with built in functions cd and exit working
 * NOTE: cd - and cd ~ do not work
 *
 * Precondition: None
 * Postcondition: The shell is open and running
 *
 * Last Edit: October 15th, 2014 12:48 AM
 */
int        main(int argc, char** argv)
{
    char   buffer[BUFFER_SIZE];
    char** args;
    char*  dir;
    int    status;
    int    bytes;
    int    pid;

    while(1)
    {
        dir = getcwd(dir, BUFFER_SIZE);

        my_str(dir);
        my_str(": ");

        if((bytes = read(0, buffer, BUFFER_SIZE - 1)) < 0)
        {
            my_str("Invalid read\n");
            exit(0);
        }

        buffer[bytes - 1] = '\0';

        args = my_str2vect(buffer);

        if(my_strcmp(args[0], "cd") == 0)
        {
            if((status = chdir(args[1])) < 0)
            {
                if(args[1] == NULL)
                {
                    my_str("Invalid arguments\n");
                }
                else
                {
                    my_str(args[1]);
                    my_str(": Directory not found\n");
                }
            }
        }
        else if(my_strcmp(args[0], "exit") == 0)
        {
            my_str("No fork bombs? Good! Have a great day :)\n");
            free(dir);
            my_freevect(args);
            exit(0);
        }
        else
        {
            if((pid = fork()) < 0)
            {
                my_str("fork() critical error!\n");
                exit(0);
            }

            if(pid > 0)
            {
                wait();
            }
            else
            {
                if((status = execvp(args[0], args)) < 0)
                {
                    my_str(args[0]);
                    my_str(": Command not found!\n");
                    exit(0);
                }
            }
        }

        my_freevect(args);
    }

    return 0;
}
