#include "main.hh"

/**
 * Get the page table iterator. Used only for clock page replacement
 *
 * Precondition: The process has been created
 * Postcondition: The iterator is returned
 *
 * @return std::vector<Page*>::iterator The iterator
 */
std::vector<Page*>::iterator Process::getIterator()
{
    return this->pageIterator;
}