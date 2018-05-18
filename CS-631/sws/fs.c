#include "fs.h"

int generate_directory_listing(char *path, int sock, int *content_length)
{
    char *server_headers;
    char *all_together;
    char fname[PATH_MAX];
    char entry[PATH_MAX];
    struct dirent **namelist;
    int handle;
    int outsize;
    int end;
    int i;
    int index;
    char *relativePath;
    char *relativePath_backup;
    char *path_scandir;

    path_scandir = strdup(path);
    outsize = 0;
    if ((handle = scandir(path_scandir, &namelist, 0, alphasort)) < 0)
    {
        free(path_scandir);
        switch(errno)
        {
        case EACCES:
            *content_length = error_response(FORBIDDEN_STATUS, FORBIDDEN_BODY, sock);
            return FORBIDDEN_CODE;
        default:
            *content_length = error_response(SERVER_ERROR_STATUS, SERVER_ERROR_BODY, sock);
            return SERVER_ERROR_CODE;
        }
    }

    relativePath = strdup(client_connection.request_line);
    relativePath_backup = relativePath;

    while (*relativePath && *relativePath != ' ')
        relativePath++;
    relativePath++;

    for (end = 0; relativePath[end] && relativePath[end] != ' ' && relativePath[end] != '\r' && relativePath[end] != '\n'; end++)
        ;
    relativePath[end] = '\0';

    /* Don't buffer everything to avoid massive buffers */
    i = 0;
    index = -1;
    while (i < handle)
    {
        if (strcmp(namelist[i]->d_name, "index.html") == 0)
        {
            index = i;
            break;
        }
        if (namelist[i]->d_name[0] == '.')
        {
            i++;
            continue;
        }
        get_html_listing(entry, relativePath, path, namelist[i]);
        outsize += strlen(entry);
        i++;
    }

    if (index > -1)
    {
        for (i = 0; i < handle; i++)
            free(namelist[i]);
        free(namelist);
        free(relativePath_backup);
        free(path_scandir);
        close(handle);
        return -1;
    }

    sprintf(fname, "<h1>Directory listing for %s</h1>", relativePath);

    outsize += strlen("<html><body></body></html>") + strlen(fname);
    server_headers = get_server_headers("text/html", outsize);

    if ((all_together = (char*) malloc(strlen(server_headers) + strlen(SUCCESS_STATUS))) == NULL)
    {
        free(server_headers);
        free(path_scandir);
        close(handle);
        warn_and_die(FALSE, "malloc failed: %s", strerror(errno));
    }

    (void) strcpy(all_together, SUCCESS_STATUS);
    (void) strcat(all_together, server_headers);

    write(sock, all_together, strlen(all_together));

    free(all_together);
    free(server_headers);

    if (client_connection.request_line != NULL && strncmp(client_connection.request_line, "HEAD ", 5) == 0)
    {
        free(path_scandir);
        return SUCCESS_CODE;
    }

    write(sock, "<html><body>", strlen("<html><body>"));
    write(sock, fname, strlen(fname));

    i = 0;
    while (i < handle)
    {
        if (namelist[i]->d_name[0] == '.')
        {
            i++;
            continue;
        }
        get_html_listing(entry, relativePath, path, namelist[i]);
        write(sock, entry, strlen(entry));
        free(namelist[i]);
        i++;
    }

    free(namelist);
    free(relativePath_backup);
    close(handle);
    free(path_scandir);
    write(sock, "</body></html>", strlen("</body></html>"));

    *content_length = outsize;
    return SUCCESS_CODE;
}

void get_html_listing(char *buff, char *path, char *abs_path, struct dirent *curr)
{
    char fname[PATH_MAX];
    char escaped[PATH_MAX];
    struct stat st;

    sprintf(fname, "%s/%s", abs_path, curr->d_name);

    urlencode(curr->d_name, escaped);

    if (stat(fname, &st) < 0)
        warn_and_die(FALSE, "stat failed: %s", strerror(errno));

    if (strcmp(path, "/") == 0)
        sprintf(fname, "%s", escaped);
    else
        sprintf(fname, "%s/%s", path, escaped);

    if (S_ISDIR(st.st_mode))
        sprintf(buff, "<a href=\"%s\">%s/</a><br />", fname, curr->d_name);
    else
        sprintf(buff, "<a href=\"%s\">%s</a><br />", fname, curr->d_name);
}

