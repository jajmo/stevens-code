#include "mygraphs.hh"

template class MyGraph<string>;
template class MyGraph<int>;

template MyGraph<string>::MyGraph();
template MyGraph<int>::MyGraph();

template <class Elem>
MyGraph<Elem>::MyGraph()
{
  cap = 10;
  vertices = new Elem[cap];
  visited = new bool[cap];
  directed = true;
  v = 0;
  e = 0;
}

template MyGraph<string>::~MyGraph();
template MyGraph<int>::~MyGraph();

template <class Elem>
MyGraph<Elem>::~MyGraph()
{
  delete [] vertices;
  delete visited;
}

template <class Elem>
MyGraph<Elem>::MyGraph(bool dir)
{
  cap = 10;
  vertices = new Elem[cap];
  visited = new bool[cap];
  directed = dir;
  v = 0;
  e = 0;
}

template <class Elem>
MyGraph<Elem>::MyGraph(unsigned int cap, bool dir)
{
  if (cap < 10)
    cap = 10;
  vertices = new Elem[cap];
  visited = new bool[cap];
  directed = dir;
  v = 0;
  e = 0;
}

template <class Elem>
MyGraph<Elem>::MyGraph(unsigned int cap)
{
  if (cap < 10)
    cap = 10;
  vertices = new Elem[cap];
  visited = new bool[cap];
  directed = FALSE;
  v = 0;
  e = 0;
}

template unsigned int MyGraph<string>::V();
template unsigned int MyGraph<int>::V();

template <class Elem>
unsigned int MyGraph<Elem>::V()
{
  return v;
}

template unsigned int MyGraph<string>::E();
template unsigned int MyGraph<int>::E();

template <class Elem>
unsigned int MyGraph<Elem>::E()
{
  return e;
}

template int MyGraph<string>::add_vertex(string);
template int MyGraph<int>::add_vertex(int);

template <class Elem>
int MyGraph<Elem>::add_vertex(Elem e)
{
  if (v < cap)
    {
      vertices[v++] = e;
      return (v - 1);
    }
  return -1;
  
}

template void MyGraph<string>::show_vertices();

template <class Elem>
void MyGraph<Elem>::show_vertices()
{
  int i;

  for (i = 0; i < v; i++)
    cout << i << ": " << vertices[i] << endl;
}

template string MyGraph<string>::vertex(unsigned int);

template <class Elem>
Elem MyGraph<Elem>::vertex(unsigned int i)
{
  if (i < v)
    return vertices[i];
  return Elem();
}


template void MyGraph<string>::traverse(bool);

template <class Elem>
void MyGraph<Elem>::traverse(bool d)
{
  int i;
  
  for (i = 0; i < v; i++)
    visited[i] = FALSE;
  for (i = 0; i < v; i++)
    if (!visited[i])
      {
  (d)?dfs(i):bfs(i);
  cout << "| ";
      }
}


template void MyGraph<string>::bfs();

template <class Elem>
void MyGraph<Elem>::bfs()
{
  traverse(false);
}

template void MyGraph<string>::dfs();

template <class Elem>
void MyGraph<Elem>::dfs()
{
  traverse(true);
}

template void MyGraph<string>::bfs(unsigned int);

template <class Elem>
void MyGraph<Elem>::bfs(unsigned int n)
{
  unsigned int Q[v];
  int w;
  unsigned int h = 0;
  unsigned int t = -1;

  visited[n] = TRUE;
  Q[++t] = n;
  while (h <= t)
    {
      n = Q[h++];
      cout << vertices[n] << " ";
      for (w = firstNeighbor(n); w >= 0; w = nextNeighbor(n, w))
  if (!visited[w])
    {
      visited[w] = TRUE;
      Q[++t] = w;
    }
    }
}

template void MyGraph<string>::dfs(unsigned int);

template <class Elem>
void MyGraph<Elem>::dfs(unsigned int n)
{
  int w;

  visited[n] = TRUE;
  cout << vertices[n] << " ";
  for (w = firstNeighbor(n); w >= 0; w = nextNeighbor(n, w))
    if (!visited[w])
      dfs(w);
}
