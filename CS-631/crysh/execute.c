#include "crysh.h"

int execute(const char *command_str)
{
    int i;
    int j;
    int size;
    int first;
    int mode;
    int stdout_redirect;
    int stderr_redirect;
    int status_param;
    int status;
    int start;
    pid_t pid;
    char ***vec;

    status = start = 0;

    if ((vec = tokenize(command_str)) == NULL)
        return PARSE_ERROR;

    /*for (i = 0; vec[i]; i++)
        for (j = 0; vec[i][j]; j++)
            printf("%d: --%s--\n", i, vec[i][j]);*/

    stdout_redirect = STDOUT_FILENO;
    stderr_redirect = STDERR_FILENO;

    for (j = 0; vec[j]; j++)
    {
        start = j;

        if (vec[j][0] == NULL)
        {
            status = PARSE_ERROR;
            break;
        }

        for (i = 0, first = -1; vec[j][i]; i++)
        {
            if (vec[j][i][0] == '>')
            {
                if (vec[j][i + 1] == NULL || strlen(vec[j][i]) > 2)
                {
                    free_2d_vec(vec, j);
                    return PARSE_ERROR;
                }

                if (strlen(vec[j][i]) == 1)
                    mode = O_WRONLY | O_TRUNC | O_CREAT;
                else
                    mode = O_WRONLY | O_APPEND | O_CREAT;

                if ((stdout_redirect = open(vec[j][i + 1], mode, FILE_MODE)) < 0)
                    errx(errno, "open failed: %s", strerror(errno));

                /* Need to set null terminator for `execvp` */
                if (first == -1)
                    first = i;
            }
            if (strncmp(vec[j][i], "2>", 2) == 0)
            {
                if (vec[j][i + 1] == NULL || strlen(vec[j][i]) > 3)
                {
                    free_2d_vec(vec, j);
                    return PARSE_ERROR;
                }

                if (strlen(vec[j][i]) == 2)
                    mode = O_WRONLY | O_TRUNC | O_CREAT;
                else
                    mode = O_WRONLY | O_APPEND | O_CREAT;

                if ((stderr_redirect = open(vec[j][i + 1], mode, FILE_MODE)) < 0)
                    errx(errno, "open failed: %s", strerror(errno));

                if (first == -1)
                    first = i;
            }
        }

        if (first != -1)
        {
            free(vec[j][first]);
            vec[j][first] = NULL;
        }

        size = i;

        if ((pid = fork()) < 0)
            errx(errno, "fork failed: %s", strerror(errno));
        else if (pid == 0)
        {
            dup2(stdout_redirect, STDOUT_FILENO);
            dup2(stderr_redirect, STDERR_FILENO);
            if (execvp(vec[j][0], vec[j]) < 0)
            {
                switch (errno)
                {
                case ENOENT:
                    errx(errno, "%s: command not found", vec[j][0]);
                    break;
                case EACCES:
                    errx(errno, "%s: permission denied", vec[j][0]);
                    break;
                default:
                    errx(errno, "%s: %s", vec[j][0], strerror(errno));
                    break;
                }
            }
        }
        else
            wait(&status_param);

        status = WIFEXITED(status_param) ? WEXITSTATUS(status_param) : 0;

        free_vec(vec[j], 0, size);
        start = j + 1;

        if (stdout_redirect != STDOUT_FILENO)
            close(stdout_redirect);
        if (stderr_redirect != STDERR_FILENO)
            close(stderr_redirect);

        if (status != 0)
            break;
    }

    free_2d_vec(vec, start);

    return status;
}

void free_2d_vec(char ***v, int start)
{
    int i;
    int j;

    for (i = start; v[i]; i++)
    {
        for (j = 0; v[i][j]; j++)
        {
            if (v[i][j] != NULL)
            {
                bzero(v[i][j], strlen(v[i][j]));
                free(v[i][j]);
            }
        }

        free(v[i]);
    }

    free(v);
}

void free_vec(char **v, int start, int end)
{
    int i;

    for (i = start; i < end; i++)
    {
        if (v[i] != NULL)
        {
            bzero(v[i], strlen(v[i]));
            free(v[i]);
        }
    }

    free(v);
}