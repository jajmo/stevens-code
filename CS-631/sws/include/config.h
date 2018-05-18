#ifndef _CONFIG_H_
#define _CONFIG_H_

#define DEFAULT_PORT 8080

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

typedef struct s_config {
    char *cgi_dir;
    int debug_mode;
    char *bind_addr;
    char *logfile;
    FILE *logfile_handle;
    int port;
    int server_socket;
    char *root_dir;
} s_config;

typedef struct c_connection {
    char *request_line;
    char *cli_ip;
} c_connection;

extern c_connection client_connection;
extern s_config config;

#endif