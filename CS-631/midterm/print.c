#include "print.h"

/* Short print elements, i.e. default `ls` output */
void short_print(FTSENT *entry)
{
    struct stat *sp;
    char *name;
    int sz;

    if (entry == NULL)
        return;

    if (entry->fts_info != FTS_NS && entry->fts_info != FTS_NSOK)
        sp = entry->fts_statp;
    else
        sp = NULL;

    sz = 0;

    if (sp != NULL)
    {
        if (flag_i == TRUE)
            (void) printf("%*s%zu ", num_len(sizes.inode) - num_len(sp->st_ino), "", sp->st_ino);

        if (flag_s == TRUE)
        {
            if (flag_h == TRUE)
                (void) printf("%*s%s ", sizes.size - (int) strlen(get_human_size(sp->st_size)), 
                              "", get_human_size(sp->st_size));
            else
                (void) printf("%*s%s ", sizes.blocks - (int) strlen(get_blocks(sp->st_blocks)), 
                              "", get_blocks(sp->st_blocks));
        }
    }

    if (sp != NULL)
        sz = strlen(get_symbol(sp->st_mode));

    if (flag_q == TRUE && flag_w == FALSE)
    {
        name = sanitize(entry->fts_name);
        (void) printf("%s%s%*s ", name, get_symbol(sp->st_mode),
                      sizes.name - (int) strlen(name) - sz, "");
        free(name);
    }
    else
        (void) printf("%s%s%*s ", entry->fts_name, get_symbol(sp->st_mode),
                      sizes.name - (int) strlen(entry->fts_name) - sz, "");

    if (flag_1 == TRUE)
        printf("\n");
    else
        printf(" ");
}

/* Long print an entry, i.e. '-l' option */
void long_print(FTSENT *entry)
{
    char buff[MAXPATHLEN + 1];
    char path[MAXPATHLEN + 1];
    char *name;
    struct stat *sp;
    int n;

    if (entry == NULL)
        return;

    sp = entry->fts_statp;

    if (sp == NULL)
        return;

    if (flag_i == TRUE)
        (void) printf("%*s%zu ", num_len(sizes.inode) - num_len(sp->st_ino), 
                      "", sp->st_ino);

    if (flag_s == TRUE)
        (void) printf("%*s%s ", sizes.blocks - 
                     (int) strlen(get_blocks(sp->st_blocks)), "", get_blocks(sp->st_blocks));

    print_perms(sp->st_mode);

#if defined(__linux__)
    (void) printf("%*s%zu ", num_len(sizes.links) - num_len(sp->st_nlink), "", sp->st_nlink);
#else
    /* NetBSD needs slightly different formatting to print `nlink_t` */
    (void) printf("%*s%u ", num_len(sizes.links) - num_len(sp->st_nlink), "", sp->st_nlink);
#endif

    (void) printf("%s%*s  ", get_user(sp->st_uid), sizes.user - (int) strlen(get_user(sp->st_uid)), "");
    (void) printf("%s %*s ", get_group(sp->st_gid), sizes.group - (int) strlen(get_group(sp->st_gid)), "");

    if (S_ISBLK(sp->st_mode) || S_ISCHR(sp->st_mode))
        (void) printf("%s%*s%s ", get_major(sp->st_rdev), 
                      sizes.size - (int) strlen(get_major(sp->st_rdev)) - (int) strlen(get_minor(sp->st_rdev)), 
                      "", get_minor(sp->st_rdev));
    else
    {
        if (flag_h == TRUE)
            (void) printf("%*s%s ", sizes.size - (int) strlen(get_human_size(sp->st_size)),
                          "", get_human_size(sp->st_size));
        else
            (void) printf("%*s%zu ", sizes.size - num_len(sp->st_size), "", sp->st_size);
    }

    switch (time_print)
    {
    case MTIME:
        print_last_modified(sp->st_mtime);
        break;
    case ATIME:
        print_last_modified(sp->st_atime);
        break;
    case CTIM:
        print_last_modified(sp->st_ctime);
        break;
    default:
        break;
    }
        

    if (flag_q == TRUE)
    {
        name = sanitize(entry->fts_name);
        (void) printf("%s%s", name, get_symbol(sp->st_mode));
        (void) free(name);
    }
    else
        (void) printf("%s%s", entry->fts_name, get_symbol(sp->st_mode));

    if (S_ISLNK(sp->st_mode))
    {
        if (entry->fts_level == FTS_ROOTLEVEL)
            (void) snprintf(path, MAXPATHLEN, "%s", entry->fts_name);
        else 
            (void) snprintf(path, MAXPATHLEN, "%s/%s", entry->fts_parent->fts_accpath, entry->fts_name);
        
        if ((n = readlink(path, buff, MAXPATHLEN)) > 0)
        {
            buff[n] = '\0';
            (void) printf(" -> %s", buff);
        }
    }

    (void) printf("\n");
}

/* Get either the group's name, or ID */
char *get_group(gid_t gid)
{
    struct group *g;
    static char buff[BUFSIZ];

    if (flag_n == TRUE || (g = getgrgid(gid)) == NULL)
        (void) snprintf(buff, BUFSIZ, "%d", gid);
    else
        (void) snprintf(buff, BUFSIZ, "%s", g->gr_name);

    return buff;
}

/* Get either the user's name, or ID */
char *get_user(uid_t uid)
{
    struct passwd *p;
    int sz;
    static char buff[BUFSIZ];

    if (flag_n == TRUE || (p = getpwuid(uid)) == NULL)
        sz = snprintf(buff, BUFSIZ, "%d", uid);
    else
        sz = snprintf(buff, BUFSIZ, "%s", p->pw_name);

    if (sz > 0)
        return buff;
    else
        return "";
}

