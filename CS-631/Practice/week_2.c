#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int, char**);

int main(int argc, char** argv)
{
    int opened_file;
    FILE* second_file;

    setprogname(argv[0]);

    printf("STDIN_FILENO: %d\n", STDIN_FILENO);
    printf("STDOUT_FILENO: %d\n", STDOUT_FILENO);
    printf("STDERR_FILENO: %d\n", STDERR_FILENO);

    printf("stdin FD: %d\n", fileno(fdopen(STDIN_FILENO, "r")));
    printf("stdout FD: %d\n", fileno(fdopen(STDOUT_FILENO, "r")));
    printf("stderr FD: %d\n", fileno(fdopen(STDERR_FILENO, "r")));

    opened_file = open(argv[0], O_RDONLY);
    printf("open() FD: %d\n", opened_file);
    close(opened_file);

    second_file = fopen(argv[0], "r");
    printf("fopen() FD: %d\n", fileno(second_file));
    fclose(second_file);

    return EXIT_SUCCESS;
}