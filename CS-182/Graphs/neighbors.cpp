#include "myamgraph.hh"

/**
 * firstNeighbor()
 * Returns the index of the first neighbor of vertex V
 *
 * Parameter V   - The vertex to get the neighbor of
 * Return int    - The index of the first neighbor of V
 * Precondition  - V is a valid vertex. Error checking is handled by get_edge()
 * Postcondition - The index of the first neighbor of V is returned
 */

template int MyAmGraph<string>::firstNeighbor(unsigned int);
template int MyAmGraph<int>   ::firstNeighbor(unsigned int);

template <class Elem>

int MyAmGraph<Elem>::firstNeighbor(unsigned int V)
{
    int i, j;

    //Only traverse diagonals for undirected
    if(!MyGraph<Elem>::directed)
    {
	/* Traverse diagonals
	 * Ex: add_edge(1, 3, 5);
	 * 3 is a neighbor of 1
	 * 1 is also a neighbor of 3
	 * This loop accounts for that
	 */
        for(j = 0; j < MyGraph<Elem>::v; j++)
	        if(get_edge(j, V) > 0)
		        return j;
    }

    for(i = 0; i < MyGraph<Elem>::v; i++)
        if(get_edge(V, i) != -1)
            return i;

    return -1;
}

/**
 * nextNeighbor()
 * Get the next neighbor of vertex at index i beyond index j
 *
 * Parameter i   - The index of the vertex to get the neighbor of
 * Parameter j   - The last neighbor found
 * Precondition  - i and j are valid indicies
 * Postcondition - The index of the next neighbor is returned, or -1 if not found
 */

template int MyAmGraph<string>::nextNeighbor(unsigned int, unsigned int);
template int MyAmGraph<int>   ::nextNeighbor(unsigned int, unsigned int);
 
template <class Elem>

int MyAmGraph<Elem>::nextNeighbor(unsigned int i, unsigned int j)
{
    int l, k;

    if(!MyGraph<Elem>::directed)
    {
	//Same idea as above
	for(l = j + 1; j < MyGraph<Elem>::v; j++)
	    if(get_edge(l, i) > 0)
                return l;
    }

    for(k = j + 1; k < MyGraph<Elem>::v; k++)
        if(get_edge(i, k) != -1)
            return k;

    return -1;
}
