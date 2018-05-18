#include "main.hh"

/**
 * Merge blocks of the disk
 *
 * Precondition: None
 * Postcondition: Blocks next to each other of the same state are merged
 */
void mergeBlocks()
{
    list<block>::iterator blockPos, nextBlock;
    block* tmp;

    blockPos = gl_env.disk->begin();
    nextBlock = gl_env.disk->begin();
    advance(nextBlock, 1);

    while(blockPos != gl_env.disk->end())
    {
        if(blockPos->used == nextBlock->used)
        {
            //Merge the blocks
            tmp = new block();
            tmp->lowerBound = blockPos->lowerBound;
            tmp->upperBound = nextBlock->upperBound;
            tmp->used = blockPos->used;

            gl_env.disk->insert(blockPos, *tmp);

            nextBlock = gl_env.disk->erase(nextBlock);
            blockPos = gl_env.disk->erase(blockPos);
            --blockPos; //Decrement to ensure the next block is correctly checked
        }
        else
        {
            //Otherwise, increment the next block and block iterators
            advance(blockPos, 1);
            advance(nextBlock, 1);
        }
    }
}
