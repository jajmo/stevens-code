#include "main.hh"

/**
 * Print files and allocated blocks
 *
 * Precondition: None
 * Postcondition: File information is printed
 */
void printFiles()
{
    tree<tree_node>::iterator it;
    list<int>::const_iterator blocks;

    it = gl_env.filesystem.begin();

    while(it != gl_env.filesystem.end())
    {
        if(it->blockAddresses != NULL)
        {
            cout << (*it).name << ": ";
            blocks = it->blockAddresses->begin();

            while(blocks != it->blockAddresses->end())
            {
                cout << *blocks << " ";
                advance(blocks, 1);
            }

            cout << endl;
        }

        ++it;
    }
}
