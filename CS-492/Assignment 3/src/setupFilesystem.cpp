#include "main.hh"

/**
 * Setup the directory tree and filesystem
 *
 * Precondition: dirList and fileList are not empty
 * Postcondition: The filesystem is setup
 *
 * @param string dirList The filename containing the list of directories
 * @param string fileList The filename containing the list of files
 */
void setupFilesystem(string dirList, string fileList)
{
    ostringstream output;
    string line;
    tree_node* node;
    unsigned int size, numBlocks;
    vector<string> tokens;
    vector<string>::iterator tokenParser;
    tree<tree_node>::iterator it;

    ifstream directories(dirList.c_str());
    ifstream files(fileList.c_str());

    //First handle directories
    while(getline(directories, line))
    {
        it = gl_env.filesystem.begin();

        tokens = split(line, '/');
        tokenParser = tokens.begin();

        while(tokenParser != tokens.end())
        {
            if(strcmp((*tokenParser).c_str(), ".") != 0)
            {
                if(tokenParser + 1 == tokens.end())
                {
                    //At the bottom, the directory needs to be created
                    node = new tree_node();
                    node->name = *tokenParser;
                    node->timestamp = ++gl_env.counter;
                    node->size = 0;
                    node->blockAddresses = NULL;

                    gl_env.filesystem.append_child(it, *node);
                }
                else
                {
                    it = findNode(it, (*tokenParser));

                    if(it == NULL)
                    {
                        cerr << "An error occured" << endl;
                        exit(1);
                    }
                }
            }

            ++tokenParser;
        }
    }

    //Next do files
    while(getline(files, line))
    {
        it = gl_env.filesystem.begin();

        tokens = split(line, ' ');
        size = atoi(tokens.back().c_str());
        tokens = split(tokens.front(), '/');
        tokenParser = tokens.begin();

        while(tokenParser != tokens.end())
        {
            if(strcmp((*tokenParser).c_str(), ".") != 0)
            {
                if(tokenParser + 1 == tokens.end())
                {
                    node = new tree_node();
                    node->name = *tokenParser;
                    node->timestamp = ++gl_env.counter;
                    node->size = size;
                    node->blockAddresses = new list<int>();
                    node->fragmentation = 32 - (size % gl_env.blockSize);
                    numBlocks = node->size / gl_env.blockSize;
                    if(numBlocks == 0 && node->size > 0)
                    {
                        numBlocks = 1;
                    }
                    if(!allocateBlocks(numBlocks, node))
                    {
                        cerr << "Unable to allocate blocks, disk full" << endl;
                        exit(1);
                    }

                    gl_env.filesystem.append_child(it, *node);
                    setParentSize(it, size);
                }
                else
                {
                    it = findNode(it, *tokenParser);

                    if(it == NULL)
                    {
                        cerr << "Unknown directory: " << *tokenParser << endl;
                        exit(1);
                    }
                }
            }

            ++tokenParser;
        }
    }
}
