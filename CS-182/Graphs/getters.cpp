#include "mygraphs.hh"
#include "myamgraph.hh"

/**
 * V()
 * Returns the number of vertices in the graph
 *
 * Return unsigned int - The number of vertices currently in the graph
 * Precondition        - None
 * Postcondition       - None
 */

template unsigned int MyGraph<string>::V();
template unsigned int MyGraph<int>   ::V();

template <class Elem>

unsigned int MyGraph<Elem>::V()
{
    return v;
}

/**
 * E()
 * Returns the number of edges in the graph
 *
 * Return unsigned int - The number of edges currently in the graph
 * Precondition        - None
 * Postcondition       - None
 */

template unsigned int MyGraph<string>::E();
template unsigned int MyGraph<int>   ::E();

template <class Elem>

unsigned int MyGraph<Elem>::E()
{
    return e;
}

/**
 * get_edge()
 * Gets the edge connecting vertex i to vertex j
 *
 * Parameter i   - The starting index
 * Parameter j   - The ending index
 * Return int    - The weight of the edge from i to j
 * Precondition  - None; error checking is handled within the method
 * Postcondition - The weight connecting i and j is returned, or -1 if there is no such thing or invalid input
 */

template int MyAmGraph<string>::get_edge(unsigned int i, unsigned int j);
template int MyAmGraph<int>   ::get_edge(unsigned int i, unsigned int j);

template <class Elem>

int MyAmGraph<Elem>::get_edge(unsigned int i, unsigned int j)
{
    if((i < MyGraph<Elem>::v) && (j < MyGraph<Elem>::v) && (i != j)) //Not complex, therefore i != j
    {
        if(MyGraph<Elem>::directed)
            return am[i][j];
        else
        {
            if(i > j)
                return am[j][i - j - 1];
            else
                return am[i][j - i - 1]; //swap(i, j)
        }
    }

    return -1;
}
