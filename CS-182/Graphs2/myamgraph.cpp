#include "myamgraph.hh"

template class MyAmGraph<string>;

template int MyAmGraph<string>::get_edge(unsigned int, unsigned int);
template int MyAmGraph<int>::get_edge(unsigned int, unsigned int);

template <class Elem>
int MyAmGraph<Elem>::get_edge(unsigned int i, unsigned int j)
{
    if (i >= this->v || j >= this->v || i == j)
        return this->INF;
    if (this->directed)
        return am[i][j];
    if (i < j)
        return am[i][j - i - 1];
    return am[j][i - j - 1];
}


template MyAmGraph<string>::MyAmGraph(unsigned int, bool);
template MyAmGraph<int>::MyAmGraph(unsigned int, bool);

template <class Elem>
MyAmGraph<Elem>::MyAmGraph(unsigned int c, bool dir)
{
    int i, j, row;
    if (c < 10)
        c = 10;
    MyGraph<Elem>::cap = 10;
    MyGraph<Elem>::vertices = new Elem[MyGraph<Elem>::cap];
    MyGraph<Elem>::visited = new bool[MyGraph<Elem>::cap];
    MyGraph<Elem>::directed = dir;
    MyGraph<Elem>::v = 0;
    MyGraph<Elem>::e = 0;
    row = c;
    if (dir)
        am = new int*[c];
    else
        am = new int*[--c];
    for (i = 0; i < c; i++)
    {
        if (dir)
            am[i] = new int[c];
        else
            am[i] = new int[--row];
        for (j = 0; j < row; j++)
            am[i][j] = MyGraph<Elem>::INF;
    }
}

template MyAmGraph<string>::~MyAmGraph();
template MyAmGraph<int>::~MyAmGraph();

template <class Elem>

MyAmGraph<Elem>::~MyAmGraph()
{
    delete [] am;
}

template <class Elem>

int MyAmGraph<Elem>::firstNeighbor(unsigned int i)
{
    unsigned int w;
    
    if (i < MyGraph<Elem>::v)
    {
        /*  for (w = 0; w < this->v; w++)
        if (i != w && get_edge(i, w) != this->INF)
        return w; */
        if (MyGraph<Elem>::directed)
        {
            for (w = 0; w < MyGraph<Elem>::v; w++)
            {
                if (i != w && am[i][w] != MyGraph<Elem>::INF)
                    return w;
            }
        }
        else
        {
            for (w = 0; w < i; w++)
                if (am[w][i - w - 1] != MyGraph<Elem>::INF)
                    return w;

            for (w = 0; w < (MyGraph<Elem>::v - i - 1); w++)
                if (am[i][w] != MyGraph<Elem>::INF)
                    return i + w + 1;
        }
        
    }
    
    return -1;
}

template <class Elem>

int MyAmGraph<Elem>::nextNeighbor(unsigned int i, unsigned int j)
{
    unsigned int w;
    
    if ((i < MyGraph<Elem>::v) && (j < MyGraph<Elem>::v))
    {
        /*
        for (w = j+1; w < this->v; w++)
        if (i != w && get_edge(i, w) != this->INF)
        return w;
        */
        if (MyGraph<Elem>::directed)
        {
            for (w = j+1; w < MyGraph<Elem>::v; w++)
            {
                if (i != w && am[i][w] != MyGraph<Elem>::INF)
                    return w;
            }
        }
        else
        {
            for (w = j+1; w < i; w++)
            {
                if (am[w][i - w - 1] != MyGraph<Elem>::INF)
                    return w;
            }
            for (w++; w < MyGraph<Elem>::v; w++)
            {
                if (w != i && am[i][w - i - 1] != MyGraph<Elem>::INF)
                    return w;
            }
        }
        
    }
    
    return -1;
}

template bool MyAmGraph<string>::add_edge(unsigned int, unsigned int, int);

template <class Elem>

bool MyAmGraph<Elem>::add_edge(unsigned int i, unsigned int j, int weight)
{
    if (i != j && i < MyGraph<Elem>::v && j < MyGraph<Elem>::v)
    {
        if (MyGraph<Elem>::directed)
            am[i][j] = weight;
        else
        {
            if (i < j)
                am[i][j - i - 1] = weight;
            else
                am[j][i - j - 1] = weight;
        }
        MyGraph<Elem>::e++;
        return TRUE;
    }
    return FALSE;
}

template <class Elem>
void MyAmGraph<Elem>::show_edges()
{
    int i, j, stop;
    
    for (i = 0; i < MyGraph<Elem>::v; i++)
    {
        if (!MyGraph<Elem>::directed)
            stop = MyGraph<Elem>::v - i - 1;
        else
            stop = MyGraph<Elem>::v;
        for (j = 0; j < stop; j++)
        {
            if (am[i][j] != MyGraph<Elem>::INF)
            {
                cout << MyGraph<Elem>::vertices[i] << "--" << am[i][j] << "-";
                if (MyGraph<Elem>::directed)
                    cout << ">" << MyGraph<Elem>::vertices[j];
                else
                    cout << "-" << MyGraph<Elem>::vertices[j + i + 1];
                cout << endl;
            }
        }
    }
}

template void MyAmGraph<string>::show_am();

template <class Elem>
void MyAmGraph<Elem>::show_am()
{
    int i, j;
    
    if (MyGraph<Elem>::directed && this->v > 0)
    {
        for (i = 0; i < MyGraph<Elem>::v; i++)
        {
            for (j = 0; j <  MyGraph<Elem>::v; j++)
            {
                if (am[i][j] == MyGraph<Elem>::INF)
                    cout << "INF ";
                else
                    cout << am[i][j] << " ";
            }
            cout << endl;
        }
    }
    else
    {
        for (i = 0; i < (MyGraph<Elem>::v - 1); i++)
        {
            for (j = 0; j < (MyGraph<Elem>::v - i - 1); j++)
            {
                if (am[i][j] == MyGraph<Elem>::INF)
                    cout << "INF ";
                else
                    cout << am[i][j] << " ";
            }
            cout << endl;
        }
    }
}