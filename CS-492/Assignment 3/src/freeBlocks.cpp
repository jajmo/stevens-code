#include "main.hh"

/**
 * Free blocks for a program
 *
 * Precondition: file is not null, num > 0
 * Postcondition: num blocks are free, or false is returned
 *
 * @param unsigned int num The number of blocks to free
 * @param tree_node* file The file to free blocks for
 * @return bool If blocks were successfully freed
 */
bool freeBlocks(unsigned int num, tree_node* file)
{
    list<int>::iterator pos;
    list<block>::iterator diskpos;
    block* tmp;
    block* tmp1;
    block* tmp2;

    pos = file->blockAddresses->begin();

    while(pos != file->blockAddresses->end() && num > 0)
    {
        diskpos = gl_env.disk->begin();

        for( ; diskpos != gl_env.disk->end(); diskpos++)
        {
            if((unsigned int) *pos >= diskpos->lowerBound && (unsigned int) *pos <= diskpos->upperBound)
            {
                //Found the corresponding block
                break;
            }
        }

        if(diskpos->lowerBound == diskpos->upperBound)
        {
            //One block
            diskpos->used = false;
        }
        else
        {
            //Multiple blocks, only use the specified number
            tmp = new block();
            tmp1 = new block();
            tmp2 = new block();

            if((unsigned int) *pos == diskpos->lowerBound)
            {
                tmp->lowerBound = *pos;
                tmp->upperBound = *pos;
                tmp->used = false;

                tmp1->lowerBound = diskpos->lowerBound + 1;
                tmp1->upperBound = diskpos->upperBound;
                tmp1->used = true;

                gl_env.disk->insert(diskpos, *tmp);
                gl_env.disk->insert(diskpos, *tmp1);
            }
            else if((unsigned int) *pos == diskpos->upperBound)
            {
                tmp->lowerBound = *pos;
                tmp->upperBound = *pos;
                tmp->used = false;

                tmp1->lowerBound = diskpos->lowerBound;
                tmp1->upperBound = diskpos->upperBound - 1;
                tmp1->used = true;

                gl_env.disk->insert(diskpos, *tmp);
                gl_env.disk->insert(diskpos, *tmp1);
            }
            else
            {
                tmp->lowerBound = diskpos->lowerBound;
                tmp->upperBound = *pos - 1;
                tmp->used = true;

                tmp1->lowerBound = *pos;
                tmp1->upperBound = *pos;
                tmp1->used = false;

                tmp2->lowerBound = *pos + 1;
                tmp2->upperBound = diskpos->upperBound;
                tmp2->used = true;

                gl_env.disk->insert(diskpos, *tmp);
                gl_env.disk->insert(diskpos, *tmp1);
                gl_env.disk->insert(diskpos, *tmp2);
            }

            gl_env.disk->erase(diskpos);
        }

        pos = file->blockAddresses->erase(pos);
        --num;
    }

    mergeBlocks();
    return (num == 0);
}
