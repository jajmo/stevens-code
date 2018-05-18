#include "main.hh"

/**
 * Find a node in the tree, given an iterator pointing to the starting position of the search
 * NOTE: This only traverses the children of the iterator
 *
 * Precondition: The filesystem is not null
 * Postcondition: An iterator is returned pointing to the found dir, otherwise null
 *
 * @param tree<tree_node>::iterator pos The starting position iterator
 * @param string name The node name to search for
 * @return tree<tree_node>::iterator|null An iterator pointing to the found node, or null if not found
 */
tree<tree_node>::iterator findNode(tree<tree_node>::iterator pos, string name)
{
    tree<tree_node>::sibling_iterator it;

    it = gl_env.filesystem.begin(pos);

    while(it != gl_env.filesystem.end(pos))
    {
        if((*it).name == name)
        {
            return it;
        }

        it++;
    }

    return NULL;
}
