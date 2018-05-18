#include "myselect.h"

/*
 * Main file of myselect
 * Links everything together, and executes the program
 *
 * Precondition: argc > 1
 * Postcondition: The elements are printed on the screen
 */
int main(int argc, char** argv)
{
    if(argc != 2)
    {
        my_str("Usage: ./myselect itemSelector\n");
        exit(1);
    }

    //signal(SIGWINCH, show_elems);

    //Prepare the terminal
    init_terminal();

    return 0;
}