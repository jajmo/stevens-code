/*
 * CS-631 Advanced Programming in the Unix Environment
 * Homework 1
 * Author: Jason Ajmo (jajmo@stevens.edu)
 * Goal: Implement `tcp`, a trivial file copying UNIX utility
 */

#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int, char**);
int isdir(const char*);
static void usage(void);

/* Delimiter used for parsing pathnames */
#define DELIM "/"

/* Buffer size */
#define BUFSIZE 4096

int main(int argc, char **argv)
{
    int fdin, fdout, len, n;
    struct stat src, dst;
    char *path, *bname;
    char buff[BUFSIZE];

    setprogname(argv[0]);

    if (argc != 3)
        usage();

    if (isdir(argv[1]) == 1)
    {
        (void) fprintf(stderr, "Source cannot be a directory\n");
        exit(EXIT_FAILURE);
    }

    /* Get file info for permissions, and to make sure the files aren't the same file */
    if (stat(argv[1], &src) > 0)
    {
    	(void) fprintf(stderr, "Unable to stat source file: %s\n", strerror(errno));
    	exit(EXIT_FAILURE);
    }
   
    if (isdir(argv[2]) == 1)
    {
        /*
         * This is only checked if it's a directory because if the user is copying a file
         * to a new file location, errno will always be > 0 since the file won't exist yet
         */
        if (errno != 0)
        {
            (void) fprintf(stderr, "Unable to open destination directory: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        /* Extract the basename from the source to construct a full path */
        bname = basename(argv[1]);
        len = strlen(argv[2]) + strlen(bname);
        if ((path = malloc(len)) == NULL)
        {
            (void) fprintf(stderr, "Unable to allocate memory: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }

        (void) strcpy(path, argv[2]);

        /* 
         * If the dest is a directory and doesn't end with a /, add it 
         * This adds support for copying to the current directory (.), previous directory (..), etc
         */
        if (argv[2][strlen(argv[2]) - 1] != '/')
        {
            if ((path = realloc(path, len + 1)) == NULL)
            {
                (void) fprintf(stderr, "Unable to allocate memory: %s\n", strerror(errno));
                exit(EXIT_FAILURE);
            }

            (void) strcat(path, DELIM);
        }

        (void) strcat(path, bname);
    }
    else
    {
        if ((path = strdup(argv[2])) == NULL)
        {
            (void) fprintf(stderr, "Unable to allocate memory: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    /* Make sure source and dest aren't the same inode */
    if (stat(path, &dst) > -1 && src.st_ino == dst.st_ino)
    {
        (void) fprintf(stderr, "Source and destination cannot be the same file\n");
        free(path);
        exit(EXIT_FAILURE);
    }

    if ((fdin = open(argv[1], O_RDONLY)) < 0)
    {
        (void) fprintf(stderr, "Unable to open source file: %s\n", strerror(errno));
        free(path);
        exit(EXIT_FAILURE);
    }

    if ((fdout = open(path, O_WRONLY | O_CREAT | O_TRUNC, src.st_mode)) < 0)
    {
        (void) fprintf(stderr, "Unable to open destination file: %s\n", strerror(errno));
        (void) close(fdin);
        free(path);
        exit(EXIT_FAILURE);
    }

    errno = 0;

    while ((n = read(fdin, buff, BUFSIZE)) > 0)
    {
        if (write(fdout, buff, n) < n)
            break;
    }

    if (errno > 0)
    {
        (void) fprintf(stderr, "Copying failed: %s\n", strerror(errno));
        (void) close(fdin);
        (void) close(fdout);
        free(path);
        exit(EXIT_FAILURE);
    }

    (void) close(fdin);
    (void) close(fdout);
    free(path);

    return EXIT_SUCCESS;
}

/*
 * Check if a path is a directory
 */
int isdir(const char *path)
{
    struct stat finfo;
    (void) stat(path, &finfo);
    return S_ISDIR(finfo.st_mode);
}

static void usage()
{
    (void) fprintf(stderr, "Usage: %s file1 file2\n", getprogname());
    exit(EXIT_FAILURE);
}