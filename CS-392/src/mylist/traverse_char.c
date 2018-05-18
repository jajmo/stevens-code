#include "mylist.h"

/*
 * traverse_char()
 *
 * Prints out the list, assuming each elem is a char
 *
 * Precondition: The elem in every node is a char
 * Postcondition: The list is printed
 *
 * @param head - A pointer to the head of the list
 */
void traverse_char(t_node* head)
{
    t_node* nextNode = head;
    char* ptr;

    while(nextNode != NULL)
    {
        if(nextNode->elem == NULL)
            my_str("NULL");
        else
        {
            ptr = (char*) nextNode->elem;
            my_char(*ptr);
        }

        my_str(" ");
        nextNode = nextNode->next;
    }

    my_char('\n');
}

