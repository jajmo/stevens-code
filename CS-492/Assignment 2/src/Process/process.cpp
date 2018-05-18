#include "main.hh"

/**
 * Create a new process
 *
 * Precondition: None
 * Postcondition: A new process is created
 *
 * @param int id The process ID
 * @param int mem The page table size
 */
Process::Process(int id, int size)
{
    int count;
    this->id = id;
    this->size = size;
    for (count = 0; count <= size; count++)
    {
        this->pageTable.push_back(new Page(++gl_env.pageNum));
    }
    this->pageIterator = this->pageTable.begin();
}