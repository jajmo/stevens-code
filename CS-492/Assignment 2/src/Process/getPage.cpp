#include "main.hh"

/**
 * Get a page, given a memory location
 *
 * Precondition: The page table is populated
 * Postcondition: The found page is returned
 *
 * @param int page The memory location
 * @return Page* A reference to the found page
 */
 Page* Process::getPage(int page)
 {
     return this->pageTable.at(page);
 }