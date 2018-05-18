#include "parse.h"

/* Adapted from https://gist.github.com/sudar/3404970 */
void urlencode(char *str, char *res)
{
    const char *hex = "0123456789abcdef";
    int i;
    int res_pos;
    int sz;

    bzero(res, PATH_MAX);

    sz = strlen(str);
    for (i = res_pos = 0; str[i] != '\0'; i++)
    {
        if (strchr(VALID_URI_CHARACTERS, str[i]) != NULL)
            res[res_pos++] = str[i];
        else
        {
            sz += 2;
            if ((res = (char *) realloc(res, sz)) == NULL)
                warn_and_die(FALSE, "realloc failed: %s", strerror(errno));

            res[res_pos++] = '%';
            res[res_pos++] = hex[str[i] >> 4];
            res[res_pos++] = hex[str[i] & 15];
        }
    }

    res[res_pos] = '\0';
}

/* Adapted from https://github.com/abejfehr/URLDecode/blob/master/urldecode.c */
char *urldecode(char *str)
{
    char *res;
    char code[] = "00";
    int d;
    int i;
    long int x;

    if ((res = strdup(str)) == NULL)
        warn_and_die(FALSE, "malloc failed: %s", strerror(errno));

    d = 0;
    while (d == 0)
    {
        d = 1;
        for (i = 0; res[i]; i++)
        {
            if (res[i] == '%')
            {
                if (res[i + 1] == '\0')
                    return res;
                if (isxdigit((int) res[i + 1]) && isxdigit((int) res[i + 2]))
                {
                    d = 0;
                    code[0] = res[i + 1];
                    code[1] = res[i + 2];
                    x = strtol(code, NULL, 16);
                    memmove(&res[i + 1], &res[i + 3], strlen(&res[i + 3]) + 1);
                    res[i] = x;
                }
            }
        }
    }

    res[i] = '\0';
    return res;
}

int parse_method(char *str)
{
    int elems;
    int ret;

    elems = elem_count(str);

    if (elems == 1 || (elems == 2 && strncmp(str, "GET ", 4) != 0) || elems > 3)
        ret = BAD_REQUEST_CODE;
    else if (elems == 3 && strncmp(str, "GET ", 4) != 0 && strncmp(str, "HEAD ", 5) != 0 && strncmp(str, "POST ", 5) != 0)
        ret = NOT_ALLOWED_CODE;
    else if (strncmp(str, "POST ", 5) == 0)
        ret = NOT_IMPLEMENTED_CODE;
    else
        ret = SUCCESS_CODE;

    return ret;
}

int validate_uri(char *uri)
{
    char *curr;

    if (uri == NULL)
        return BAD_REQUEST_CODE;

    if (strlen(uri) > PATH_MAX)
        return URI_TOO_LONG_CODE;

    for (curr = uri; *curr; curr++)
        if (strchr(VALID_URI_CHARACTERS, *curr) == NULL)
            return BAD_REQUEST_CODE;

    if (strstr(uri, "../") != NULL)
        return BAD_REQUEST_CODE;

    return SUCCESS_CODE;
}

char *parse_uri(char *str)
{
    char *ret;
    int size;
    int uri_start;
    int uri_end;
    int username_start;
    int username_end;
    int home;
    int need_slash;

    need_slash = FALSE;

    /* Step 1: Figure out where the URI starts and ends in the request string */
    for (uri_start = 1; str[uri_start] && str[uri_start - 1] != ' '; uri_start++)
        ;

    for (uri_end = uri_start; str[uri_end] && str[uri_end] != ' ' && str[uri_end] != '\r' && str[uri_end] != '\n'; uri_end++)
        ;

    /* Step 2: Determine if we need to make it a home directory */
    home = (str[uri_start] == '~' || str[uri_start + 1] == '~') ? TRUE : FALSE;

    /* Step 3: Determine size to malloc() for return value and malloc */
    size = strlen(config.root_dir);

    if (home == FALSE && config.root_dir[size - 1] != '/' && str[uri_start] != '/')
    {
        need_slash = TRUE;
        size += 1;
    }

    if (home == TRUE)
    {
        size += strlen("/home//sws/");
        size -= (str[uri_start] == '~') ? 1 : 2;

        /* Figure out where the username starts and ends */
        username_start = (str[uri_start] == '~') ? uri_start + 1 : uri_start + 2;
        if (str[username_start] == '/')
            username_start++;
        for (username_end = username_start + 1; str[username_end] && str[username_end] != '/' &&
                                                str[username_end] != '\r' && str[username_end] != '\n' &&
                                                str[username_end] != ' '; username_end++)
            ;
    }

    size += (uri_end - uri_start);

    if ((ret = (char*) malloc((size + 1) * sizeof(char))) == NULL)
        warn_and_die(FALSE, "malloc failed: %s", strerror(errno));

    /* Step 4: Build the path */
    if (home == TRUE)
    {
        (void) strncpy(ret, "/home/", size);
        (void) strncat(ret, str + username_start, username_end - username_start);
        (void) strncat(ret, "/sws/", size);
        if (str[username_end] == '/')
            (void) strncat(ret, str + username_end + 1, uri_end - username_end - 1);
        else
            (void) strncat(ret, str + username_end, uri_end - username_end);
    }
    else
    {
        (void) strncpy(ret, config.root_dir, size);
        if (need_slash)
            (void) strncat(ret, "/", 1);
        if (config.root_dir[strlen(config.root_dir) - 1] == '/' && str[uri_start] == '/')
            (void) strncat(ret, str + uri_start + 1, uri_end - uri_start - 1);
        else
            (void) strncat(ret, str + uri_start, uri_end - uri_start);
    }

    ret[size] = '\0';
    return ret;
}

int parse_version(char *str)
{
    int sz;
    int j;

    if (elem_count(str) == 2)
        return 0; /* Simple request - the method has already been validated, so assume the second element is the URI */

    for (sz = 0; str[sz] && str[sz] != '\r' && str[sz] != '\n'; sz++)
        ;

    for (j = sz; j > 1 && str[j - 1] != ' '; j--)
        ;

    return (strncmp(str + j, "HTTP/1.0", 8) != 0 && strncmp(str + j, "HTTP/0.9", 8) != 0);
}

time_t parse_modified_since(char *headers)
{
    char *date;
    struct tm tm;

    if ((date = strstr(headers, MODIFIED_SINCE_HEADER_NAME)) == NULL)
        return -1;

    date += strlen(MODIFIED_SINCE_HEADER_NAME);

    while (date[0] == ' ')
        date++;

    //Check rfc1123 format
    if(strptime(date, "%a, %d %b %Y %H:%M:%S %Z", &tm) == NULL)
    {
        //Check rfc850 format
        if(strptime(date, "%A, %d-%b-%y %H:%M:%S %Z", &tm) == NULL)
        {
            //Check asctime format
            if(strptime(date, "%a, %b %n%d %H:%M:%S %Y", &tm) == NULL)
            {
                return -1;
            }
        }
    }

    return mktime(&tm);
}

int parse_request(char *headers, int sock)
{
    int res;

    if ((res = parse_method(headers)) != SUCCESS_CODE)
        return res;

    if (parse_version(headers) != 0)
        return VERSION_NOT_SUPPORTED_CODE;

    return SUCCESS_CODE;
}
