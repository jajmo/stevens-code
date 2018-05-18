#include "myamgraph.hh"

/**
 * show_am()
 * Prints out the adjacency matrix from index 0 to v - 1
 *
 * Precondition  - None
 * Postcondition - The adjacency matrix is printed from index 0 to v - 1
 */

template void MyAmGraph<string>::show_am();
template void MyAmGraph<int>   ::show_am();

template <class Elem>

void MyAmGraph<Elem>::show_am()
{
    int i, j;

    if(MyGraph<Elem>::directed)
    {
        for(i = 0; i < MyGraph<Elem>::v; i++)
        {
            for(j = 0; j < MyGraph<Elem>::v; j++)
                cout << am[i][j] << " ";

            cout << endl;
        }
    }
    else
    {
        for(i = 0; i < MyGraph<Elem>::v; i++)
        {
            for(j = 0; j < MyGraph<Elem>::v - i; j++)
                cout << am[i][j] << " ";

            cout << endl;
        }
    }
}

/**
 * show_edges()
 * Prints out the edges in the adjacency matrix
 *
 * Precondition  - None
 * Postcondition - The adjacency matrix is printed
 */

template void MyAmGraph<string>::show_edges();
template void MyAmGraph<int>   ::show_edges();

template <class Elem>

void MyAmGraph<Elem>::show_edges()
{
    if(MyGraph<Elem>::directed)
    {
        int i, j;

        for(i = 0; i < MyGraph<Elem>::v; i++)
        {
            for(j = 0; j < MyGraph<Elem>::v; j++)
                if(get_edge(i, j) > -1)
                    cout << am[i][j] << " ";
        }

        cout << endl;
    }
    else
    {
        int i, j;

        for(i = 0; i < MyGraph<Elem>::v; i++)
        {
            for(j = 0; j < MyGraph<Elem>::v - i; j++)
                if(am[i][j] > -1)
                    cout << am[i][j] << " ";
        }

        cout << endl;
    }
}
