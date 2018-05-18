#include "mylist.h"

/*
 * add_elem()
 *
 * Creates a new node and adds it to the beginning of the list
 *
 * Precondition: data and head are both not null
 * Postcondition: A new node is allocated and added to the front of the list
 * containing data
 *
 * @param data - The data to put inside the node
 * @param head - The head of the list
 */
void add_elem(void* data, t_node** head)
{
    t_node* newNode;

    if(data != NULL && head != NULL)
    {
        newNode = new_node(data, NULL);
        add_node(newNode, head);
    }
}
