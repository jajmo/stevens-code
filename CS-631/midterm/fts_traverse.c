#include "print.h"

/* Core function of the program that traverses the operands */
void fts_traverse(char **entries, int count)
{
    FTS *filesystem;
    FTSENT *parent;
    int fts_options;
    int ch_options;
    int printed;

    fts_options = FTS_PHYSICAL;
    ch_options = printed = 0;

    if (flag_a == TRUE)
        fts_options |= FTS_SEEDOT;

    if ((filesystem = fts_open(entries, fts_options, (flag_f == TRUE) ? NULL : &fts_cmp)) == NULL)
        errx(EXIT_FAILURE, "fts_open() failed: %s\n", strerror(errno));

    fts_print(fts_children(filesystem, 0));

    while ((parent = fts_read(filesystem)) != NULL)
    {
        parent->fts_info = (flag_d == TRUE && parent->fts_info == FTS_D) ? FTS_F : parent->fts_info;
        switch (parent->fts_info)
        {
        case FTS_DC:
            warnx("%s: causes a cycle", parent->fts_name);
            break;
        case FTS_NS:
        case FTS_DNR:
        case FTS_ERR:
            if (parent->fts_level != FTS_ROOTLEVEL)
                warnx("%s: %s", parent->fts_name, strerror(parent->fts_errno));
            else
                warnx("%s: %s", parent->fts_path, strerror(parent->fts_errno));
            break;
        case FTS_D:
            if (output == 1)
                (void) printf("\n%s:\n", parent->fts_path);
            else if (count > 1)
            {
                (void) printf("%s:\n", parent->fts_path);
                output = 1;
            }

            fts_print(fts_children(filesystem, ch_options));

            if (flag_R == FALSE)
                (void) fts_set(filesystem, parent, FTS_SKIP);
            break;
        default:
            break;
        }
    }

    (void) fts_close(filesystem);
}