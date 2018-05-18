#include "sort.h"

/* Compare function for FTS */
int fts_cmp(const FTSENT **first, const FTSENT **second)
{
    struct stat *s1;
    struct stat *s2;
    int i1;
    int i2;

    i1 = (*first)->fts_info;
    i2 = (*second)->fts_info;

    if (i1 == FTS_ERR || i2 == FTS_ERR)
        return 0;

    /* fts_statp cannot be used if fts_info is FTS_NS or FTS_NSOK */
    if (i1 == FTS_NS || i1 == FTS_NSOK || i2 == FTS_NS || i2 == FTS_NSOK)
    {
        if (flag_r == FALSE)
            return strcmp((*first)->fts_name, (*second)->fts_name);
        else
            return strcmp((*second)->fts_name, (*first)->fts_name);
    }

    /* Sorting the operands needs to obey some different rules first */
    if (i1 != i2 && flag_d == FALSE && (*first)->fts_level == FTS_ROOTLEVEL)
    {
        if (i1 == FTS_D)
            return 1;
        else if (i2 == FTS_D)
            return -1;
    }

    /*
     * These can never be null. The if() above that checks the info fields for
     * FTS_NS and FTS_NSOK ensure this.
     */
    s1 = (*first)->fts_statp;
    s2 = (*second)->fts_statp;

    if (flag_r == TRUE)
    {
        if (flag_t == TRUE)
        {
            if (flag_c == TRUE)
            {
                if (s1->st_ctim.tv_sec != s2->st_ctim.tv_sec)
                    return s1->st_ctim.tv_sec - s2->st_ctim.tv_sec;
                else if (s1->st_ctim.tv_nsec != s2->st_ctim.tv_nsec)
                    return s1->st_ctim.tv_nsec - s2->st_ctim.tv_nsec;
            }
            else if (flag_u == TRUE)
            {
                if (s1->st_atim.tv_sec != s2->st_atim.tv_sec)
                    return s1->st_atim.tv_sec - s2->st_atim.tv_sec;
                else if (s1->st_atim.tv_nsec != s2->st_atim.tv_nsec)
                    return s1->st_atim.tv_nsec - s2->st_atim.tv_nsec;
            }
            else
            {
                if (s1->st_mtim.tv_sec != s2->st_mtim.tv_sec)
                    return s1->st_mtim.tv_sec - s2->st_mtim.tv_sec;
                else if (s1->st_mtim.tv_nsec != s2->st_mtim.tv_nsec)
                    return s1->st_mtim.tv_nsec - s2->st_mtim.tv_nsec;
            }

            return strcmp((*second)->fts_name, (*first)->fts_name);
        }
        else if (flag_S == TRUE && s1->st_size != s2->st_size)
            return s1->st_size - s2->st_size;
        
        return strcmp((*second)->fts_name, (*first)->fts_name);
    }
    else
    {
        if (flag_t == TRUE)
        {
            if (flag_c == TRUE)
            {
                if (s1->st_ctim.tv_sec != s2->st_ctim.tv_sec)
                    return s2->st_ctim.tv_sec - s1->st_ctim.tv_sec;
                else if (s1->st_ctim.tv_nsec != s2->st_ctim.tv_nsec)
                    return s2->st_ctim.tv_nsec - s1->st_ctim.tv_nsec; 
            }
            else if (flag_u == TRUE)
            {
                if (s1->st_atim.tv_sec != s2->st_atim.tv_sec)
                    return s2->st_atim.tv_sec - s1->st_atim.tv_sec;
                else if (s1->st_atim.tv_nsec != s2->st_atim.tv_nsec)
                    return s2->st_atim.tv_nsec - s1->st_atim.tv_nsec;
            }
            else
            {
                if (s1->st_mtim.tv_sec != s2->st_mtim.tv_sec)
                    return s2->st_mtim.tv_sec - s1->st_mtim.tv_sec;
                else if (s1->st_mtim.tv_nsec != s2->st_mtim.tv_nsec)
                    return s2->st_mtim.tv_nsec - s1->st_mtim.tv_nsec;
            }

            return strcmp((*first)->fts_name, (*second)->fts_name);
        }
        else if (flag_S == TRUE && s1->st_size != s2->st_size)
            return s2->st_size - s1->st_size;

        return strcmp((*first)->fts_name, (*second)->fts_name);
    }
}