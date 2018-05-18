#include "main.hh"

/**
 * Recursively increase the size of all parent nodes
 *
 * Precondition: it is not null
 * Postcondition: The parent sizes of it are all increased by size
 *
 * @param tree<tree_node>::iterator it The iterator pointing to the original node
 * @param int size The size to increase/decrease the nodes by
 */
void setParentSize(tree<tree_node>::iterator it, int size)
{
    (*it).size += size;

    if((*it).name == "/")
    {
        return;
    }
    else
    {
        setParentSize(--it, size);
    }
}
