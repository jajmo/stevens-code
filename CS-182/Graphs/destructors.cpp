#include "myamgraph.hh"

/**
 * ~MyGraph()
 * MyGraph destructor
 */

template MyGraph<string>::~MyGraph();
template MyGraph<int>   ::~MyGraph();

template <class Elem>

MyGraph<Elem>::~MyGraph()
{
    delete [] vertices;
    delete [] visited;
}

/**
 * ~MyAmGraph()
 * MyAmGraph destructor
 */

template MyAmGraph<string>::~MyAmGraph();
template MyAmGraph<int>   ::~MyAmGraph();

template <class Elem>

MyAmGraph<Elem>::~MyAmGraph()
{
   	int i;

    for(i = 0; i < MyGraph<Elem>::cap; i++)
        delete [] am[i];

    delete [] am;
}
