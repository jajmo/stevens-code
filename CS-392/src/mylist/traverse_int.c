#include "mylist.h"

/*
 * traverse_int()
 *
 * Prints out the list, assuming each elem is an int
 *
 * Precondition: Each elem in the list is an int
 * Postcondition: The list is printed
 *
 * @param head - A pointer to the head of the list
 */
void traverse_int(t_node* head)
{
    t_node* nextNode = head;
    int* ptr;

    while(nextNode != NULL)
    {
        if(nextNode->elem == NULL)
            my_str("NULL");
        else
        {
            ptr = (int*) nextNode->elem;
            my_int(*ptr);
        }

        my_str(" ");
        nextNode = nextNode->next;
    }

    my_char('\n');
}

