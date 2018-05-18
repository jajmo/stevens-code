#include "mylist.h"

/*
 * node_at()
 *
 * Get the node from the location specified by num
 *
 * Precondition: head is not null, and num <= length(list)
 * Postcondition: A pointer to the node is returned
 *
 * @param head - The head of the list
 * @param num - The number node to return
 * @return t_node* - A pointer to the found node
 */
t_node* node_at(t_node* head, unsigned int num)
{
    t_node* nextNode = NULL;

    if(head != NULL)
    {
        nextNode = head;

        while(nextNode->next != NULL && num > 0)
        {
            nextNode = nextNode->next;
            num--;
        }
    }

    return nextNode;
}
