#include "main.hh"

/**
 * Replace pages based on the clock algorithm
 *
 * Precondition: The page table is setup and initialized
 * Postcondition: Page replacement on the parameter is ran with the clock algorithm
 *
 * @param Process* p A reference to the containing process
 * @param int page The ID of the page to be put in memory
 * @param bool prePaging If pre paging is enabled or not
 */
void PageReplacement::clock(Process* p, int page, bool prePaging)
{
    Page* tmp;
    Page* newPage;
    int nextPageNum;
    int count;
    int size;

    for ( ; ; p->incrementIterator())
    {
        if (p->getIterator() == p->getEndIterator())
        {
            p->resetIterator();
        }

        tmp = *(p->getIterator());

        //1. Find the first invalid page
        if (!tmp->getValid())
        {
            //2. When we find an invalid page, swap it with the desired page
            //If R = 0, replace the page
            p->swapPages(tmp->getNum(), page);
            break;
        }
        else
        {
            //1a. If a valid page is found, set its R bit to 0
            tmp->setValid(0);
        }
    }

    if (prePaging)
    {
        //If we have pre paging, get rid of another page
        if (!p->getPagesRemaining())
        {
            //If we don't have pages remaining, figure out which page we need to insert 
            size = p->getSize();
            for (count = 0; count < size; count++)
            {
                newPage = p->getPage(count);
                if (newPage->getNum() > page && !p->isInMemory(newPage->getNum())) //We only want pages after the current page
                {
                    nextPageNum = newPage->getNum();
                    break;
                }
            }
        }

        for ( ; ; p->incrementIterator())
        {
            if (p->getIterator() == p->getEndIterator())
            {
                p->resetIterator();
            }

            tmp = *(p->getIterator());
            if (tmp->getValid() == 0)
            {
                if (!p->getPagesRemaining())
                {
                    p->swapPages(tmp->getNum(), nextPageNum);
                }
                else
                {
                    p->swapPages(-1, nextPageNum);
                }
                break;
            }
            else
            {
                tmp->setValid(0);
            }
        }
    }
}
