#include "sws.h"

s_config config = { NULL, FALSE, NULL, NULL, NULL, DEFAULT_PORT, -1, NULL };
c_connection client_connection = { NULL, NULL };

int main(int argc, char **argv)
{
    int opt;
    int retval;
    FILE *pidfile;

    signal(SIGINT, handle_signal);
    signal(SIGCHLD, SIG_IGN); /* We don't care about exit status of the child - just reap it and move on */

    setprogname(argv[0]);

    while ((opt = getopt(argc, argv, "c:dhi:l:p:?")) > -1)
    {
        switch (opt)
        {
        case 'c':
            config.cgi_dir = strdup(optarg);
            break;
        case 'd':
            config.debug_mode = TRUE;
            break;
        case 'i':
            config.bind_addr = strdup(optarg);
            break;
        case 'l':
            config.logfile = strdup(optarg);
            break;
        case 'p':
            config.port = atoi(optarg);
            break;
        case 'h':
        case '?':
        default:
            usage();
            break;
        }
    }

    if (config.cgi_dir != NULL && !is_valid_path(config.cgi_dir)) {
        fprintf(stderr, "%s is not a valid CGI directory!\n",config.cgi_dir);
        exit(EXIT_FAILURE);
    }
    
    if (optind >= argc)
        warn_and_die(TRUE, "root directory required");

    if (config.port < 1 || config.port > 65536)
        warn_and_die(TRUE, "invalid port number");

    if (config.logfile != NULL && config.debug_mode == FALSE && (config.logfile_handle = fopen(config.logfile, "a")) == NULL)
        warn_and_die(TRUE, "unable to open logfile: %s", strerror(errno));

    config.root_dir = argv[optind];

    if (access(config.root_dir, R_OK) < 0)
        warn_and_die(FALSE, "unable to access root directory: %s", strerror(errno));

    if (access(PID_FILE, F_OK) == 0)
        warn_and_die(FALSE, "pid file %s exists. is %s already running?", PID_FILE, getprogname());

    if ((pidfile = fopen(PID_FILE, "a")) == NULL)
        warnx("unable to open pid file (%s): %s. Continuing...", PID_FILE, strerror(errno));

    if (pidfile != NULL)
    {
        fprintf(pidfile, "%d", (int) getpid());
        fclose(pidfile);
    }

    retval = setup_socket();
    cleanup();

    return retval;
}

void handle_signal(int sig)
{
    cleanup();
    exit(0);
}