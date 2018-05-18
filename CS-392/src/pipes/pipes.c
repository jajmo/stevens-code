#include "my.h"

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 512
#endif

/*
 * pipes
 *
 * Forks processes and sends data to the child processes through pipes
 *
 * Precondition: argc > 1
 * Postcondition: The strings the children recieve are printed to stdout
 *
 * NOTE: Both paramaters are from the command line
 * @param argc - The number of arguments passed (>= 1)
 * @param argv - A vector of arguments
 * @return int - The return status of the program
 */
int       main(int argc, char** argv)
{
    char  buffer[BUFFER_SIZE];
    int   pipe1[2];
    int   pipe2[2];
    int   pid;
    int   bytes_read;
    char* s;

    if(argc < 2)
    {
        my_str("Usage: ./pipes arg1 [arg2] [arg3]...\n");
        exit(0);
    }

    pipe(pipe1);

    if((pid = fork()) < 0)
    {
        my_str("Grandparent fork() critical error!\n");
        exit(0);
    }


    if(pid > 0)
    {
        close(pipe1[0]);
        
        s = my_vect2str(&argv[1]);

        my_str("I am grandpa sending \"");
        my_str(s);
        my_str("\"\n");

        write(pipe1[1], s, BUFFER_SIZE - 1);
        wait();
    }
    else
    {
        close(pipe1[1]);
        bytes_read = read(pipe1[0], buffer, BUFFER_SIZE - 1);
        buffer[bytes_read] = '\0';

        my_str("I am dad receiving \"");
        my_str(buffer);
        my_str("\"\n");

        pipe(pipe2);

        if((pid = fork()) < 0)
        {
            my_str("Dad fork() critical error!\n");
            exit(0);
        }

        if(pid > 0)
        {
            close(pipe2[0]);
            write(pipe2[1], buffer, BUFFER_SIZE - 1);
            wait();
        }
        else
        {
            close(pipe2[1]);
            bytes_read = read(pipe2[0], buffer, BUFFER_SIZE - 1);
            buffer[bytes_read] = '\0';

            my_str("I am child receiving \"");
            my_str(buffer);
            my_str("\"\n");
            exit(0);
        }
    }

    return 0;
}