int send_file_response(char *path, int sock, int *content_length, time_t mtime)
{
    unsigned char buffer[BUFSIZ];
    int numRead;
    FILE* fd = NULL;
    struct stat st;
    char* serverHeaders;
    char* headers;
    char* cleanPath;

    cleanPath = urldecode(path);

    if(stat(cleanPath, &st) == -1)
    {
        free(cleanPath);
        if (errno == ENOENT)
        {
            *content_length = error_response(NOT_FOUND_STATUS, NOT_FOUND_BODY, sock);
            return NOT_FOUND_CODE;
        }
        else if (errno == EACCES)
        {
            *content_length = error_response(FORBIDDEN_STATUS, FORBIDDEN_BODY, sock);
            return FORBIDDEN_CODE;
        }
        else
        {
            *content_length = error_response(SERVER_ERROR_STATUS, SERVER_ERROR_BODY, sock);
            return SERVER_ERROR_CODE;
        }
    }

    if(S_ISDIR(st.st_mode))
    {
        numRead = generate_directory_listing(cleanPath, sock, content_length);

        if (numRead > -1) /* index.html not found - listing already written to client */
        {
            free(cleanPath);
            return numRead;
        }

        if ((cleanPath = (char*) realloc(cleanPath, strlen(cleanPath) + strlen("index.html") + 1)) == NULL)
            warn_and_die(FALSE, "realloc failed: %s", strerror(errno));
        (void) strcat(cleanPath, "index.html");

        if(stat(cleanPath, &st) == -1)
        {
            free(cleanPath);
            if (errno == ENOENT)
            {
                *content_length = error_response(NOT_FOUND_STATUS, NOT_FOUND_BODY, sock);
                return NOT_FOUND_CODE;
            }
            else if (errno == EACCES)
            {
                *content_length = error_response(FORBIDDEN_STATUS, FORBIDDEN_BODY, sock);
                return FORBIDDEN_CODE;
            }
            else
            {
                *content_length = error_response(SERVER_ERROR_STATUS, SERVER_ERROR_BODY, sock);
                return SERVER_ERROR_CODE;
            }
        }
    }

    if (mtime > -1 && st.st_mtime < mtime)
    {
        *content_length = error_response(NOT_MODIFIED_STATUS, "", sock);
        free(cleanPath);
        return NOT_MODIFIED_CODE;
    }

    *content_length = st.st_size;

    if((fd = fopen(cleanPath, "r")) == NULL)
    {
        free(cleanPath);
        if (errno == EACCES)
        {
            *content_length = error_response(FORBIDDEN_STATUS, FORBIDDEN_BODY, sock);
            return FORBIDDEN_CODE;
        }
        else
        {
            *content_length = error_response(SERVER_ERROR_STATUS, SERVER_ERROR_BODY, sock);
            return SERVER_ERROR_CODE;
        }
    }

    if (elem_count(client_connection.request_line) > 2)
    {
        serverHeaders = get_server_headers(get_magic_file(cleanPath), st.st_size);

        if ((headers = malloc(strlen(serverHeaders) + strlen(SUCCESS_STATUS) + 1)) == NULL)
        {
            free(serverHeaders);
            free(cleanPath);
            warn_and_die(FALSE, "malloc failed: %s", strerror(errno));
        }

        (void) strcpy(headers, SUCCESS_STATUS);
        (void) strcat(headers, serverHeaders);

        if(write(sock, headers, strlen(headers)) < strlen(headers))
        {
            free(headers);
            free(serverHeaders);
            free(cleanPath);
            warn_and_die(FALSE, "write failed: %s", strerror(errno));
        }

        free(serverHeaders);
        free(headers);

        if (client_connection.request_line != NULL && strncmp(client_connection.request_line, "HEAD ", 5) == 0)
        {
            fclose(fd);
            free(cleanPath);
            return SUCCESS_CODE;
        }
    }

    while((numRead = fread(buffer, 1, BUFSIZ, fd)) > 0)
    {
        if(write(sock, buffer, numRead) < numRead)
        {
            fclose(fd);
            warn_and_die(FALSE, "fopen failed: %s", strerror(errno));
        }
    }

    free(cleanPath);
    fclose(fd);
    return SUCCESS_CODE;
}
