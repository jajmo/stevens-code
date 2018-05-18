#ifndef _CONFIG_H_
#define _CONFIG_H_

#if defined(__linux__)
#include <bsd/bsd.h>
#endif

#include <stdlib.h>
#include <time.h>

#ifndef FALSE
#define FALSE 0
#endif

#ifndef TRUE
#define TRUE 1
#endif

#define FTS_IGNORE 1

#define FLAG char
#define BOOL char
#define DEFAULT_BLOCKSIZE 512
#define DATE_SIZE 13 /* Formatted date will never be > 12 characters: MMM DD HH:MM */

#define SIZE 1
#define TIME 2
#define NAME 3

#define ATIME 1
#define MTIME 2
#define CTIM 3

/* Column width for long form printing */
typedef struct s_column_fmt {
    int blocks;
    int inode;
    int links;
    int user;
    int group;
    int name;
    int size;
} column_fmt;

/*
 * All `extern` variables are initialized in `ls.c`
 */

extern char *default_path[];
extern column_fmt sizes;
extern int columns;
extern int output;
extern int time_print;

extern FLAG flag_A; /* List all entries except '.' and '..' */
extern FLAG flag_a; /* Include hidden directories and files */
extern FLAG flag_c; /* Use file last status change for sorting instead of time of last modification */
extern FLAG flag_C; /* Force multi-column output */
extern FLAG flag_d; /* Directories are listed as plain files, and symlinks in the argument list are not indirected through */
extern FLAG flag_F; /* Display certain things based on the filetype, i.e. display a slash after a directory */
extern FLAG flag_f; /* Don't sort output */
extern FLAG flag_h; /* Reports size in a human-readable format. Overrides -k */
extern FLAG flag_i; /* Print each file's serial number (inode number) */
extern FLAG flag_k; /* Report size in kilobytes */
extern FLAG flag_l; /* List in long format */
extern FLAG flag_n; /* Same as -l, except owner and group IDs are displayed numerically */ 
extern FLAG flag_q; /* Force printing of non-printable characters in file names as '?' */
extern FLAG flag_R; /* Recursively list subdirectories */
extern FLAG flag_r; /* Reverse the order of the sort */
extern FLAG flag_S; /* Sort by size, largest file first */
extern FLAG flag_s; /* Display the number of blocks used by each file */
extern FLAG flag_t; /* Sort by time modified before lexographical sorting */
extern FLAG flag_u; /* Use time of last access instead of modification for sorting or printing */
extern FLAG flag_w; /* Force raw-printing of non-printable characters */
extern FLAG flag_x; /* Multi-column output sorted across the page rather than down */
extern FLAG flag_1; /* Force ourput to be one entry per line */

#endif /* !_CONFIG_H_ */