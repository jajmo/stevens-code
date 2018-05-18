#include "main.hh"

/**
 * Process a command. This function is essentially the core of the program
 *
 * Precondition: None
 * Postcondition: The command is ran
 *
 * @param string command The command to execute
 * @return bool If the program should terminate or not
 */
bool processCommand(string command)
{
    tree<tree_node>::sibling_iterator it;
    tree<tree_node>::iterator fragIterator;
    vector<string> tokens;
    vector<string>::iterator tokenLocation;
    list<block>::iterator diskIterator;
    tree_node* tmp;
    int fragmentation;

    if(command.empty() || command.find_first_not_of(' ') == std::string::npos)
    {
        return true;
    }

    tokens = split(command, ' ');

    if(tokens.front() == "cd")
    {
        if(tokens.size() > 1)
        {
            tokens = split(tokens.at(1), '/');
            tokenLocation = tokens.begin();
            it = gl_env.workingDirectory;

            while(tokenLocation != tokens.end())
            {
                if(*tokenLocation == "..")
                {
                    if(it != gl_env.filesystem.begin())
                    {
                        it = gl_env.filesystem.parent(it);
                    }
                }
                else
                {
                    it = findNode(it, *tokenLocation);

                    if(it == NULL)
                    {
                        cout << "Directory " << *tokenLocation << " not found" << endl;
                        break;
                    }
                    else if((*it).blockAddresses != NULL)
                    {
                        cout << "Can't cd to " << *tokenLocation << ": It's a file" << endl;
                        it = NULL;
                        break;
                    }
                }

                tokenLocation++;
            }

            if(it != NULL)
            {
                gl_env.workingDirectory = it;
            }
        }
        else
        {
            cout << "Invalid arguments to `cd`" << endl;
        }
    }
    else if(tokens.front() == "cd..")
    {
        processCommand("cd ../");
    }
    else if(tokens.front() == "ls")
    {
        it = gl_env.filesystem.begin(gl_env.workingDirectory);
        while(it != gl_env.filesystem.end(gl_env.workingDirectory))
        {
            if((*it).blockAddresses != NULL)
            {
                cout << (*it).name << " ";
            }
            else
            {
                cout << (*it).name << "/ ";
            }
            it++;
        }
        cout << endl;
    }
    else if(tokens.front() == "mkdir")
    {
        if(tokens.size() < 2)
        {
            cout << "Invalid arguments for `mkdir`" << endl;
        }
        else
        {
            it = findNode(gl_env.workingDirectory, tokens.at(1));

            if(it == NULL)
            {
                tmp = new tree_node();
                tmp->size = 0;
                tmp->name = tokens.at(1);
                tmp->timestamp = gl_env.counter++;

                gl_env.filesystem.append_child(gl_env.workingDirectory, *tmp);
            }
            else
            {
                cout << "Cannot create directory " << tokens.at(1) << ": File exists" << endl;
            }
        }
    }
    else if(tokens.front() == "create")
    {
        if(tokens.size() == 1)
        {
            cout << "Invalid arguments for `create`" << endl;
        }
        else
        {
            tmp = new tree_node();
            tmp->size = 0;
            tmp->name = tokens.at(1);
            tmp->blockAddresses = new list<int>();
            tmp->timestamp = gl_env.counter++;

            gl_env.filesystem.append_child(gl_env.workingDirectory, *tmp);
        }
    }
    else if(tokens.front() == "append")
    {
        if(tokens.size() < 3)
        {
            cout << "Invalid arguments for `append`" << endl;
        }
        else
        {
            it = findNode(gl_env.workingDirectory, tokens.at(1));
            if(it == NULL)
            {
                cout << "Cannot find file " << tokens.at(1) << endl;
            }
            else if((*gl_env.filesystem.begin()).size + atoi(tokens.at(2).c_str()) > gl_env.diskSize)
            {
                cout << "Cannot append " << tokens.at(2) << " bytes: disk full" << endl;
            }
            else if((*it).blockAddresses == NULL)
            {
                cout << "Cannot append to " << tokens.at(1) << ": it is a directory" << endl;
            }
            else
            {
                allocateBlocks(atoi(tokens.at(2).c_str()) / gl_env.blockSize, &(*it));
                it->timestamp = gl_env.counter++;
                it->fragmentation = 32 - ((it->size + atoi(tokens.at(2).c_str())) % gl_env.blockSize);
                setParentSize(it, atoi(tokens.at(2).c_str()));
            }
        }
    }
    else if(tokens.front() == "remove")
    {
        if(tokens.size() < 3)
        {
            cout << "Invalid arguments for `remove`" << endl;
        }
        else
        {
            it = findNode(gl_env.workingDirectory, tokens.at(1));
            if(it == NULL)
            {
                cout << "Cannot find file " << tokens.at(1) << endl;
            }
            else if((*it).blockAddresses == NULL)
            {
                cout << "Cannot remove from " << tokens.at(1) << ": it is a directory" << endl;
            }
            else
            {
                if((*it).size < (unsigned int) atoi(tokens.at(2).c_str()))
                {
                    cout << "Cannot remove " << tokens.at(2) << " bytes from file: its size is " << (*it).size << endl;
                }
                else
                {
                    freeBlocks(atoi(tokens.at(2).c_str()) / gl_env.blockSize, &(*it));
                    it->timestamp = gl_env.counter++;
                    it->fragmentation = 32 - ((it->size - atoi(tokens.at(2).c_str())) % gl_env.blockSize);
                    setParentSize(it, atoi(tokens.at(2).c_str()) * -1);
                }
            }
        }
    }
    else if(tokens.front() == "delete")
    {
        if(tokens.size() < 2)
        {
            cout << "Invalid arguments for `delete`" << endl;
        }
        else
        {
            it = findNode(gl_env.workingDirectory, tokens.at(1));

            if(it != NULL)
            {
                if((*it).blockAddresses == NULL)
                {
                    if(gl_env.filesystem.number_of_children(it) > 0)
                    {
                        cout << "Cannot delete " << (*it).name << ": Directory not empty" << endl;
                    }
                    else
                    {
                        gl_env.filesystem.erase(it);
                    }
                }
                else
                {
                    freeBlocks((*it).size / gl_env.blockSize, &(*it));
                    setParentSize(it, (*it).size * -1);
                    gl_env.filesystem.parent(it)->timestamp = gl_env.counter++;
                    gl_env.filesystem.erase(it);
                }
            }
            else
            {
                cout << tokens.at(1) << ": Directory/File not found" << endl;
            }
        }
    }
    else if(tokens.front() == "exit")
    {
        return false;
    }
    else if(tokens.front() == "dir")
    {
        printDirs();
    }
    else if(tokens.front() == "prfiles")
    {
        printFiles();
    }
    else if(tokens.front() == "prdisk")
    {
        diskIterator = gl_env.disk->begin();
        fragIterator = gl_env.filesystem.begin();
        fragmentation = 0;

        while(diskIterator != gl_env.disk->end())
        {
            if((*diskIterator).used)
            {
                cout << "In use: ";
            }
            else
            {
                cout << "Free: ";
            }

            if(diskIterator->lowerBound != diskIterator->upperBound)
            {
                cout << (*diskIterator).lowerBound << "-" << (*diskIterator).upperBound;
            }
            else
            {
                cout << diskIterator->lowerBound;
            }
            cout << endl;
            advance(diskIterator, 1);
        }

        while(fragIterator != gl_env.filesystem.end())
        {
            fragmentation += fragIterator->fragmentation;
            advance(fragIterator, 1);
        }

        cout << "Fragmentation: " << fragmentation << " bytes" << endl;
    }
    else
    {
        cout << "Invalid command: " << command << endl;
    }

    return true;
}
