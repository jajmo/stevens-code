#include "socketsgtk.h"

/*
 * close_connect_window()
 *
 * Signal callback for the cancel button of the connect window
 * Closes the window, resets the connect button, and reenables the main window
 *
 * Precondition: None
 * Postcondition: The window is closed, the connect button is reset, and the
 *                   main window's widgets are all reenabled
 *
 * @param GtkWidget* w The widget that was clicked. In this case, the cancel button
 * @param gpointer d null
 */
void close_connect_window(GtkWidget* w, gpointer d)
{
    gtk_signal_handler_block(gl_env.connect_button, gl_env.connect_id);
    gtk_toggle_button_set_active((GtkToggleButton*) gl_env.connect_button, FALSE);
    gtk_signal_handler_unblock(gl_env.connect_button, gl_env.connect_id);
    enable_main();
    gtk_widget_destroy(w);
}