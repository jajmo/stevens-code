#include "mylist.h"

/*
 * append()
 *
 * Adds a node to the end of the list
 *
 * Precondition: node is preallocated, and head is not null
 * Postcondition: node is added to the end of the list
 *
 * @param node - The node to add to the list
 * @param head - The head of the list
 */
void append(t_node* node, t_node** head)
{
    t_node* nextNode;
    t_node* prev;

    if(head != NULL && node != NULL && *head != NULL)
    {
        prev = *head;
        nextNode = *head;

        while(nextNode != NULL)
        {
            prev = nextNode;
            nextNode = nextNode->next;
        }
        
        if(prev != NULL)
            prev->next = node;
        else
            (*head)->next = node;
    }
}
