#include "main.hh"

/**
 * Check if a page is currently loaded in memory
 *
 * Precondition: The process is created
 * Postcondition: If the process is in memory, true is created. Else false.
 *
 * @param int pg The page ID to search for
 * @return bool If the page is in memory or not
 */
bool Process::isInMemory(int pg)
{
    unsigned int count;
    Page* page;
    std::vector<Page*>::iterator it;

    for (count = 0; count < this->pageTable.size(); count++)
    {
        if (this->pageTable.at(count)->getNum() == pg)
        {
            page = this->pageTable.at(count);
            break;
        }
    }

    it = std::find(this->loadedPages.begin(), this->loadedPages.end(), page);

    return it != this->loadedPages.end();
}