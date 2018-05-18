#include "main.hh"

/**
 * Reset the iterator to the beginning
 *
 * Precondition: The process exists
 * Postcondition: The iterator is reset to the beginning of the vector
 */
void Process::resetIterator()
{
    this->pageIterator = this->loadedPages.begin();
}