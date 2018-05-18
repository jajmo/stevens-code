#include "main.hh"

/**
 * Update the timestamp of a page
 *
 * Precondition: The page has been created
 * Postcondition: The timestamp is updated
 */
void Page::updateTimestamp()
{
    this->accessTime = gl_env.counter++;
}