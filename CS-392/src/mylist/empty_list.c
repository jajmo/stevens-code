#include "mylist.h"

/*
 * empty_list()
 *
 * Clear out the list
 *
 * Precondition: None
 * Postcondition: The list is emptied
 *
 * @param head - The head of the list
 */
void empty_list(t_node** head)
{
    if(head != NULL && *head != NULL)
        for( ; *head != NULL; remove_node(head));
}
