#include "main.hh"

/**
 * Get the valid bit of the page
 *
 * Precondition: The page has been created
 * Postcondition: The valid bit is returned
 *
 * @return int The valid bit of the page
 */
int Page::getValid()
{
    return this->valid;
}