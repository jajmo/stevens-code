#include "main.hh"

/**
 * Allocate blocks for a file
 *
 * Precondition: num > 0 and file is not null
 * Postcondition: num blocks are allocated, or false is returned
 *
 * @param unsigned int num The number of blocks to allocate
 * @param tree_node* file A pointer to the tree_node object representing the file
 * @return bool If all blocks were allocated or not
 */
bool allocateBlocks(unsigned int num, tree_node* file)
{
    list<block>::iterator blockIterator;
    block* tmp, tmp2;
    blockIterator = gl_env.disk->begin();
    unsigned int count;

    while(num > 0 && blockIterator != gl_env.disk->end())
    {
        if(blockIterator->used == false)
        {
            if(blockIterator->lowerBound == blockIterator->upperBound)
            {
                //Block of size 1
                blockIterator->used = true;
                file->blockAddresses->push_back(blockIterator->lowerBound);
                --num;
            }
            else
            {
                //Block of size > 1
                if((blockIterator->upperBound - blockIterator->lowerBound) < num)
                {
                    //If the file can use all of the blocks
                    blockIterator->used = true;
                    for(count = blockIterator->lowerBound; count <= blockIterator->upperBound; count++)
                    {
                        file->blockAddresses->push_back(count);
                    }

                    num -= (blockIterator->upperBound - blockIterator->lowerBound);
                }
                else
                {
                    tmp = new block();
                    tmp->lowerBound = blockIterator->lowerBound;
                    tmp->upperBound = blockIterator->lowerBound + num - 1;
                    tmp->used = true;

                    tmp2 = *blockIterator;
                    tmp2.lowerBound = tmp->upperBound + 1;

                    blockIterator = gl_env.disk->erase(blockIterator);
                    gl_env.disk->insert(blockIterator, *tmp);
                    gl_env.disk->insert(blockIterator, tmp2);

                    for(count = tmp->lowerBound; count <= tmp->upperBound; count++)
                    {
                        file->blockAddresses->push_back(count);
                    }

                    num = 0;
                    break;
                }
            }
        }

        ++blockIterator;
    }

    mergeBlocks();

    return (num == 0);
}
