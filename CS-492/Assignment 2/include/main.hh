#ifndef _MAIN_HH_
#define _MAIN_HH_

#include <algorithm>
#include <climits>
#include <fstream>
#include <iostream>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <vector>

#define MEMORY_LOCATIONS 512

typedef struct s_gl_env
{
	bool prePaging;
	int algorithm; //1 for FIFO, 2 for LRU, 3 for Clock
	int pageNum; //The page number counter
	int pageSize;
	std::vector<int> mainMemory;
	unsigned long counter;
} t_gl_env;

extern t_gl_env gl_env;

std::vector<std::string> split(const std::string&, char);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
int getIndex(int val);

class Page
{
	private:
		int num;
		int valid;
		unsigned long accessTime;	

	public:
		Page(int num);
		int getNum();
		int getValid();
		unsigned long getTimestamp();
		void updateTimestamp();
		void setValid(int valid);
};

class Process
{
	private:
		std::vector<Page*> pageTable;
		std::vector<Page*> loadedPages;
		int id;
		int size;
		int pagesRemaining;
		std::vector<Page*>::iterator pageIterator;

	public:
		Process(int id, int size);
		int loadPages(int num);
		Page* getPage(int page);
		int getSize();
		int getPagesRemaining();
		void setPagesRemaining(int pages);

		//These functions are all used for clock
		std::vector<Page*>::iterator getIterator();
		std::vector<Page*>::iterator getEndIterator();
		void resetIterator();
		void incrementIterator();
		void swapPages(int p1, int p2);
		bool isInMemory(int pg);
};

class PageReplacement
{
	public:
		static void fifo(Process* p, int page, bool prePaging);
		static void lru(Process* p, Page* page, bool prePaging);
		static void clock(Process* p, int page, bool prePaging);
};

#endif