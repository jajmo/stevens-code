#include "mylist.h"

/*
 * add_node()
 *
 * Adds a pre-allocated node to the front of the list
 *
 * Precondition: node is preallocated, and head is not null
 * Postcondition: node is added to the front of the list
 *
 * @param node - The node to add to the list
 * @param head - The head of the list
 */
void add_node(t_node* node, t_node** head)
{
    if(node != NULL && head != NULL)
    {
        if(*head == NULL)
            *head = node;
        else
        {
            node->next = *head;
            *head = node;
        }
    }
}
