#include "socketsgtk.h"

/*
 * disable_main()
 *
 * Disable all of the main window's widgets
 *
 * Precondition: The main window is created
 * Postcondition: All of the widgets on the main window are disabled
 */
void disable_main()
{
    gtk_widget_set_sensitive((GtkWidget*) gl_env.quit_button, FALSE);
    gtk_widget_set_sensitive((GtkWidget*) gl_env.connect_button, FALSE);
    gtk_widget_set_sensitive((GtkWidget*) gl_env.send_button, FALSE);
    gtk_widget_set_sensitive((GtkWidget*) gl_env.message_input, FALSE);
}