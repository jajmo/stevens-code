#include "main.hh"

/**
 * Create a new page table entry
 *
 * Precondition: None
 * Postcondition: The page is created
 *
 * @param int id The page ID
 */
Page::Page(int num)
{
    this->num = num;
    this->valid = 0;
    this->accessTime = 0;
}