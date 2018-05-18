#include "main.hh"

t_gl_env gl_env;

/**
 * The main method of the program
 * Handles processing files, parsing the file input strings, calling methods, etc.
 * All of the gruntwork is handled by the page replacement algorithms and methods
 * of the processes class.
 *
 * @param int argc The number of command line arguments
 * @param char** argv The vector of command line arguments
 * @return int the exit status
 */
int main(int argc, char** argv)
{
    std::string ptraceFile;
    std::string plistFile;
    unsigned int pageSize;
    int processCount;
    int count;
    int page;
    int pagefault;
    Page* foundPage;
    std::string pageReplacement;
    std::string prePaging;
    std::string line;
    std::ifstream file;
    std::vector<Process*> processes;
    std::vector<std::string> tokens;
    std::vector<int>::iterator it;

    if (argc != 6)
    {
        std::cout << "Invalid number of command line parameters!" << std::endl;
        return 1;
    }

    plistFile       = argv[1];
    ptraceFile      = argv[2];
    pageSize        = atoi(argv[3]);
    pageReplacement = argv[4];
    prePaging       = argv[5];

    if (ptraceFile.empty() || plistFile.empty() || pageSize == 0 || pageReplacement.empty() || prePaging.empty())
    {
        std::cout << "Invalid command line arguments!" << std::endl;
        return 1;
    }

    if (prePaging.compare("+") == 0)
    {
        gl_env.prePaging = true;
    }
    else
    {
        gl_env.prePaging = false;
    }

    if (pageReplacement.compare("FIFO") == 0)
    {
        gl_env.algorithm = 1;
    }
    else if (pageReplacement.compare("LRU") == 0)
    {
        gl_env.algorithm = 2;
    }
    else
    {
        gl_env.algorithm = 3;
    }

    gl_env.pageNum = 0;
    gl_env.pageSize = pageSize;

    file.open(plistFile.c_str());

    //Setup processes
    processCount = 0;
    if (file.is_open())
    {
        while (getline(file, line))
        {
            tokens = split(line, ' ');
            processes.push_back(new Process(atoi(tokens.front().c_str()), (int) ceil((double) atoi(tokens.back().c_str()) / pageSize)));
            processCount++;
        }
    }
    else
    {
        std::cout << "Could not open file " << plistFile << "!" << std::endl;
    }
    file.close();

    //Setup process page tables
    pagefault = 0;
    for (count = 0; count  < processCount; count++)
    {
        pagefault += processes.at(count)->loadPages((int) ceil((double) (MEMORY_LOCATIONS / pageSize) / processCount));
    }
    file.open(ptraceFile.c_str());
    gl_env.counter = 0;

    if (file.is_open())
    {
        while (getline(file, line))
        {
            tokens = split(line, ' ');
            page = (int) floor((double) atoi(tokens.back().c_str()) / pageSize);
            foundPage = processes.at(atoi(tokens.front().c_str()))->getPage(page);

            if(gl_env.algorithm != 3)
            {
                it = std::find(gl_env.mainMemory.begin(), gl_env.mainMemory.end(), foundPage->getNum());

                //Check for page fault, and choose appropriate algorithm
                if (it == gl_env.mainMemory.end())
                {
                    pagefault++;
                    if (gl_env.algorithm == 1)
                    {
                        PageReplacement::fifo(processes.at(atoi(tokens.front().c_str())), foundPage->getNum(), gl_env.prePaging);
                    }
                    else if (gl_env.algorithm == 2)
                    {
                        PageReplacement::lru(processes.at(atoi(tokens.front().c_str())), foundPage, gl_env.prePaging); 
                    }
                }
                else
                {
                    foundPage->updateTimestamp();
                }
            }
            else
            {
                if(!processes.at(atoi(tokens.front().c_str()))->isInMemory(foundPage->getNum()))
                {
                    pagefault++;
                    PageReplacement::clock(processes.at(atoi(tokens.front().c_str())), foundPage->getNum(), gl_env.prePaging); 
                }
                else
                {
                    foundPage->setValid(1);
                }
            }
        }
        std::cout << pagefault << " page faults" << std::endl;
    }
    else
    {
        std::cout << "Could not open file " << ptraceFile << "!" << std::endl;
        return 1;
    }

    gl_env.mainMemory.clear();
    return 0;
}