#include "main.hh"

/**
 * Set the valid bit of a page
 *
 * Precondition: The page is created
 * Postcondition: The valid bit is updated
 *
 * @param int valid The new valid bit
 */
void Page::setValid(int valid)
{
    this->valid = valid;
}