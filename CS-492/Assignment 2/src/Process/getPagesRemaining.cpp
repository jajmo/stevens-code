#include "main.hh"

/**
 * Get the pages remaining
 *
 * Precondition: The process is created and pages have been loaded
 * Postcondition: Pages remaining is returned
 *
 * @return int The number of pages remaining
 */
int Process::getPagesRemaining()
{
    return this->pagesRemaining;
}