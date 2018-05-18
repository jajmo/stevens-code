#include "print.h"

/* Master FTS print function */
void fts_print(FTSENT *path)
{
    unsigned long blocks;
    unsigned long size;
    FTSENT *curr;
    FTSENT **entries;
    unsigned int count;
    int denom;
    int rentries;
    int nrows;
    int ecount;
    int row;
    int total;

    if (path == NULL)
        return;

    reset_sizes();
    blocks = total = size = 0;
    count = 0;

    /* The entries must be iterated over twice: once for stats, once for printing */
    for (curr = path; curr != NULL; curr = curr->fts_link)
    {
        if (need_show_file(curr) == FALSE)
            curr->fts_number = FTS_IGNORE;

        /* 
         * This will only be triggered when processing file operands, in which case,
         * directories will be printed in later fts iterations
         */
        if (curr->fts_level == FTS_ROOTLEVEL && curr->fts_info == FTS_D && flag_d == FALSE)
            curr->fts_number = FTS_IGNORE;

        if (curr->fts_info == FTS_ERR || curr->fts_info == FTS_NS || curr->fts_info == FTS_NSOK || curr->fts_info == FTS_DNR)
            curr->fts_number = FTS_IGNORE;

        if (curr->fts_number == FTS_IGNORE)
            continue;

        count++;

        if (path->fts_level != FTS_ROOTLEVEL)
        {
            size += curr->fts_statp->st_size;
            blocks += curr->fts_statp->st_blocks;
        }

        update_columns(curr);
    }

    if (count == 0)
        return;

    entries = (FTSENT**) xmalloc((count + 1) * sizeof(FTSENT*));
    for (denom = 0, curr = path; curr != NULL; curr = curr->fts_link)
    {
        if (curr->fts_number == FTS_IGNORE)
            continue;

        entries[denom++] = curr;
    }

    entries[denom] = NULL;

    denom = sizes.name + 1;
    denom += (flag_i == TRUE) ? num_len(sizes.inode) + 1 : 0;
    denom += (flag_s == TRUE) ? sizes.blocks + 1 : 0;

    if (flag_F == TRUE)
        denom += 1;

    rentries = floor((double) columns / denom);
    nrows = ceil((double) count / rentries);

    if ((flag_l == TRUE || flag_n == TRUE || flag_s == TRUE) && path->fts_level != FTS_ROOTLEVEL)
    {
        if (flag_h == TRUE)
            (void) printf("total %s\n", get_human_size(size));
        else
            (void) printf("total %s\n", get_blocks(blocks));
    }

    total = count;
    denom = count = ecount = row = 0;

    /* 
     * If 0 entries fit on a row, default to -1 (one).
     * This means the terminal is too small for columnizing.
     */
    if (rentries == 0)
    {
        flag_1 = TRUE;
        flag_C = flag_x = FALSE;
    }

    if (flag_C == TRUE)
    {
        while (denom < total)
        {
            if (count < total)
            {
                short_print(entries[count]);
                ++denom;
            }

            count += nrows;
            ++ecount;

            if (ecount == rentries)
            {
                count = ++row;
                ecount = 0;
                (void) printf("\n");
            }
        }

        if (ecount > 0)
            (void) printf("\n");
    }
    else
    {
        for (count = 0, ecount = 0; entries[count] != NULL; count++, ecount++)
        {
            if (flag_x == TRUE && ecount == rentries)
            {
                (void) printf("\n");
                ecount = 0;
            }

            if (flag_l == TRUE || flag_n == TRUE)
                long_print(entries[count]);
            else
                short_print(entries[count]);
        }

        if (flag_x == TRUE)
            (void) printf("\n");
    }

    free(entries);
    output = 1;
}