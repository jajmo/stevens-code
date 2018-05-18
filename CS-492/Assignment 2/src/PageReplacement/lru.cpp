#include "main.hh"

/**
 * Replace a page using the LRU algorithm
 *
 * Precondition: The page table has been setup and is filled appropriately
 * Postcondition: 1 (or 2) pages are replaced, depending on the prePaging parameter
 *
 * @param Process* p A reference to the process in question
 * @param Page* page The page to be swapped out of memory
 * @param bool prePaging If pre paging is enabled or not
 */
void PageReplacement::lru(Process* p, Page* page, bool prePaging)
{
    int counter;
    unsigned long minUpdateTime;
    int minUpdateTimePageId;
    Page* pageTemp;

    minUpdateTime = ULONG_MAX;

    //1. Find the page that is in the page ID range of the process, and that has the smallest timestamp
    //Note: minUpdateTimePageId is local to process p
    for (counter = 0; counter < p->getSize(); counter++)
    {
        pageTemp = p->getPage(counter);
        if (pageTemp->getValid() && pageTemp->getTimestamp() < minUpdateTime)
        {
            minUpdateTime = pageTemp->getTimestamp();
            minUpdateTimePageId = counter;
        }
    }

    //2. Unload that page and load the new page, setting valid bits accordingly
    p->getPage(minUpdateTimePageId)->setValid(0);
    gl_env.mainMemory.erase(gl_env.mainMemory.begin() + getIndex(p->getPage(minUpdateTimePageId)->getNum()));

    gl_env.mainMemory.push_back(page->getNum());
    page->setValid(1);
    page->updateTimestamp();

    //3. Handle pre paging, if necessary
    if (prePaging)
    {
        if (p->getPagesRemaining() == 0)
        {
            minUpdateTime = ULONG_MAX;
            for (counter = 0; counter < p->getSize(); counter++)
            {
                pageTemp = p->getPage(counter);
                if (pageTemp->getValid() && pageTemp->getTimestamp() < minUpdateTime) 
                {
                    minUpdateTime = pageTemp->getTimestamp();
                    minUpdateTimePageId = counter;
                }
            }
            p->getPage(minUpdateTimePageId)->setValid(0);
            p->getPage(minUpdateTimePageId)->updateTimestamp();
            gl_env.mainMemory.erase(gl_env.mainMemory.begin() + getIndex(p->getPage(minUpdateTimePageId)->getNum()));
            p->setPagesRemaining(1);
        }
        
        for(counter = 0; counter < p->getSize(); counter++)
        {
            if(p->getPage(counter)->getNum() > page->getNum() && !p->getPage(counter)->getValid())
            {
                //Next invalid page is found, push it to memory
                gl_env.mainMemory.push_back(p->getPage(counter)->getNum());
                p->getPage(counter)->setValid(1);
                p->getPage(counter)->updateTimestamp();
                p->setPagesRemaining(p->getPagesRemaining() - 1);
                break;
            }
        }
    }
}