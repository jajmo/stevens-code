#include "socketsgtk.h"

/*
 * close_quit_window()
 *
 * Signal callback for the no button of the quit confirmation window
 *
 * Precondition: None
 * Postcondition: The quit window is closed, and the main widnow's widgets are reenabled
 *
 * @param GtkWidget* w The widget clicked. In this case, the no button
 * @param gpointer d The main quit window
 */
void close_quit_window(GtkWidget* w, gpointer d)
{
    enable_main();
    gtk_widget_destroy(w);
}