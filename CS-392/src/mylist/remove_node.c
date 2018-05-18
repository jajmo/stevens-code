#include "mylist.h"

/*
 * remove_node()
 *
 * Remove the first node in the list, and return a pointer to the data contained
 * inside the node
 *
 * Precondition: The list contains at least one node
 * Postcondition: The first node is removed, and a pointer to the data is
 * returned
 *
 * @param head - A double pointer to the head of the list
 * @return void* - A pointer to the data contained in the first node of the list
 */
void* remove_node(t_node** head)
{
    void* nodeelem = NULL;
    t_node* headNext;

    if(head != NULL && *head != NULL)
    {
        headNext = *head;
        nodeelem = (*head)->elem;
        *head = headNext->next;
        free(headNext);
        headNext = NULL;
    }

    return nodeelem;
}
