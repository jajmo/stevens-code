#include "main.hh"

/**
 * Swap a page in and out of memory
 * This is used by clock
 *
 * Precondition: The process is running and the index exists in the vector
 * Postcondition: The page is removed, and the new page is added
 *
 * @param int p1 The page ID to remove
 * @param int p2 The page ID to add
 */
void Process::swapPages(int p1, int p2)
{
    unsigned int count;
    unsigned int size;
    Page* page1;

    if (p1 > -1)
    {
        for (count = 0; count < this->loadedPages.size(); count++)
        {
            if (this->loadedPages.at(count)->getNum() == p1)
            {
                this->loadedPages.erase(this->loadedPages.begin() + count);
                this->pagesRemaining++;
                break;
            }
        }
    }

    size = this->pageTable.size();
    for (count = 0; count < size; count++)
    {
        page1 = this->pageTable.at(count);
        if (page1->getNum() == p2)
        {
            break;
        }
    }

    page1->setValid(1);
    this->loadedPages.insert(this->pageIterator, page1);
    this->pagesRemaining--;
}