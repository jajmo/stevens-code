#include "main.hh"

/**
 * Get the iterator for the end of the loaded pages vector
 * This is only used for the clock algorithm
 *
 * Precondition: The process has been created, and the loaded pages is not empty
 * Postcondition: The end iterator is returned
 *
 * @return std::vector<Page*>::iterator The iterator that points to the end of the vector
 */
std::vector<Page*>::iterator Process::getEndIterator()
{
    return this->loadedPages.end();
}