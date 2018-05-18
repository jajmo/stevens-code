#include "socketsgtk.h"

/*
 * quit_button()
 *
 * Signal callback for the x button on all windows that it should be disabled for
 *
 * Precondition: None
 * Postcondition: An error message is printed to the terminal, and the program doesn't exit
 */
gint quit_button()
{
    g_print("Please use the Quit button!\n");
    return TRUE;
}