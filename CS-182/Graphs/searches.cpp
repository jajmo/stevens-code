#include "mygraphs.hh"

/**
 * traverse()
 * Traverse the array. Calls BFS or DFS depending on the parameter
 *
 * Parameter dfs - If true, dfs() is called. If false, bfs() is called
 * Precondition  - None
 * Postcondition - The graph traversal is printed
 */

template void MyGraph<string>::traverse(bool);
template void MyGraph<int>   ::traverse(bool);

template <class Elem>

void MyGraph<Elem>::traverse(bool dfs)
{
    int i, j;

    for(i = 0; i < v; i++)
        visited[i] = false;

    for(j = 0; j < v; j++)
    {
        if(!visited[j])
        {
            if(dfs)
                this->dfs(j);
            else
                this->bfs(j);
        }
    }

    cout << endl;
}

/**
 * bfs()
 * Calls the private method bfs to traverse the graph
 *
 * Precondition  - None
 * Postcondition - The graph traversal is printed
 */

template void MyGraph<string>::bfs();
template void MyGraph<int>   ::bfs();

template <class Elem>

void MyGraph<Elem>::bfs()
{
    int i, j;

    for(i = 0; i < v; i++)
        visited[i] = false;

    for(j = 0; j < v; j++)
    {
        if(!visited[j])
            this->bfs(j);
    }

    cout << endl;
}

/**
 * dfs()
 * Calls the private method dfs to traverse the graph
 *
 * Precondition  - None
 * Postcondition - The graph traversal is printed
 */

template void MyGraph<string>::dfs();
template void MyGraph<int>   ::dfs();

template <class Elem>

void MyGraph<Elem>::dfs()
{
    int i, j;

    for(i = 0; i < v; i++)
        visited[i] = false;

    for(j = 0; j < v; j++)
    {
        if(!visited[j])
            this->dfs(j);
    }

    cout << endl;
}

/**
 * bfs()
 * Traverse the graph using a breadth first search
 *
 * Parameter i   - The index to begin the bfs at
 * Precondition  - i < v and i < cap
 * Postcondition - The bfs traversal is printed
 */

template void MyGraph<string>::bfs(unsigned int);
template void MyGraph<int>   ::bfs(unsigned int);

template <class Elem>

void MyGraph<Elem>::bfs(unsigned int i)
{
    unsigned int Q[v];
    unsigned int f = 0, b = 0;

    Q[b++]     = i;
    visited[i] = true;

    while(f != b)
    {
        unsigned int vertex = Q[f++];
        int n;
        cout << vertices[vertex] << " ";

        for(n = firstNeighbor(i); n >= 0; n = nextNeighbor(i, n))
        {
            if(!visited[n])
            {
                Q[b++] = n;
                visited[n] = true;
            }
        }
    }
}

/**
 * dfs()
 * Traverse the graph using a depth first search
 *
 * Parameter i   - The index to begin the dfs at
 * Precondition  - i < v and i < cap
 * Postcondition - The dfs traversal is printed
 */

template void MyGraph<string>::dfs(unsigned int);
template void MyGraph<int>   ::dfs(unsigned int);

template <class Elem>

void MyGraph<Elem>::dfs(unsigned int i)
{
    int n;
    visited[i] = true;

    cout << vertices[i] << " ";

    for(n = firstNeighbor(i); n >= 0; n = nextNeighbor(i, n))
        if(!visited[n])
            dfs(n);
}
