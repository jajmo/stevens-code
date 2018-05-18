#include "response.h"

int error_response(char *status, char *body, int sock)
{
    char *res;

    res = construct_response_text(status, body);

    if (write(sock, res, strlen(res)) < 0)
    {
        free(res);
        warn_and_die(FALSE, "write failed: %s", strerror(errno));
    }

    free(res);
    return strlen(body);
}

char *construct_response_text(char *header, char *body)
{
    char *headers;
    char *retval;
    const char *content_type;
    int sz;

    content_type = get_magic_buffer(body);
    headers = get_server_headers(content_type, strlen(body));
    sz = strlen(header) + strlen(headers) + 1;

    if (client_connection.request_line != NULL && strncmp(client_connection.request_line, "HEAD ", 5) != 0)
        sz += strlen(body);

    if ((retval = (char*) malloc(sz * sizeof(char)))  == NULL)
        warn_and_die(FALSE, "malloc failed: %s", strerror(errno));

    (void) strcpy(retval, header);
    (void) strcat(retval, headers);

    if (client_connection.request_line != NULL && strncmp(client_connection.request_line, "HEAD ", 5) != 0)
        (void) strcat(retval, body);

    free(headers);

    return retval;
}

char *get_server_headers(const char *response_type, int content_len)
{
    char buff[BUFSIZ];
    char retbuff[BUFSIZ];
    time_t now;
    struct tm *tm;

    now = time(NULL);
    if ((tm = gmtime(&now)) < 0)
        warn_and_die(FALSE, "gmtime failed: %s", strerror(errno));

    strftime(buff, sizeof(buff), "Date: %a, %d %b %Y %H:%M:%S %Z", tm);

    if (response_type != NULL)
    {
        if (snprintf(retbuff, sizeof(retbuff), "\r\nServer: " SERVER_NAME "\r\n%s\r\nContent-Length: %d\r\nContent-Type: %s\r\n\r\n",
                     buff, content_len, response_type) < 0)
            warn_and_die(FALSE, "snprintf failed: %s", strerror(errno));
    }
    else /* CGI response */
    {
        if (snprintf(retbuff, sizeof(retbuff), "\r\nServer: " SERVER_NAME "\r\n%s\r\nContent-Length: %d\r\n",
                     buff, content_len) < 0)
            warn_and_die(FALSE, "snprintf failed: %s", strerror(errno));
    }

    return strdup(retbuff);
}