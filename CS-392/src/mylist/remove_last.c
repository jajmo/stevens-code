#include "mylist.h"

/*
 * remove_last()
 *
 * Remove the last node from the list, and return a pointer to the data stored
 * in the node
 *
 * Precondition: The list contains at least one element
 * Postcondition: A pointer to the data of the last node is returned
 *
 * @param head - A double pointer to the head of the list
 * @return void* - The data contained inside the last node
 */
void* remove_last(t_node** head)
{
    t_node* nextNode;
    void* returnElem = NULL;

    if(head != NULL && *head != NULL)
    {
        nextNode  = *head;

        while(nextNode->next->next != NULL)
            nextNode = nextNode->next;

        returnElem = nextNode->next->elem;
        nextNode->next = NULL;
    }

    return returnElem;
}
