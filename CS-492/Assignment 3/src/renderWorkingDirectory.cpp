#include "main.hh"

/**
 * Render the working directory
 *
 * Precondition: None
 * Postcondition: The working directory is printed
 */
void renderWorkingDirectory()
{
    tree<tree_node>::iterator dir;
    vector<string> workingDir;
    unsigned int i;

    dir = gl_env.workingDirectory;

    while(dir != gl_env.filesystem.begin())
    {
        workingDir.insert(workingDir.begin(), (*dir).name);
        dir = gl_env.filesystem.parent(dir);
    }

    cout << "/";
    
    for(i = 0; i < workingDir.size(); i++)
    {
        cout << workingDir.at(i) << "/";
    }

    workingDir.clear();
}
