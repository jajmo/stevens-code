#include "socketsgtk.h"

/*
 * render_quit_window()
 *
 * Render the quit confirmation window
 *
 * Precondition: None
 * Postcondition: The program either exits or the confirmation window closes
 */
void render_quit_window() 
{
    GtkWidget* win;
    GtkWidget* table;
    GtkWidget* confirm_label;
    GtkWidget* yes_button;
    GtkWidget* no_button;

    disable_main();

    table = gtk_table_new(2, 4, FALSE);

    win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    confirm_label = gtk_label_new("Are you sure you want to quit?");
    yes_button = gtk_button_new_with_label("Yes");
    no_button = gtk_button_new_with_label("No");

    gtk_window_set_title(GTK_WINDOW(win), "Confirm");
    gtk_container_add(GTK_CONTAINER(win), table);

    g_signal_connect(G_OBJECT(win), "delete_event", G_CALLBACK(close_quit_window), G_OBJECT(win));
    g_signal_connect_swapped(no_button, "clicked", G_CALLBACK(close_quit_window), G_OBJECT(win));
    g_signal_connect(yes_button, "clicked", G_CALLBACK(close_program), NULL);

    gtk_table_attach((GtkTable*) table, confirm_label, 0, 4, 0, 1, GTK_FILL, GTK_FILL, 5, 5);
    gtk_table_attach((GtkTable*) table, yes_button, 0, 2, 1, 2, GTK_FILL, GTK_FILL, 5, 5);
    gtk_table_attach((GtkTable*) table, no_button, 2, 4, 1, 2, GTK_FILL, GTK_FILL, 5, 5);
    gtk_widget_show_all(win);
}