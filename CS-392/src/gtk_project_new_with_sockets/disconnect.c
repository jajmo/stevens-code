#include "socketsgtk.h"

/*
 * disconnect()
 *
 * Disconnect from the server
 *
 * Precondition: None
 * Postcondition: /exit is sent to the server if sockfd > -1, and the client resets to start state
 */

void disconnect()
{
    if(gl_env.sockfd > -1)
    {
        write(gl_env.sockfd, "/exit", 6);
        gl_env.sockfd = -1;
        g_print("Disconnected\n");
        gtk_signal_handler_block(gl_env.connect_button, gl_env.connect_id);
        gtk_toggle_button_set_active((GtkToggleButton*) gl_env.connect_button, FALSE);
        gtk_signal_handler_unblock(gl_env.connect_button, gl_env.connect_id);
        gtk_button_set_label((GtkButton*) gl_env.connect_button, "Connect");
    }
}