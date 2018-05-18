#include "common.h"

void warn_and_die(int print_usage, char *format, ...)
{
    va_list args;

    va_start(args, format);
    fprintf(stderr, "%s: ", getprogname());
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);

    cleanup();
    if (print_usage == TRUE)
        usage();
    else
        exit(1);
}

void cleanup()
{
    (void) unlink(PID_FILE);

    if (config.cgi_dir != NULL)
        free(config.cgi_dir);
    if (config.logfile != NULL)
        free(config.logfile);
    if (config.bind_addr != NULL)
        free(config.bind_addr);
    if (config.server_socket > -1)
        close(config.server_socket);
    if (client_connection.request_line != NULL)
        free(client_connection.request_line);
    if (config.logfile_handle != NULL)
        fclose(config.logfile_handle);
}

void usage()
{
    fprintf(stderr, "Usage: %s [−dh] [−c dir] [−i address] [−l file] [−p port] dir\n", getprogname());
    exit(EXIT_FAILURE);
}

const char *get_magic_buffer(char *str)
{
    const char *content_type;
    magic_t cookie;

    cookie = get_magic_cookie();

    if ((content_type = magic_buffer(cookie, str, strlen(str))) == NULL)
        content_type = DEFAULT_CONTENT_TYPE;

    magic_close(cookie);
    return content_type;
}

const char *get_magic_file(char *file)
{
    const char *content_type;
    magic_t cookie;
    
    cookie = get_magic_cookie();

    if ((content_type = magic_file(cookie, file)) == NULL)
        content_type = DEFAULT_CONTENT_TYPE;

    if (strncmp(content_type, "inode/x-empty", 13) == 0)
        content_type = DEFAULT_CONTENT_TYPE;

    magic_close(cookie);
    return content_type;
}

magic_t get_magic_cookie()
{
    magic_t cookie;

    if ((cookie = magic_open(MAGIC_MIME)) == NULL)
        warn_and_die(FALSE, "magic failed: %s", strerror(errno));

    if (magic_load(cookie, NULL) < 0)
        warn_and_die(FALSE, "magic_load failed: %s", strerror(errno));

    return cookie;
}

void log_request(int status, int content_length)
{
    char buff[BUFSIZ];
    char *proc;
    time_t now;
    struct tm *tptr;
    int i;

    if (config.debug_mode == FALSE && config.logfile_handle == NULL)
        return; /* Avoid doing extra work */

    now = time(NULL);
    tptr = localtime(&now);
    strftime(buff, BUFSIZ, "[%d/%b/%Y:%T %z]", tptr);

    proc = (client_connection.request_line == NULL) ? "" : strdup(client_connection.request_line);

    if (client_connection.request_line != NULL)
    {
        for (i = 0; proc[i]; i++)
        {
            if (proc[i] == '\r' || proc[i] == '\n')
            {
                proc[i] = '\0';
                break;
            }
        }
    }

    if (config.debug_mode == TRUE)
    {
        printf(LOG_FORMAT, client_connection.cli_ip, buff, proc, status, content_length);
        fflush(stdout);
    }
    else if (config.logfile_handle != NULL)
    {
        fprintf(config.logfile_handle, LOG_FORMAT, client_connection.cli_ip, buff, proc, status, content_length);
        fflush(config.logfile_handle);
    }

    if (client_connection.request_line != NULL)
        free(proc);
}

int elem_count(char *str)
{
    int elems;
    int i;

    for (i = 0, elems = 0; str[i] && str[i] != '\n' && str[i] != '\r'; i++)
    {
        if (str[i] == ' ')
            elems++;
    }

    if (str[i] == '\0' || str[i] == '\r' || str[i] == '\n')
        elems++;

    return elems;
}

int is_valid_path(const char *path)
{
    struct stat st;
    if (path == NULL)
        return 0;
    return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
}


char *get_cgi_absolute_path(const char *path)
{
    char *abs_path = NULL;
    char tmp[PATH_MAX];
    int start;
    int end;

    if(config.cgi_dir == NULL)
        return NULL;
    
    abs_path = (char *) malloc(sizeof(char) * PATH_MAX);

    if (abs_path == NULL) {
        fprintf(stderr,"can't allocate memory");
        return NULL;
    }

    for (start = 0; client_connection.request_line[start]; start++)
        if (client_connection.request_line[start] == ' ')
            break;
    start += strlen("/cgi-bin") + 1;

    for (end = start; client_connection.request_line[end]; end++)
        if (client_connection.request_line[end] == ' ' || client_connection.request_line[end] == '\r' || client_connection.request_line[end] == '\n'
            || client_connection.request_line[end] == '?')
            break;

    snprintf(tmp, end - start + 1, "%s", client_connection.request_line + start);

    if (config.cgi_dir[strlen(config.cgi_dir) - 1] == '/' && tmp[0] == '/')
        snprintf(abs_path, PATH_MAX, "%s%s", config.cgi_dir, tmp + 1);
    else
        snprintf(abs_path, PATH_MAX, "%s%s", config.cgi_dir, tmp);

    return abs_path;

}

int validate_stat(const char *path,struct stat *req_stat)
{
    int ret = 0;
    if (stat(path, req_stat) < 0) {
        if (errno == ENOENT)
            ret = 404;
        else if (errno == EACCES)
            ret = 403;
        else
            ret = 400;
        return ret;
    }

    if (access(path, R_OK) < 0) {
        if (errno == EACCES)
            ret = 403;
        else
            ret = 400;
        return ret;
    }
    return ret;
}




