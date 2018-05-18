#include "mylist.h"

/*
 * add_node_at()
 * 
 * Adds a node to the list in a specified position
 *
 * Precondition: node is preallocated, head is not null, and pos <= length(list)
 * Postcondition: node is added to pos spot in the list, treating pos as an
 * index.
 * i.e., add_node_at(node, head, 0) will add it to the front of the list.
 *
 * @param node - The node add to the list
 * @param head - The head of the list
 * @param pos - The position to add the node to
 */
void add_node_at(t_node* node, t_node** head, unsigned int pos)
{
    t_node* nextNode;

    if(head != NULL && node != NULL)
    {
        if(pos == 0 || *head == NULL)
            add_node(node, head);
        else
        {
            nextNode = *head;
            pos--;

            for( ; pos > 0 && nextNode->next != NULL; nextNode = nextNode->next, pos--)
                ;

            node->next = nextNode->next;
            nextNode->next = node;
        }
    }
}
