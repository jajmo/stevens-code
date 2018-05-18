#include "main.hh"

/**
 * Get the size of the page table
 *
 * Precondition: The process has been created
 * Postcondition: The size of the page table is returned
 *
 * @return int The size of the page table
 */
int Process::getSize()
{
    return this->size;
}