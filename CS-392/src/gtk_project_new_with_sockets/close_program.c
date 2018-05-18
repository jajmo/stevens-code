#include "socketsgtk.h"

/*
 * close_program()
 *
 * Cleanly shutdown the close_program
 *
 * Precondition: None
 * Postcondition: The disconnect signal is sent to the server, and the program quits
 *
 * @param GtkWidget* w The widget clicked
 * @param gpointer d null
 */
void close_program(GtkWidget* w, gpointer d)
{
    if(gl_env.sockfd > -1)
    {
        disconnect();
    }

    gtk_main_quit();
}