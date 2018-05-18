/*
 * CS-631 Advanced Programming in the Unix Environment
 * Midterm
 * Author: Jason Ajmo (jajmo@stevens.edu)
 * Goal: Implement `ls(1)`
 */

#include "ls.h"

column_fmt sizes = { 0, 0, 0, 0, 0, 0, 0 };

FLAG flag_A = FALSE;
FLAG flag_a = FALSE;
FLAG flag_c = FALSE;
FLAG flag_C = FALSE;
FLAG flag_d = FALSE;
FLAG flag_F = FALSE;
FLAG flag_f = FALSE;
FLAG flag_h = FALSE;
FLAG flag_i = FALSE;
FLAG flag_k = FALSE;
FLAG flag_l = FALSE;
FLAG flag_n = FALSE;
FLAG flag_q = FALSE;
FLAG flag_R = FALSE;
FLAG flag_r = FALSE;
FLAG flag_S = FALSE;
FLAG flag_s = FALSE;
FLAG flag_t = FALSE;
FLAG flag_u = FALSE;
FLAG flag_w = FALSE;
FLAG flag_x = FALSE;
FLAG flag_1 = FALSE;

char *default_path[] = { ".", NULL };
int columns = 0;
int output = 0;
int time_print = MTIME;

int main(int argc, char** argv)
{
    int opt;
    char *cols;
    int sort;
    struct winsize w;

    setprogname(argv[0]);

    if (geteuid() == 0)
        flag_A = TRUE;

    sort = NAME;

    if (isatty(STDOUT_FILENO))
    {
        flag_q = flag_C = TRUE;
        if ((cols = getenv("COLUMNS")) == NULL || (columns = atoi(cols)) == 0)
        {
            if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) < 0)
            {
                flag_C = flag_x = FALSE;
                flag_1 = TRUE;
            }
            else
                columns = w.ws_col;
        }
    }
    else
        flag_w = flag_1 = TRUE;

    while ((opt = getopt(argc, argv, "AacCdFfhiklnqRrSstuwx1?")) != -1)
    {
        switch(opt)
        {
        case 'A':
            flag_A = TRUE;
            break;
        case 'a':
            flag_a = TRUE;
            break;
        case 'c':
            flag_c = TRUE;
            flag_u = FALSE;
            sort = TIME;
            time_print = CTIM;
            break;
        case 'C':
            flag_C = TRUE;
            flag_1 = flag_l = flag_n = flag_x = FALSE;
            break;
        case 'd':
            flag_d = TRUE;
            break;
        case 'F':
            flag_F = TRUE;
            break;
        case 'f':
            flag_f = flag_a = TRUE; /* NetBSD's implementation shows all (-a) when -f is passed in */
            sort = 0;
            break;
        case 'h':
            flag_h = TRUE;
            flag_k = FALSE;
            break;
        case 'i':
            flag_i = TRUE;
            break;
        case 'k':
            flag_k = TRUE;
            flag_h = FALSE;
            break;
        case 'l':
            flag_l = TRUE;
            flag_C = flag_1 = flag_n = flag_x = FALSE;
            break;
        case 'n':
            flag_n = TRUE;
            flag_C = flag_l = flag_1 = flag_x = FALSE;
            break;
        case 'q':
            flag_q = TRUE;
            flag_w = FALSE;
            break;
        case 'R':
            flag_R = TRUE;
            break;
        case 'r':
            flag_r = TRUE;
            break;
        case 'S':
            flag_S = TRUE;
            sort = SIZE;
            break;
        case 's':
            flag_s = TRUE;
            break;
        case 't':
            flag_t = TRUE;
            sort = TIME;
            time_print = MTIME;
            break;
        case 'u':
            flag_u = TRUE;
            flag_c = FALSE;
            sort = TIME;
            time_print = ATIME;
            break;
        case 'w':
            flag_w = TRUE;
            flag_q = FALSE;
            break;
        case 'x':
            flag_x = TRUE;
            flag_1 = flag_C = flag_l = flag_n = FALSE;
            break;
        case '1':
            flag_1 = TRUE;
            flag_C = flag_l = flag_n = flag_x = FALSE;
            break;
        case '?':
        default:
            usage();
            break;
            /* NOTREACHED */
        }
    }

    argc -= optind;
    argv += optind;

    if ((sort == TIME && flag_t == FALSE) || sort == SIZE)
        flag_u = flag_c = flag_t = FALSE;

    if (argc > 0)
        fts_traverse(argv, argc);
    else
        fts_traverse(default_path, 1);

    return EXIT_SUCCESS;
}

/* Print program usage */
static void usage()
{
    (void) fprintf(stderr, "Usage: %s [−AacCdFfhiklnqRrSstuwx1] [file ...]\n", getprogname());
    exit(EXIT_FAILURE);
}