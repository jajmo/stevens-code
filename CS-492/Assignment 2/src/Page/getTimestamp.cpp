#include "main.hh"

/**
 * Get the timestamp of a page
 *
 * Precondition: The page has been created
 * Postcondition: The timestamp is returned
 *
 * @return unsigned long The timestamp
 */
unsigned long Page::getTimestamp()
{
    return this->accessTime;
}