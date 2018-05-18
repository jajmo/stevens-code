#include "main.hh"

/**
 * Print the directory tree in BFS order
 *
 * Precondition: None
 * Postcondition: The directory tree is printed in BFS order
 *
 * @param unsigned int level The current level. Used internally
 * @param tree<tree_node>::breadth_first_queued_iterator dir The current directory
 */
void printDirs()
{
    tree<tree_node>::breadth_first_queued_iterator it;

    it = gl_env.filesystem.begin_breadth_first();

    while(it != gl_env.filesystem.end_breadth_first())
    {
        cout << it->name;
        if(it->blockAddresses == NULL && it->name != "/")
        {
            cout << "/";
        }
        cout << endl;
        ++it;
    }
}
