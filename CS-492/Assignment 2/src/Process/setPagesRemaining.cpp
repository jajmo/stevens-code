#include "main.hh"

/**
 * Set the number of pages remaining
 *
 * Precondition: The process has been created
 * Postcondition: The number of remaining pages is updated
 *
 * @param int pages The number of remaining pages
 */
void Process::setPagesRemaining(int pages)
{
    this->pagesRemaining = pages;
}