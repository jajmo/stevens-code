#include "cgi_handler.h"


int *handle_cgi(/*Input cgi request*/char *request,int cli_sock)
{
    char *path;
    int pipefd[2];
    char buffer[BUFSIZ];
    pid_t pid;
    int status;
    struct stat request_stat;
    int http_code;

    path = get_cgi_absolute_path(request);

    if (validate_uri(request)!= SUCCESS_CODE) 
    {
        error_response(BAD_REQUEST_STATUS,BAD_REQUEST_BODY,cli_sock);
        return 0;
    }

    if (path == NULL) 
    {
        error_response(SERVER_ERROR_STATUS,SERVER_ERROR_BODY,cli_sock);
        return 0;
    }

    do{
        
        if ((http_code = validate_stat(path,&request_stat)) != 0) 
        {
            if(http_code==400)
            {
                error_response(BAD_REQUEST_STATUS,BAD_REQUEST_BODY,cli_sock);  
            } 
            else if (http_code==403)
            {
                error_response(FORBIDDEN_STATUS,FORBIDDEN_BODY,cli_sock); 
            }
            else
            {
                error_response(NOT_FOUND_STATUS,NOT_FOUND_BODY,cli_sock);  
            }  
                
            break;
        }

        if (!S_ISREG(request_stat.st_mode)) 
        {           
            error_response(FORBIDDEN_STATUS,FORBIDDEN_BODY,cli_sock);
            break;
        }

        if (access(path, X_OK) == -1) 
        {
            error_response(FORBIDDEN_STATUS,FORBIDDEN_BODY,cli_sock);
            break;
        }
        if (pipe(pipefd) == -1) 
        {
            error_response(SERVER_ERROR_STATUS,SERVER_ERROR_BODY,cli_sock);
            break;
        }

        pid = fork();
        if (pid == -1) 
        {
            error_response(SERVER_ERROR_STATUS,SERVER_ERROR_BODY,cli_sock);
            break;
        }    
        else if (pid == 0) 
        {
            if (dup2(pipefd[1], STDOUT_FILENO) < 0)
                warn_and_die(FALSE, "dup2 failed: %s", strerror(errno));

            close(pipefd[0]);
            setenv("QUERY_STRING", get_cgi_params(), 1);
            char *params[] = { path, (char *) 0 };

            if (execv(params[0], params) < 0) {
                //To add debugging function
                exit(1);
            }
            exit(0);
        }
        else
        {
            close(pipefd[1]);
            size_t pos = 0;
            size_t count;

            while ((count = read(pipefd[0], buffer + pos, BUFSIZ - pos)) > 0) 
                pos += count;

            if (count < 0) 
            {
                error_response(SERVER_ERROR_STATUS,SERVER_ERROR_BODY,cli_sock);
                free(path);
                return 0;
            }  

            close(pipefd[0]);

            if (WIFEXITED(status) == 0 ||  WEXITSTATUS(status) != 0) {
                error_response(SERVER_ERROR_STATUS,SERVER_ERROR_BODY,cli_sock);
                break;
            }

            buffer[pos] = '\0';
            cgi_response(buffer, strlen(buffer), cli_sock);
        }
    } while(0);

    return 0;
}

void cgi_response(char *buffer, int buflen,int cli_sock)
{
    char *server_headers;
    char *all_together;
    server_headers = get_server_headers(NULL, buflen);
    if ((all_together = (char*) malloc(strlen(server_headers) + strlen(SUCCESS_STATUS) + strlen(buffer))) == NULL)
    {
        warn_and_die(FALSE, "malloc failed: %s", strerror(errno));
    }
    (void) strcpy(all_together, SUCCESS_STATUS);
    (void) strcat(all_together, server_headers);
    (void) strcat(all_together, buffer);
    send(cli_sock, all_together, strlen(all_together), 0);
    free(all_together);
}

char *get_cgi_params()
{
    int start;
    int end;
    static char buff[BUFSIZ];

    for (start = 0; client_connection.request_line[start]; start++)
        if (client_connection.request_line[start] == '?')
            break;

    if (client_connection.request_line[start] == '\0')
        return "";

    start++;
    for (end = start; client_connection.request_line[end]; end++)
        if (client_connection.request_line[end] == ' ' || client_connection.request_line[end] == '\r' || client_connection.request_line[end] == '\n')
            break;

    snprintf(buff, end - start + 1, "%s", client_connection.request_line + start);
    return buff;
}