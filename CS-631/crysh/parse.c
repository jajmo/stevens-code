#include "crysh.h"

#define IS_SEP(S) ((S) == ' ' || (S) == '\t' || (S) == ';')
#define IS_SP(S)  ((S) == ' ' || (S) == '\t')

char ***tokenize(const char *str)
{
    char ***res;
    int count;
    int curr;
    int start;
    int end;
    int i;

    count = get_command_count(str);

    if ((res = (char ***) malloc((count + 1) * sizeof(char **))) == NULL)
        errx(errno, "malloc failed: %s", strerror(errno));
    res[count] = NULL;

    for (start = curr = i = 0; str[i] && curr < count; i++)
    {
        if ((str[i] == ';' && str[i - 1] != '\\') || str[i + 1] == '\0')
        {
            end = i + 1;
            res[curr++] = extract_command(str + start, end - start);
            if (res[curr - 1] == NULL)
            {
                free_2d_vec(res, 0);
                return NULL;
            }
            start = i;
        }
    }

    return res;
}

char **extract_command(const char *str, int end)
{
    char **res;
    int count;
    int i;
    int orig;
    int total;

    count = total = get_token_count(str, end);

    if ((res = (char **) malloc((count + 1) * sizeof(char *))) == NULL)
        errx(errno, "malloc failed: %s", strerror(errno));
    res[count] = NULL;

    for (i = count = 0; i < end && count < total; )
    {
        /* Iterate past separators */
        while (str[i] && i < end && IS_SEP(str[i]))
            i++;

        /* Check for redirection */
        if ((str[i] == '>' || (str[i] == '2' && str[i + 1] && str[i + 1] == '>')) && str[i - 1] != '\\')
        {
            orig = i;
            if (str[i] == '2')
                i++;
            while (str[i] && str[i] == '>')
                i++;
            if (i - orig > 3)
            {
                free_vec(res, 0, total);
                return NULL;
            }
            res[count++] = get_word(str + orig, i - orig);
        }

        /* Iterate past any separators */
        while (str[i] && i < end && IS_SEP(str[i]))
            i++;

        if (!str[i] || i == end)
            break;

        /* Extract the current word */
        res[count++] = get_word(str + i, -1);
        if (res[count - 1] == NULL)
        {
            free_vec(res, 0, total);
            return NULL;
        }

        /* Iterate over any escaped stuff, since get_word() handles that */
        while (str[i] && i < end)
        {
            if (str[i] == '"')
            {
                i++;
                while (str[i] && str[i] != '"' && i < end)
                    i++;
            }

            if (IS_SP(str[i]) && str[i - 1] != '\\')
                break;
            i++;
        }
    }

    return res;
}

char *get_word(const char *str, int count)
{
    char *res;
    int i;
    int quote;
    int sz;
    int pos;

    if (count > -1)
    {
        if ((res = (char *) malloc((count + 1) * sizeof(char))) == NULL)
            errx(errno, "malloc failed: %s\n", strerror(errno));

        for (i = 0; i < count; i++)
            res[i] = str[i];

        res[count] = '\0';
        return res;
    }

    for (i = 0, quote = FALSE; str[i]; i++)
    {
        if (str[i] == '"')
            quote = (quote == TRUE) ? FALSE : TRUE;
        if (IS_SP(str[i]) && quote == FALSE && i > 0 && str[i - 1] != '\\')
            break;
    }

    sz = i;

    if ((res = (char *) malloc((sz + 1) * sizeof(char))) == NULL)
        errx(errno, "malloc failed: %s", strerror(errno));

    for (i = 0, pos = 0; i < sz; i++)
    {
        if (str[i] == '"' && str[i - 1] != '\\')
        {
            i++;
            while (str[i] && str[i] != '"')
                res[pos++] = str[i++];
            if (str[i] != '"')
            {
                free(res);
                return NULL;
            }
            i++;
        }
        if (str[i] == ';' && str[i - 1] != '\\')
            break;
        if (str[i] == '\\' && str[i - 1] != '\\')
            continue;
        res[pos++] = str[i];
        if (IS_SP(str[i]) && i > 0 && str[i - 1] != '\\')
            break;
    }

    res[pos] = '\0';

    return res;
}

int get_command_count(const char *str)
{
    int i;
    int count;

    for (i = 0, count = 0; str[i]; i++)
        if (str[i] == ';' && str[i - 1] != '\\')
            count++;

    for (i = i - 1; i > 0; i--)
        if (str[i] != ' ' && str[i] != '\t')
            break;

    if (str[i] != ';')
        count++;

    return count;
}

int get_token_count(const char *str, int end)
{
    int i;
    int count;
    int in_str;

    for (i = 0, count = 0, in_str = FALSE; str[i] && i < end; i++)
    {
        if (str[i] != ' ' && str[i] != '\t' && in_str == FALSE)
        {
            in_str = TRUE;
            count++;
        }
        else if (IS_SP(str[i]))
            in_str = FALSE;

        if (str[i] == '"')
        {
            i++;
            while (str[i] && str[i] != '"')
                i++;
        }

        if (str[i] == '\\')
        {
            count++;
            i += 2;
        }

        if (str[i] == '>' && strncmp(str + i, "> ", 2) != 0 && strncmp(str + i, ">> ", 3) != 0)
            count++;
        if (str[i] == '2' && str[i + 1] == '>' && strncmp(str + i, "2> ", 3) != 0 && strncmp(str + i, "2>> ", 4) != 0)
            count++;
    }

    return count;
}