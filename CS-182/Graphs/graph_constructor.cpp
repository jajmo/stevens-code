#include "mygraphs.hh"

/**
 * MyGraph()
 * Default constructor for MyGraph
 */

template MyGraph<string>::MyGraph();
template MyGraph<int>   ::MyGraph();

template <class Elem>

MyGraph<Elem>::MyGraph()
{
    vertices = new Elem[15];
    directed = false;
    v        = 0;
    e        = 0;
    cap      = 15;
    visited  = new bool[15];
}

/**
 * MyGraph()
 * Constructor for MyGraph
 *
 * Parameter dir - true for directed, false for undirected
 */

template MyGraph<string>::MyGraph(bool);
template MyGraph<int>   ::MyGraph(bool);

template <class Elem>

MyGraph<Elem>::MyGraph(bool dir)
{
    vertices = new Elem[15];
    directed = dir;
    v        = 0;
    e        = 0;
    cap      = 15;
    visited  = new bool[15];
}

/**
 * MyGraph()
 * Constructor for MyGraph
 *
 * Parameter cap - The capacity of the graph
 * Parameter dir - true for directed, false for undirected
 */

template MyGraph<string>::MyGraph(unsigned int, bool);
template MyGraph<int>   ::MyGraph(unsigned int, bool);

template <class Elem>

MyGraph<Elem>::MyGraph(unsigned int cap, bool dir)
{
    vertices  = new Elem[cap];
    directed  = dir;
    v         = 0;
    e         = 0;
    this->cap = cap;
    visited   = new bool[cap];
}

/**
 * MyGraph()
 * Constructor for MyGraph
 *
 * Parameter cap - The capacity of the graph
 */

template MyGraph<string>::MyGraph(unsigned int);
template MyGraph<int>   ::MyGraph(unsigned int);

template <class Elem>

MyGraph<Elem>::MyGraph(unsigned int cap)
{
    vertices  = new Elem[cap];
    directed  = false;
    v         = 0;
    e         = 0;
    this->cap = cap;
    visited   = new bool[cap];
}
