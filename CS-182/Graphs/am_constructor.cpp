#include "myamgraph.hh"

/**
 * MyAmGraph()
 * AmGraph Constructor
 *
 * Parameter cap - the capacity of the graph
 * Parameter dir - true if directed, false if undirected
 */

template MyAmGraph<string>::MyAmGraph(unsigned int, bool);
template MyAmGraph<int>   ::MyAmGraph(unsigned int, bool);

template <class Elem>

MyAmGraph<Elem>::MyAmGraph(unsigned int cap, bool dir) : MyGraph<Elem>::MyGraph(cap, dir)
{
    int i, j, k;

    //Create adjacency matrix
    if(!dir)
        am = new int*[cap - 1];
    else
        am = new int*[cap];

    //Create adjacency matrix sub arrays
    for(i = 0; i < cap; i++)
    {
        if(!dir)
            am[i] = new int[cap - i - 1];
        else
            am[i] = new int[cap];
    }

    //Set am to -1
    for(j = 0; j < cap; j++)
    {
        if(!dir)
            for(k = 0; k < cap - j; k++)
                am[j][k] = -1;
        else
            for(k = 0; k < cap; k++)
                am[j][k] = -1;
    }
}
