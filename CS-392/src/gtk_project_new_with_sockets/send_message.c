#include "socketsgtk.h"

/*
 * send_message()
 *
 * Send a message to the server
 *
 * Precondition: The client is connected to the server
 * Postcondition: The message is sent, or an error message is printed
 *
 * @param GtkWidget* w The send button
 * @param gpointer d null
 */
void       send_message(GtkWidget* w, gpointer d)
{
    char  message[2];
    char* user_message;
    int   bytes_read;

    user_message = (char*) gtk_entry_get_text((GtkEntry*) gl_env.message_input);

    if(gl_env.sockfd == -1)
    {
        g_print("ERROR: Not connected to server\n");
        return;
    }

    if(my_strcmp(user_message, "") == 0)
    {
        g_print("ERROR: Please enter a message\n");
        return;
    }

    if(write(gl_env.sockfd, user_message, my_strlen(user_message) + 1) < 0)
    {
        g_print("Communication with server failed!\n");
        disconnect();
    }

    bytes_read = read(gl_env.sockfd, message, 3);

    if(bytes_read < 1)
    {
        my_str("Server closed connection!\n");
        gtk_toggle_button_set_active((GtkToggleButton*) gl_env.connect_button, FALSE);
        return;
    }

    if(my_strncmp(user_message, "/exit", 5) == 0 && (user_message[5] == ' ' || !user_message[5]))
    {
        gtk_toggle_button_set_active((GtkToggleButton*) gl_env.connect_button, FALSE);
    }

    gtk_entry_set_text((GtkEntry*) gl_env.message_input, "");
}