/* Convert file size to a human readable format */
char *get_human_size(off_t fsize)
{
    int i;
    int sz;
    double res;
    static char buff[6]; /* Size will never be > 5 characters: 1000G */
    const char* units[] = {"B", "K", "M", "G", "T", "P", "E", "Z", "Y"};

    res = fsize;
    i = 0;

    while (res > 1024)
    {
        res /= 1024;
        i++;
    }

    if (res > 10 || res == 0 || i == 0)
        sz = snprintf(buff, 6, "%d%s", (int) round(res), units[i]);
    else
        sz = snprintf(buff, 6, "%.1f%s", res, units[i]);
    
    if (sz >= 0)
        return buff;
    else
        return "";
}

/* Print the time a file or directory was last modified */
void print_last_modified(time_t modified)
{
    char buff[DATE_SIZE];
    const char *fmt;
    time_t now;

    now = time(NULL);

    if (difftime(now, modified) > (365 / 2) * 86400 || difftime(modified, now) > (365 / 2) * 86400)
        fmt = "%b %e  %Y";
    else
        fmt = "%b %e %H:%M";

    /* strftime(3) automatically uses the TZ environment variable */
    if (strftime(buff, DATE_SIZE, fmt, localtime(&modified)) > 0)
        (void) printf("%s ", buff);
    else
        (void) printf("%s ", "????????????");
}

/* Print file permissions */
void print_perms(mode_t mode)
{
    char buf[13]; /* strmode(3) always returns 12 bytes + null terminator */

    strmode(mode, buf);
    (void) printf("%s ", buf);
}

/* Print the file symbol (-F flag) */
char *get_symbol(mode_t mode)
{   

    if (flag_F == FALSE) return "";
    if (S_ISDIR(mode) > 0) return "/";
    else if (S_ISLNK(mode) > 0) return "@";
#ifdef S_ISWHT
    else if (S_ISWHT(mode) > 0) return "%";
#endif
    else if (S_ISSOCK(mode) > 0) return "=";
    else if (S_ISFIFO(mode) > 0) return "|";
    else if ((mode & S_IXUSR) || (mode & S_IXGRP) || (mode & S_IXOTH)) return "*";

    return "";
}

/* Returns the number of blocks used, respecting the -h and -k modifiers */
char *get_blocks(unsigned int blocks)
{
    char *env;
    int sz;
    static int bsize = 0;
    static char buff[BUFSIZ];

    if (bsize == 0)
    {
        if (flag_k == FALSE && ((env = getenv("BLOCKSIZE")) == NULL || (bsize = atoi(env)) <= 0 || bsize < DEFAULT_BLOCKSIZE))
        {
            if (env != NULL)
                warnx("unknown blocksize: %s", env);
            else if (env != NULL && bsize < DEFAULT_BLOCKSIZE)
                warnx("minimum blocksize is %d", DEFAULT_BLOCKSIZE);
            bsize = DEFAULT_BLOCKSIZE;
        }
        else
            bsize = 1024;
    }

    if (flag_h == FALSE)
        sz = snprintf(buff, BUFSIZ, "%d", (int) ceil((blocks * DEFAULT_BLOCKSIZE) / bsize));
    else
        sz = snprintf(buff, BUFSIZ, "%s", get_human_size(blocks * bsize));

    if (sz < 0)
        return "";
    else
        return buff;
}

/* Update the max column sizes */
void update_columns(FTSENT *file)
{
    int size;
    struct stat *sp;

    if ((sp = file->fts_statp) != NULL)
    {
        if (flag_s == TRUE && (size = strlen(get_blocks(sp->st_blocks))) > sizes.blocks)
            sizes.blocks = size;
        if (sp->st_ino > sizes.inode)
            sizes.inode = sp->st_ino;
        if (sp->st_nlink > sizes.links)
            sizes.links = sp->st_nlink;
        if ((size = strlen(get_user(sp->st_uid))) > sizes.user)
            sizes.user = size;
        if ((size = strlen(get_group(sp->st_gid))) > sizes.group)
            sizes.group = size;
        if ((S_ISBLK(sp->st_mode) || S_ISCHR(sp->st_mode)) && 
            (size = strlen(get_major(sp->st_rdev)) + strlen(get_minor(sp->st_rdev))) > sizes.size)
            sizes.size = size;
        else if (flag_h == FALSE && (size = num_len(sp->st_size)) > sizes.size)
            sizes.size = size;
        else if (flag_h == TRUE && (size = strlen(get_human_size(sp->st_size))) > sizes.size)
            sizes.size = size;
    }

    if ((size = strlen(file->fts_name)) > sizes.name)
        sizes.name = size;

}

char *get_minor(dev_t dev)
{
    /* minor() returns a number from 0 to 255 */
    static char buff[3 + 1];

    if (snprintf(buff, 3, "%d", minor(dev)) < 0)
        return "";
    else
        return buff;
}

char *get_major(dev_t dev)
{
    /*
     * major() returns a number from INT_MIN to INT_MAX. The length
     * needs to be hardcoded since it can't be determined at compile-time.
     * The extra 3 bytes are for the potential negative from major(), a comma,
     * and a null-terminator.
     */
    static char buff[10 + 3];

    if (snprintf(buff, 13, "%d,", major(dev)) < 0)
        return "";
    else
        return buff;
}