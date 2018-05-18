#include "main.hh"

t_gl_env gl_env;

int main(int argc, char** argv)
{
    tree_node* rootDirectory;
    tree<tree_node>::iterator it;
    block* tmp;
    int i;
    string fileList, dirList, command;

    gl_env.blockSize = 0;
    gl_env.diskSize = 0;

    //Parse command line arguments
    for(i = 1; i < argc - 1; i++)
    {
        if(strcmp(argv[i], "-f") == 0)
        {
            dirList = argv[i + 1];
            fileList = argv[i + 2];
        }
        else if(strcmp(argv[i], "-s") == 0)
        {
            gl_env.diskSize = atoi(argv[i + 1]);
        }
        else if(strcmp(argv[i], "-b") == 0)
        {
            gl_env.blockSize = atoi(argv[i + 1]);
        }
    }

    if(!gl_env.blockSize || !gl_env.diskSize)
    {
        cout << "Block size or disk size arguments missing, using defaults..." << endl;
        gl_env.blockSize = 32;
        gl_env.diskSize = 512;
    }

    gl_env.numBlocks = floor(gl_env.diskSize / gl_env.blockSize);

    //Allocate blocks
    tmp = new block();
    tmp->lowerBound = 0;
    tmp->upperBound = gl_env.numBlocks - 1;
    tmp->used = false;

    gl_env.disk = new list<block>();
    gl_env.disk->push_front(*tmp);

    //Setup root directory and filesystem if desired
    rootDirectory = new tree_node();
    rootDirectory->name = "/";
    rootDirectory->size = 0;
    rootDirectory->timestamp = 0;
    rootDirectory->blockAddresses = NULL;

    gl_env.counter = 0;
    gl_env.filesystem.set_head(*rootDirectory);
    gl_env.workingDirectory = gl_env.filesystem.begin();

    if(!fileList.empty() && !dirList.empty())
    {
        setupFilesystem(dirList, fileList);
    }

    //Main command processing loop
    while(1)
    {
        renderWorkingDirectory();
        cout << ": ";
        getline(cin, command);

        if(!processCommand(command))
        {
            break;
        }
    }

    //Clear out the blockAddresses list
    for(it = gl_env.filesystem.begin(); it != gl_env.filesystem.end(); it++)
    {
        if(it->blockAddresses != NULL)
        {
            it->blockAddresses->clear();
        }
    }

    //Clear data structures
    gl_env.filesystem.clear();
    gl_env.disk->clear();

    cout << "Goodbye!" << endl;

    return 0;
}
