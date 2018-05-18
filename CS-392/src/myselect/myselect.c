#include "myselect.h"

/*
 * Main file of myselect
 * Links everything together, and executes the program
 *
 * Precondition: argc > 1
 * Postcondition: The elements are printed on the screen
 */
int      main(int argc, char** argv)
{
    int  count;
    int  bytes;
    char input[READMIN + 2];

    if(argc < 2 || !my_strpos(argv[1], '*'))
    {
        my_str("No files found!\n");
        exit(1);
    }

    signal(SIGWINCH, show_elems);

    //Get all the termcaps
    init_caps();

    //Prepare the terminal
    init_terminal();

    //Setup the elements
    setup_elems(argc - 1, &argv[1]);

    //Turn off the cursor
    tputs(gl_env.cursoroff, 0, my_termprint);

    //Print the elements for the first time
    show_elems();

    //Main loop
    while(1)
    {
        bytes = read(0, &input, READMIN + 2);
        input[bytes] = '\0';

        if(!gl_env.flag)
        {
            check_char(input);
        }
    }
    
    return 0;
}