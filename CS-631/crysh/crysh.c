#include "crysh.h"

int main (int argc, char **argv)
{
    char buff[BUFSIZ];
    unsigned char *decrypted_commands;
    size_t nread;
    int first;
    int res;

    setprogname(argv[0]);
    first = TRUE;

    while ((nread = read(STDIN_FILENO, buff, BUFSIZ)) > 0)
    {
        if (first == TRUE)
        {
            if (decrypt_init(buff, nread) < 0)
                errx(DECRYPTION_FAILED, "unable to decrypt input");
            first = FALSE;
        }
        else if (decrypt_update(buff, nread) < 0)
            errx(DECRYPTION_FAILED, "unable to decrypt input");
    }

    if (nread < 0)
        errx(errno, "unable to read from stdin: %s\n", strerror(errno));

    if ((decrypted_commands = decrypt_final()) == NULL)
        errx(DECRYPTION_FAILED, "unable to decrypt input");

    res = execute((char *) decrypted_commands);

    if (res == PARSE_ERROR)
        fprintf(stderr, "%s: syntax error\n", getprogname());

    free(decrypted_commands);
    return res;
}