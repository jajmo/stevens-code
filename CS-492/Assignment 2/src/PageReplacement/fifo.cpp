#include "main.hh"

/**
 * Replace a page, using the FIFO algorithm
 *
 * Precondition: The program is running and all pages/page tables have been created
 * Postcondition: FIFO has been successfully ran, with pre or demand paging
 *
 * NOTE: By using the order of the vector, it eliminates the need to use a counter with FIFO.
 *
 * @param Process* p A reference to the process object that is involved with this pass of the algorithm
 * @param int page The page ID that is being inserted 
 * @param bool demand If we are using demand (true) or pre (false) paging
 */
void PageReplacement::fifo(Process* p, int page, bool prePaging)
{
    int count;
    int size;
    int minId;
    int maxId;
    int id;

    minId = p->getPage(0)->getNum();
    maxId = p->getPage(p->getSize())->getNum();
    size = gl_env.mainMemory.size(); //We store this in a variable to avoid calling size() size() times

    //1. Find the first index in the main memory vector that belongs to process P
    for(count = 0; count < size; count++)
    {
        id = gl_env.mainMemory.at(count);
        if(id >= minId && id <= maxId)
        {
            break;
        }
    }

    //2. Mark the found page as not in memory, and unload it
    gl_env.mainMemory.erase(gl_env.mainMemory.begin() + count);
    p->getPage(id - minId)->setValid(0);

    //3. Push the new page to main memory and mark it as valid
    gl_env.mainMemory.push_back(page);
    p->getPage(page - minId)->setValid(1);

    //4. Handle pre-paging, if necessary
    if (prePaging)
    {
        if(!p->getPagesRemaining())
        {
            for(count = 0; count < size; count++)
            {
                id = gl_env.mainMemory.at(count);
                if(id >= minId && id <= maxId)
                {
                    break;
                }
            }
            gl_env.mainMemory.erase(gl_env.mainMemory.begin() + count);
            p->getPage(id - minId)->setValid(0);
            p->setPagesRemaining(1);
        }

        for(count = 0; count < p->getSize(); count++)
        {
            if(p->getPage(count)->getNum() > page && !p->getPage(count)->getValid())
            {
                break;
            }
        }
        
        //4a. Next invalid page is found. Push it to main memory, mark it valid, and break
        gl_env.mainMemory.push_back(p->getPage(count)->getNum());
        p->getPage(count)->setValid(1);
        p->setPagesRemaining(p->getPagesRemaining() - 1);
    }
} 