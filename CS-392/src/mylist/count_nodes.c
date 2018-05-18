#include "mylist.h"

/*
 * count_nodes()
 *
 * Counts the number of nodes in the current list
 *
 * Precondition: head is not null
 * Postcondition: The number of nodes is returned
 *
 * @param head - The head of the list
 * @return unsigned int - The number of nodes in the list
 */
unsigned int count_nodes(t_node* head)
{
    unsigned int num = 0;

    if(head != NULL)
    {
        t_node* nextElem = head;

        while(nextElem != NULL)
        {
            nextElem = nextElem->next;
            num++;
        }
    }

    return num;
}
