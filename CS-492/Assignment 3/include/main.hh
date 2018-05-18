#ifndef _MAIN_HH_
#define _MAIN_HH_

#include "tree_util.hh"
#include <fstream>
#include <iostream>
#include <list>
#include <math.h>
#include <sstream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

using namespace std;

//A node in the filesystem
typedef struct s_tree_node {
    string name;
    unsigned int size;
    unsigned int timestamp;
    unsigned int fragmentation;
    list<int>* blockAddresses;
} tree_node;

//A disk block
typedef struct s_block {
    unsigned int lowerBound;
    unsigned int upperBound;
    bool used;
} block;

//Global structure
typedef struct s_gl_env {
    tree<tree_node> filesystem;
    tree<tree_node>::iterator workingDirectory;

    list<block>* disk;

    unsigned int counter;
    unsigned int diskSize;
    unsigned int blockSize;
    unsigned int numBlocks;
} t_gl_env;

extern t_gl_env gl_env;

bool allocateBlocks(unsigned int num, tree_node* file);
bool freeBlocks(unsigned int num, tree_node* file);
tree<tree_node>::iterator findNode(tree<tree_node>::iterator, string name);
void mergeBlocks();
void printDirs();
void printFiles();
bool processCommand(string command);
void renderWorkingDirectory();
void setupFilesystem(string dirList, string fileList);
void setParentSize(tree<tree_node>::iterator, int size);
std::vector<std::string> split(const std::string &s, char delim);
std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);

#endif
