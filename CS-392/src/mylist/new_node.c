#include "mylist.h"

/*
 * new_node()
 *
 * Allocates a new node
 *
 * Precondition: data is not null
 * Postcondition: The new node is allocated in the heap, and a pointer to it is
 * returned
 *
 * @param data - The data to put inside the node
 * @param node - A pointer to the next node, or NULL
 * @return t_node* - A pointer to the new node
 */
t_node* new_node(void* data, t_node* node)
{
    t_node* newNode = NULL;
    
    if(data != NULL)
    {
        newNode = (t_node*) xmalloc(sizeof(t_node));
        newNode->elem = data;
        newNode->next = node;
    }

    return newNode;
}
