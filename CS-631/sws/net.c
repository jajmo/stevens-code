#include "net.h"

static _request_type get_request_type(char *name)
{
    int i;

    for (i = 0; name[i]; i++)
        if (name[i] == ' ')
            break;

    if (strncmp(name + i + 1, "/cgi-bin", 8) == 0)
        return Cgi_Request;
    return Static_Request;
}

int setup_socket()
{
    int cli_sock;
    pid_t pid;
    socklen_t len;
    struct sockaddr_in server;
    struct sockaddr_in client;

    if ((config.server_socket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        warn_and_die(FALSE, "unable to open socket");

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = (config.bind_addr == NULL) ? INADDR_ANY : inet_addr(config.bind_addr);
    server.sin_port = htons(config.port);

    if (bind(config.server_socket, (struct sockaddr *)&server, sizeof(server)) != 0)
        warn_and_die(FALSE, "unable to bind socket: %s", strerror(errno));

    len = sizeof(server);

    if (getsockname(config.server_socket, (struct sockaddr *)&server, &len) != 0)
        warn_and_die(FALSE, "unable to determine socket name: %s", strerror(errno));

    if (listen(config.server_socket, 5) < 0)
        warn_and_die(FALSE, "listen failed: %s", strerror(errno));

    if (config.debug_mode == FALSE)
        if (daemon(0, 0) < 0)
            warn_and_die(FALSE, "unable to daemonize: %s", strerror(errno));

    while (TRUE)
    {
        if ((cli_sock = accept(config.server_socket, (struct sockaddr *)&client, &len)) < 0)
            warn_and_die(FALSE, "unable to accept client: %s", strerror(errno));

        client_connection.cli_ip = inet_ntoa(client.sin_addr); /* Set this here to ensure the child gets it properly */

        if (config.debug_mode == TRUE)
        {
            handle_client(cli_sock);
            close(cli_sock);
            continue;
        }

        if ((pid = fork()) < 0)
            warn_and_die(FALSE, "fork failed: %s", strerror(errno));
        else if (pid == 0)
        {
            handle_client(cli_sock);
            close(cli_sock);
            cleanup();
            exit(EXIT_SUCCESS);
        }
        else
            close(cli_sock);
    }

    return 0;
}

void handle_client(int cli_sock)
{
    char *uri;
    char buff[BUFSIZ];
    time_t modified_since;
    int rval;
    int res;
    int content_length;
    int c;
    int first;
    int wait_for_headers;
    struct timeval timeout;

    uri = NULL;
    rval = 1;
    wait_for_headers = TRUE;
    first = TRUE;
    modified_since = -1;
    timeout.tv_sec = SOCKET_TIMEOUT;
    timeout.tv_usec = 0;

    if (setsockopt(cli_sock, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout)) < 0)
        warn_and_die(FALSE, "unable to set socket timeout: %s", strerror(errno));

    while (rval != 0)
    {
        bzero(buff, sizeof(buff));
        if ((rval = read(cli_sock, buff, BUFSIZ)) < 0)
            return;
        if (rval == 0)
            break;
        else
        {
            /*
             * This translates to:
             * - if only received CRLF (end of telnet request) or
             * - this is a simple request (no headers allowed) or
             * - it is a browser request (received CRLF * 2 somewhere in the buffer)
             * then don't wait for any more headers
             */
            if (strcmp(buff, "\r\n") == 0 || (first == TRUE && elem_count(buff) == 2) || strstr(buff, "\r\n\r\n") != NULL)
                wait_for_headers = FALSE;

            content_length = 0;

            /* Always try re-parsing for this header if it hasn't been set */
            modified_since = (modified_since < 0) ? parse_modified_since(buff) : modified_since;

            if (first == TRUE)
            {
                c = res = parse_request(buff, cli_sock);
                client_connection.request_line = strdup(buff);
            }
            else
                c = res = SUCCESS_CODE; /* short circuit switch() since request has already been validated */

            switch(res)
            {
            case SUCCESS_CODE:
                if (first == TRUE)
                {
                    /* If this is the first line received (i.e. request line via telnet), store the URI since the buff
                       will be lost on the next iteration */
                    uri = parse_uri(buff);
                    c = validate_uri(uri);
                    first = FALSE;
                }

                if (c != SUCCESS_CODE)
                    content_length = handle_code(&c, cli_sock);

                if (c != SUCCESS_CODE || wait_for_headers == TRUE)
                    break;

                if(config.cgi_dir != NULL && get_request_type(client_connection.request_line) == Cgi_Request)
                    handle_cgi(uri, cli_sock);
                else
                    c = send_file_response(uri, cli_sock, &content_length, modified_since);
                break;
            default:
                content_length = handle_code(&c, cli_sock);
                break;
            }

            if (wait_for_headers == FALSE || c != SUCCESS_CODE)
            {
                free(uri);
                log_request(c, content_length);
                return;
            }
        }
    }
}

int handle_code(int *c, int cli_sock)
{
    switch(*c)
    {
    case BAD_REQUEST_CODE:
        return error_response(BAD_REQUEST_STATUS, BAD_REQUEST_BODY, cli_sock);
        break;
    case NOT_ALLOWED_CODE:
        return error_response(NOT_ALLOWED_STATUS, NOT_ALLOWED_BODY, cli_sock);
        break;
    case VERSION_NOT_SUPPORTED_CODE:
        return error_response(VERSION_NOT_SUPPORTED_STATUS, VERSION_NOT_SUPPORTED_BODY, cli_sock);
        break;
    case URI_TOO_LONG_CODE:
        return error_response(URI_TOO_LONG_STATUS, URI_TOO_LONG_BODY, cli_sock);
        break;
    case NOT_IMPLEMENTED_CODE:
        return error_response(NOT_IMPLEMENTED_STATUS, NOT_IMPLEMENTED_BODY, cli_sock);
        break;
    default:
        *c = SERVER_ERROR_CODE;
        return error_response(SERVER_ERROR_STATUS, SERVER_ERROR_BODY, cli_sock);
        break;
    }
}
