#include "helpers.h"

/* malloc() with error checking */
void *xmalloc(size_t len)
{
    void *res;

    if ((res = malloc(len)) == NULL)
        errx(EXIT_FAILURE, "malloc() failed: %s", strerror(errno));

    return res;
}

/* Get the length of a number */
int num_len(unsigned long num)
{
    int i;
    i = 1;

    while (num > 9)
    {
        num /= 10;
        i++;
    }

    return i;
}

/* Determine if a file needs to be displayed and counted */
BOOL need_show_file(FTSENT *f)
{
    if (f->fts_level == FTS_ROOTLEVEL)
        return TRUE;

    if (flag_A == TRUE && strcmp(f->fts_name, ".") != 0 && strcmp(f->fts_name, "..") != 0)
        return TRUE;
    else if (flag_a == FALSE && f->fts_name[0] == '.')
        return FALSE;
    else
        return TRUE;
}

/* Sanitize a string */
char *sanitize(char *str)
{
    int len;
    int i;
    char *res;

    if (str == NULL)
        return NULL;

    len = strlen(str);
    res = (char*) xmalloc((len + 1) * sizeof(char));

    for (i = 0; i < len; i++)
        res[i] = (str[i] > 32 && str[i] < 127) ? str[i] : '?';
    res[i] = '\0';
    
    return res;
}

/* Reset sizes for columnization */
void reset_sizes()
{
    sizes.blocks = 0;
    sizes.inode = 0;
    sizes.links = 0;
    sizes.user = 0;
    sizes.group = 0;
    sizes.name = 0;
    sizes.size = 0;
}