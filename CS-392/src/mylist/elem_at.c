#include "mylist.h"

/*
 * elem_at()
 *
 * Returns the elem at num position in the list
 *
 * Precondition: num <= length(list)
 * Postcondition: The element at position num is returned
 *
 * @param head - The head of the list
 * @param num - The index of the data to return
 * @return void* - The data from the node
 */
void* elem_at(t_node* head, unsigned int num)
{
    void* returnElem = NULL;
    t_node* counter;

    if(head != NULL)
    {
        counter = head;

        for( ; num > 0 && counter->next != NULL; counter = counter->next, num--)
            ;

        returnElem = counter->elem;
    }

    return returnElem;
}
