#include "mylist.h"

/*
 * remove_node_at()
 *
 * Removes a node at a specified location, and returns a pointer to the data
 * from the removed node
 *
 * Precondition: pos <= length(list), and head is not null
 * Postcondition: A pointer to the data is returned
 *
 * @param head - A double pointer to the head of the list
 * @param pos - The position of the node to remove
 * @return void* - A pointer to the data of the removed node
 */
void* remove_node_at(t_node** head, unsigned int pos)
{
    t_node* prev;
    t_node* nextNode;
    void* returnElem = NULL;

    if(head != NULL)
    {
        if(pos == 0)
            returnElem = remove_node(head);
        else
        {
            nextNode = (*head)->next;

            while(pos > 0 && nextNode != NULL)
            {
                prev = nextNode;
                nextNode = nextNode->next;
                pos--;
            }

            returnElem = prev->elem;
            prev->next = nextNode;
        }
    }

    return returnElem;
}
