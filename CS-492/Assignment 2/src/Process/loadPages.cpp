#include "main.hh"

/**
 * Load a set of pages into memory
 *
 * Precondition: The process is created
 * Postcondition: The required number of pages are loaded
 *
 * @param int num The number of pages to load
 * @return int the number of page faults
 */
int Process::loadPages(int num)
{
    int count;
    int faults;
    this->pagesRemaining = num;
    for(count = 0, faults = 0; count < this->size && this->pagesRemaining; count++)
    {
        Page* page = this->pageTable.at(count);
        page->setValid(1);
        if(gl_env.algorithm < 3)
        {
            gl_env.mainMemory.push_back(page->getNum());
        }
        else
        {
            this->loadedPages.push_back(page);
        }
        this->pagesRemaining--;
        faults++;
    }    
    if(gl_env.algorithm == 3)
    {
        this->pageIterator = this->loadedPages.begin();
    }

    return faults;
}