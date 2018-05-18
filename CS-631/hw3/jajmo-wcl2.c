#include <sys/wait.h>

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/**
 * wcl2.c
 * Author: Jason Ajmo (jajmo@stevens.edu)
 *
 * Counts number of stdout and stderr lines by:
 * 1. Creates two pipes: one for stdout, and one for stderr
 * 2. Forks a child
 * 3. Child sets stdout to be the first pipe, and stderr to be the second pipe using dup2(2)
 * 4. Child execvp(3)'s the user's arguments
 * 5. Parent reads first from the stdout pipe and then from the stderr pipe, looking for '\n' along the way,
 *    and incrementing the appropriate counter
 */
int main(int argc, char **argv)
{
    int pipes_stdout[2];
    int pipes_stderr[2];
    int n;
    int i;
    int stdout_n;
    int stderr_n;
    char buff[BUFSIZ];
    pid_t pid;

    if (argc == 1)
    {
        (void) fprintf(stderr, "Usage: %s [command]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    argv++;

    if (pipe(pipes_stdout) < 0 || pipe(pipes_stderr) < 0)
    {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    if ((pid = fork()) < 0)
    {
        perror("fork");
        exit(EXIT_FAILURE);
    }
    else if (pid == 0)
    {
        (void) close(pipes_stdout[0]);
        (void) close(pipes_stderr[0]);

        if (dup2(pipes_stdout[1], STDOUT_FILENO) != STDOUT_FILENO ||
            dup2(pipes_stderr[1], STDERR_FILENO) != STDERR_FILENO)
        {
            perror("dup2");
            exit(EXIT_FAILURE);
        }

        (void) execvp(argv[0], argv);
        perror("execvp");
        exit(EXIT_FAILURE);
    }
    else
    {
        (void) close(pipes_stdout[1]);
        (void) close(pipes_stderr[1]);
        stdout_n = 0;
        stderr_n = 0;

        while ((n = read(pipes_stdout[0], buff, BUFSIZ)) > 0)
        {
            for (i = 0; i < n; i++)
                if (buff[i] == '\n')
                    stdout_n++;
        }

        if (n < 0)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        while ((n = read(pipes_stderr[0], buff, BUFSIZ)) > 0)
        {
            for (i = 0; i < n; i++)
                if (buff[i] == '\n')
                    stderr_n++;
        }

        if (n < 0)
        {
            perror("read");
            exit(EXIT_FAILURE);
        }

        (void) printf("stdout: %d\n", stdout_n);
        (void) printf("stderr: %d\n", stderr_n);

        if (waitpid(pid, NULL, 0) < 0)
        {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        exit(EXIT_SUCCESS);
    }

    return 0;
}