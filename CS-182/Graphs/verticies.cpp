#include "mygraphs.hh"

/**
 * add_vertex()
 * Adds vertex newVertex to the graph
 *
 * Parameter newVertex - The vertex to be added to the graph
 * Return int          - The index of the element in the vertices array
 * Precondition        - The length of vertices is less than cap
 * Postcondition       - newVertex is added to vertices[v]
 */

template int MyGraph<int>   ::add_vertex(int);
template int MyGraph<string>::add_vertex(string);

template <class Elem>

int MyGraph<Elem>::add_vertex(Elem newVertex)
{
    if(v < cap)
    {
        vertices[v] = newVertex;
        return v++;
    }

    return -1;
}

/**
 * show_vertices()
 * Prints out the vertices array
 *
 * Precondition  - None
 * Postcondition - The vertices array is printed in the order the vertices were added
 */

template void MyGraph<int>   ::show_vertices();
template void MyGraph<string>::show_vertices();

template <class Elem>

void MyGraph<Elem>::show_vertices()
{
    int i;

    for(i = 0; i < v; i++)
        cout << vertices[i] << " ";

    cout << endl;
}

/**
 * vertex()
 * Returns the vertex at vertices[i]
 *
 * Parameter i   - The index of the vertex to return
 * Return Elem   - The element vertices[i]
 * Precondition  - Elem is not a string; i < v
 * Postcondition - vertices[i] is returned
 */

template int MyGraph<int>      ::vertex(unsigned int);
template string MyGraph<string>::vertex(unsigned int);

template <class Elem>

Elem MyGraph<Elem>::vertex(unsigned int i)
{
    if (i < v)
        return vertices[i];

    return 0;
}
