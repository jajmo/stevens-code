#include "mylist.h"

/*
 * traverse_string()
 *
 * Prints out the list assuming each elem is a string
 *
 * Precondition: Each elem in the list is a string
 * Postcondition: The list is printed
 *
 * @param head - A pointer to the head of the list
 */
void traverse_string(t_node* head)
{
    t_node* nextNode = head;

    while(nextNode != NULL)
    {
        if(nextNode->elem == NULL)
            my_str("NULL");
        else
            my_str(nextNode->elem);

        my_str(" ");
        nextNode = nextNode->next;
    }

    my_char('\n');
}
